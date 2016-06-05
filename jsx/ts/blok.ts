/// <reference path="./typings/noderequire.d.ts" />
/// <reference path="./typings/illustrator.d.ts" />

"use strict"

import Rect = require("./rect");
import Css = require("./css");
import BlokUserSettings = require("./blok-user-settings");
import BlokContainer = require("./blok-container");
import BlokAdapter = require("./blok-adapter");
import Utils = require("./utils");

/**
 * Wraps an Illustrator pageItem to add the capabilities needed for layout.
 * Ensures that all layout settings are persisted to disk.
 */
class Blok {
    /**
     * Normalize art object bounds
     *
     * @param pageItem - an Illustrator pageItem
     * @returns a 4 digit array representing the geometric bounds of art in SCREEN coordinates
     */
    protected static getPageItemBounds(pageItem: any): number[] {
        var bounds = pageItem.geometricBounds;

        // Convert from cartesian to screen coordinates
        bounds[1] *= -1;
        bounds[3] *= -1;

        return bounds;
    }

    protected _pageItem: any;

    /** DO NOT CALL, use a static method to instantiate! */
    constructor(pageItem: any) {
        this._pageItem = pageItem;
    }

    /** The visible position and size, relative to the parent BlokContainer */
    public getRect(): Rect {
        let actualArtboard = new Rect(Blok.getPageItemBounds(this._pageItem));
        let actualContainerArtboard = new Rect(Blok.getPageItemBounds(this.getContainer()._pageItem));

        // Translate to coordinates relative to container
        let relativeX = actualArtboard.getX() - actualContainerArtboard.getX();
        let relativeY = actualArtboard.getY() - actualContainerArtboard.getY();

        actualArtboard.setX(relativeX);
        actualArtboard.setY(relativeY);

        return actualArtboard;
    }
    /** Provide a new visible position and size (relative to the parent BlokContainer), the art will update to comply */
    public setRect(value: Rect): void {
        this.layout(value, undefined);
    }

    /** Optional >= 0 number for CSS flex-grow */
    public getFlex(): number {
        return this.getSavedProperty<number>("flex");
    }
    /** Optional >= 0 number for CSS flex-grow */
    public setFlex(value: number): void {
        if (value !== undefined && value < 0) {
            throw new RangeError("Cannot set a negative flex!");
        }

        this.setSavedProperty<number>("flex", value);
    }

    /** Optional value for CSS align-self */
    public getAlignSelf(): Css.Alignments {
        return this.getSavedProperty<Css.Alignments>("alignSelf");
    }
    /** Optional value for CSS align-self */
    public setAlignSelf(value: Css.Alignments): void {
        this.setSavedProperty<Css.Alignments>("alignSelf", value);
    }

    /** Create a settings object reflecting our current state */
    public getUserSettings(): BlokUserSettings {
        let settings = new BlokUserSettings();
        
        settings.flex = this.getFlex();
        settings.alignSelf = this.getAlignSelf();

        return settings;
    }

    /** Make our current state match the given user settings */
    public setUserSettings(value: BlokUserSettings): void {
        this.setFlex(value.flex);
        this.setAlignSelf(value.alignSelf);
    }

    /** Return a css-layout node */
    public computeCssNode(): any {
        let r = this.getRect();
        let w = r.getWidth();
        let h = r.getHeight();

        let cssNode: any = {
            style: {
                width: w,
                height: h,
                flex: this.getFlex()
            }
        };
        
        // Have to set it here, css-layout gets confused if it's set and not needed
        if (this.getAlignSelf() !== undefined) {
            cssNode.style.alignSelf = Css.enumStringToCssString(Css.Alignments[this.getAlignSelf()]);
        }

        return cssNode;
    }

    /** Trigger a layout of our container */
    public invalidate(): void {
        this.getContainer().invalidate();
    }

    /**
     * Check the art's actual dimensions against cachedWidth and cachedHeight. If
     * they don't match, then ask the parent BlokContainer to re-layout.
     *
     * @param lastSelection - the last known selection
     */
    public checkForRelayout(lastSelection: any): void {
        let rect = this.getRect();
        let z = this.getZIndex();
        let cachedZ = this.getCachedZIndex();

        let isWidthInvalid = !Utils.nearlyEqual(this.getCachedWidth(), rect.getWidth());
        let isHeightInvalid = !Utils.nearlyEqual(this.getCachedHeight(), rect.getHeight());
        let isZIndexInvalid = cachedZ !== undefined && cachedZ !== z;

        if (isWidthInvalid || isHeightInvalid || isZIndexInvalid) {
            this.getContainer().invalidate();
        }
        
        // Update z index cache
        this.setCachedZIndex(z);
    }

    /** A reference to the parent BlokContainer */
    public getContainer(): BlokContainer {
        let container = undefined;

        if (BlokAdapter.isBlokContainerAttached(this._pageItem.parent)) {
            container = BlokAdapter.getBlokContainer(this._pageItem.parent);
        }
        else {
            throw new Error("Our parent isn't a BlokContainer!");
        }

        return container;
    }

    /** A reference to the BlokContainer at the root of this tree */
    public getRootContainer(): BlokContainer {
        let par: Blok = this.getContainer();
        let blok: Blok = par;

        while (par) {
            blok = par;
            par = blok.getContainer();
        }

        return <BlokContainer>blok;
    }

    /**
     * PROTECTED: Resize and position the art, relative to the parent BlokContainer.
     *
     * @param desired - a rectangle for the new location and size
     * @param rootNode - a matching CSS node with full style and layout information, possibly undefined
     * @param skipScaleTransform - if true, don't perform any scale
     * @param skipCache - if true, don't cache any data
     */
    public layout(desired: Rect, rootNode: any, skipScaleTransform = false, skipCache = false): void {
        let actual = this.getRect();
        let isScaleRequested = false;
        let transformMatrix = app.getIdentityMatrix();
        let aiDeltaX, aiDeltaY;

        if (!skipScaleTransform) {
            // Scale
            aiDeltaX = (desired.getWidth() / actual.getWidth()) * 100;
            aiDeltaY = (desired.getHeight() / actual.getHeight()) * 100;

            isScaleRequested = !Utils.nearlyEqual(aiDeltaX, 100) || !Utils.nearlyEqual(aiDeltaY, 100);

            transformMatrix = app.concatenateScaleMatrix(transformMatrix, aiDeltaX, aiDeltaY);
        }

        // Translate
        aiDeltaX = desired.getX() - actual.getX();
        aiDeltaY = desired.getY() - actual.getY();

        // Invert Y coordinate to go from screen to cartesian in Q4
        aiDeltaY *= -1;

        transformMatrix = app.concatenateTranslationMatrix(transformMatrix, aiDeltaX, aiDeltaY);

        // Apply

        if (this._pageItem.typename === "TextFrame" && this._pageItem.kind === TextType.AREATEXT) {
            // If you transform area type, it'll scale instead of just resizing the bounding box.
            // You have to manipulate the TextPath
            this._pageItem.textPath.left += aiDeltaX;
            this._pageItem.textPath.top += aiDeltaY;
            this._pageItem.textPath.width = desired.getWidth();
            this._pageItem.textPath.height = desired.getHeight();

            if (!skipCache) {
                // Cache dims
                let curR = this.getRect();
                this.setCachedWidth(curR.getWidth());
                this.setCachedHeight(curR.getHeight());
            }
        }
        else {
            if (isScaleRequested || !Utils.nearlyEqual(aiDeltaX, 0) || !Utils.nearlyEqual(aiDeltaY, 0)) {
                this._pageItem.transform(
                    transformMatrix,
                    true /*changePositions*/,
                    false /*changeFillPatterns*/,
                    false /*changeFillGradients*/,
                    false /*changeStrokePattern*/,
                    0.0 /*changeLineWidth - this one is weird. If you say 5, it multiplies the current stroke width by 5... */,
                    Transformation.TOPLEFT /*transformAbout*/
                );
            }

            if (!skipCache) {
                // Cache dims
                let curR = this.getRect();
                this.setCachedWidth(curR.getWidth());
                this.setCachedHeight(curR.getHeight());
            }
        }
    }

    /**
     * Compare this Blok to another for equality.
     *
     * @param value - another Blok
     *
     * @returns true if the Bloks refer to the same art object
     */
    public equals(value: Blok): boolean {
        return this._pageItem === value._pageItem;
    }

    public getZIndex(): number {
        let index = -1;

        for (let i = 0; i < this._pageItem.parent.pageItems.length; i++) {
            if (this._pageItem === this._pageItem.parent.pageItems[i]) {
                index = i;
                break;
            }
        }

        return index;
    }

    /** Optional positive number for width. Use as a cache, not used in layout */
    protected getCachedWidth(): number {
        return this.getSavedProperty<number>("cachedWidth");
    }
    /** Optional positive number for width. Use as a cache, not used in layout */
    protected setCachedWidth(value: number): void {
        if (value !== undefined && value < 0) {
            throw new RangeError("Cannot set a negative cached width!");
        }

        this.setSavedProperty<number>("cachedWidth", value);
    }

    /** Optional positive number for height. Use as a cache, not used in layout */
    protected getCachedHeight(): number {
        return this.getSavedProperty<number>("cachedHeight");
    }
    /** Optional positive number for width. Use as a cache, not used in layout */
    protected setCachedHeight(value: number): void {
        if (value !== undefined && value < 0) {
            throw new RangeError("Cannot set a negative cached height!");
        }

        this.setSavedProperty<number>("cachedHeight", value);
    }

    /** Optional cache of layer position */
    public getCachedZIndex(): number {
        return this.getSavedProperty<number>("cachedZIndex");
    }
    /** Optional cache of layer position */
    public setCachedZIndex(value: number): void {
        if (value !== undefined && value < 0) {
            throw new RangeError("Cannot set a negative cached z index!");
        }

        this.setSavedProperty<number>("cachedZIndex", value);
    }

    /** Retrieve a property from the pageItem's tags. */
    protected getSavedProperty<T>(name: string): T {
        return BlokAdapter.getSavedProperty<T>(this._pageItem, name);
    }

    /** Set a proeprty in the pageItem's tags so it will be saved with the file. */
    protected setSavedProperty<T>(name: string, value: T): void {
        BlokAdapter.setSavedProperty<T>(this._pageItem, name, value);
    }
}

export = Blok;