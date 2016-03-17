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
     * Normalize art object bounds be what we consider visible bounds.
     *
     * @param pageItem - an Illustrator pageItem
     * @returns a 4 digit array representing the visible bounds of art in SCREEN coordinates
     */
    protected static getPageItemBounds(pageItem: any): number[] {
        var bounds = pageItem.visibleBounds;

        if (pageItem.typename === "TextFrame" && pageItem.kind == TextType.AREATEXT) {
            bounds = pageItem.geometricBounds;
        }
        else if (pageItem.typename === "GroupItem") {
            let geoBounds = pageItem.geometricBounds;

            // Extremely special case. If a GroupItem contains a TextFrame that's AREATEXT, it's
            // possible for the top visible bound of that TextFrame to be greater than it's geometric
            // bounds. Since we always for a GroupItem's visible bounds, it naturally includes the taller
            // version of the TextFrame.
            //
            // Since it's normal for the GroupItem's visible and geometric bounds to differ (in cases
            // where child PathItems have a stroke), we have to check to see if the discrepency is
            // specifically due to a TextFrame. I've only seen this for the top or bottom bound, all others
            // seem to be fine.
            for (let b = 1; b < 4; b += 2) {
                if (!Utils.nearlyEqual(bounds[b], geoBounds[b])) {
                    for (let i = 0; i < pageItem.pageItems.length; i++) {
                        let child = pageItem.pageItems[i];

                        if (child.typename === "TextFrame" && child.kind == TextType.AREATEXT) {
                            if (Utils.nearlyEqual(bounds[b], child.visibleBounds[b])) {
                                bounds[b] = geoBounds[b];
                                break;
                            }
                        }
                    }
                }
            }
        }

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
     */
    public checkForRelayout(): void {
        let rect = this.getRect();

        let isWidthInvalid = !Utils.nearlyEqual(this.getCachedWidth(), rect.getWidth());
        let isHeightInvalid = !Utils.nearlyEqual(this.getCachedHeight(), rect.getHeight());

        if (isWidthInvalid || isHeightInvalid) {
            this.getContainer().invalidate();
        }
    }

    /** A reference to the parent BlokContainer */
    protected getContainer(): BlokContainer {
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
     */
    public layout(desired: Rect, rootNode: any): void {
        let actual = this.getRect();

        let transformMatrix = app.getIdentityMatrix();

        // Scale
        let aiDeltaX = (desired.getWidth() / actual.getWidth()) * 100;
        let aiDeltaY = (desired.getHeight() / actual.getHeight()) * 100;

        let isScaleRequested = !Utils.nearlyEqual(aiDeltaX, 100) || !Utils.nearlyEqual(aiDeltaY, 100);

        transformMatrix = app.concatenateScaleMatrix(transformMatrix, aiDeltaX, aiDeltaY);

        aiDeltaX = desired.getX() - actual.getX();
        aiDeltaY = desired.getY() - actual.getY();

        // Invert Y coordinate to go from screen to cartesian in Q4
        aiDeltaY *= -1;

        transformMatrix = app.concatenateTranslationMatrix(transformMatrix, aiDeltaX, aiDeltaY);

        // Apply

        if (isScaleRequested && this._pageItem.typename === "TextFrame" && this._pageItem.kind === TextType.AREATEXT) {
            // If you transform area type, it'll scale instead of just resizing the bounding box.
            // The crazy thing is -- there's no method to resize it's bounding box. The only way to
            // touch it at all is to create a brand new area type object...
            // This scenario is important... so that's what we do :(

            // First we have to write down the z index
            let z = 0; // 0 is top of Z stack

            for (let i = 0; i < this._pageItem.parent.pageItems.length; i++) {
                if (this._pageItem.parent.pageItems[i] === this._pageItem) {
                    z = i;
                    break;
                }
            }

            // Create a path with our desired location and size
            let tmpRect = this._pageItem.parent.pathItems.rectangle(
                this._pageItem.geometricBounds[1] + aiDeltaY, /*top*/
                this._pageItem.geometricBounds[0] + aiDeltaX, /*left*/
                desired.getWidth(), /*width*/
                desired.getHeight() /*height*/
                /*reversed (optional boolean, not sure what it does)*/
            );

            // Create the new area type
            let newAreaText = this._pageItem.parent.textFrames.areaText(
                tmpRect, /*path to serve as the bounds*/
                this._pageItem.orientation /*orientation (optional, not sure what it does, but seems safe to copy)*/
                /*baseFrame (optional TextFrameItem. For when you have text flowing from one area text box to another, this would be the preceeding box...)*/
                /*postFix (optional boolean, ...if you set postFix to true, then the baseFrame is the next/child box instead of the previous/parent)*/
            );

            //tmpRect.remove(); not necessary, seems to be eaten by area text. Attempting to remove will crash

            // Now that we have a TextFrame area with the correct size, copy over everything we can to
            // make this seamless

            // ??? maybe this keeps the frames hooked up?
            /*let prevFrame = this._pageItem.previousFrame;
            let nextFrame = this._pageItem.nextFrame;*/

            // Make sure this correctly preserves text content and styling
            this._pageItem.textRange.duplicate(newAreaText);

            // Track selection state
            let wasSelected = this._pageItem.selected;

            // Track all BlokSettings so we don't lose things
            let settings = this.getUserSettings();

            newAreaText.name = this._pageItem.name;
            newAreaText.note = this._pageItem.note;
            newAreaText.opacity = this._pageItem.opacity;

            this._pageItem.remove();
            this._pageItem = newAreaText;

            // Copy the tags onto the new PageItem
            BlokAdapter.getBlok(this._pageItem, settings);

            // Fix the z order
            for (let j = 0; j < z; j++) {
                this._pageItem.zOrder(ZOrderMethod.SENDBACKWARD);
            }

            if (wasSelected) {
                // Have to call redraw here or the selection won't go through
                app.redraw();

                // Select the new item
                this._pageItem.selected = true;
            }

            // Cache dims
            let curR = this.getRect();
            this.setCachedWidth(curR.getWidth());
            this.setCachedHeight(curR.getHeight());
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

            // Cache dims
            let curR = this.getRect();
            this.setCachedWidth(curR.getWidth());
            this.setCachedHeight(curR.getHeight());
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