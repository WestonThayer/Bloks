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

        if (pageItem.typename === "TextFrame") {
            bounds = pageItem.geometricBounds;
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

    /** Optional positive number for width */
    public getFixedWidth(): number {
        return this.getSavedProperty<number>("fixedWidth");
    }
    /** Optional positive number for width */
    public setFixedWidth(value: number): void {
        if (value !== undefined && value < 0) {
            throw new RangeError("Cannot set a negative width!");
        }

        this.setSavedProperty<number>("fixedWidth", value);
    }

    /** Optional positive number for height */
    public getFixedHeight(): number {
        return this.getSavedProperty<number>("fixedHeight");
    }
    /** Optional positive number for width */
    public setFixedHeight(value: number): void {
        if (value !== undefined && value < 0) {
            throw new RangeError("Cannot set a negative height!");
        }

        this.setSavedProperty<number>("fixedHeight", value);
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

        settings.fixedWidth = this.getFixedWidth();
        settings.fixedHeight = this.getFixedHeight();
        settings.flex = this.getFlex();
        settings.alignSelf = this.getAlignSelf();

        return settings;
    }

    /** Make our current state match the given user settings */
    public setUserSettings(value: BlokUserSettings): void {
        this.setFixedWidth(value.fixedWidth);
        this.setFixedHeight(value.fixedHeight);
        this.setFlex(value.flex);
        this.setAlignSelf(value.alignSelf);
    }

    /** Return a css-layout node */
    public computeCssNode(): any {
        let w = this.getFixedWidth();
        let h = this.getFixedHeight();

        let cssNode: any = {
            style: {
                width: w,
                height: h,
                flex: this.getFlex()
            }
        };
        
        // Have to set it here, css-layout gets confused if it's set and not needed
        if (this.getAlignSelf()) {
            cssNode.style.alignSelf = Css.enumStringToCssString(Css.Alignments[this.getAlignSelf()]);
        }

        return cssNode;
    }

    /**
     * Check the art's actual dimensions against fixedWidth and fixedHeight. If
     * they don't match and a resize is allowed, then update the Blok's size to match
     * and ask the parent BlokContainer to re-layout.
     */
    public checkForRelayout(): void {
        let rect = this.getRect();

        let isWidthInvalid = !Utils.nearlyEqual(this.getFixedWidth(), rect.getWidth());
        let isHeightInvalid = !Utils.nearlyEqual(this.getFixedHeight(), rect.getHeight());
        let shouldRevertWidth = false;
        let shouldRevertHeight = false;

        let container = this.getContainer();
        let containerRect = container.getRect();

        if (this.getAlignSelf() === Css.Alignments.STRETCH ||
            container.getAlignItems() === Css.Alignments.STRETCH) {
            if (container.getFlexDirection() === Css.FlexDirections.ROW) {
                // Has to be adjusted at the BlokContainer level
                shouldRevertHeight = true;
            }
            else if (container.getFlexDirection() === Css.FlexDirections.COLUMN) {
                if (rect.getWidth() < containerRect.getWidth()) {
                    // Ditto for col
                    shouldRevertWidth = true;
                }
            }
            else {
                throw new Error("Unknown flex-direction!");
            }
        }

        if (shouldRevertWidth || shouldRevertHeight) {
            // Correct the user by undoing their change
            app.undo();

            // This gets a little sad if user is decreasing both
            // width and height. They'd probably expect that we just
            // fix the dimension that we don't allow them to change.
            // However, this will cause a wonky undo stack (their change,
            // then our fix of it). They'll probably learn to scale a single
            // side.
        }
        else if (isWidthInvalid || isHeightInvalid) {
            if (isWidthInvalid) {
                this.setFixedWidth(rect.getWidth());
            }

            if (isHeightInvalid) {
                this.setFixedHeight(rect.getHeight());
            }

            // We allow resizing in both dimensions
            container.invalidate();
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
    protected getRootContainer(): BlokContainer {
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

        transformMatrix = app.concatenateScaleMatrix(transformMatrix, aiDeltaX, aiDeltaY);

        // This assumes that all scales happen from the midpoint of the art. Seems safe, couldn't
        // find a way to change the midpoint.
        let actualX = actual.getX() - ((desired.getWidth() - actual.getWidth()) / 2);
        let actualY = actual.getY() - ((desired.getHeight() - actual.getHeight()) / 2);

        aiDeltaX = desired.getX() - actualX;
        aiDeltaY = desired.getY() - actualY;

        // Invert Y coordinate to go from screen to cartesian in Q4
        aiDeltaY *= -1;

        transformMatrix = app.concatenateTranslationMatrix(transformMatrix, aiDeltaX, aiDeltaY);

        // Apply
        this._pageItem.transform(
            transformMatrix,
            true /*changePositions*/,
            false /*changeFillPatterns*/,
            false /*changeFillGradients*/,
            false /*changeStrokePattern*/,
            0.0 /*changeLineWidth - this one is weird. If you say 5, it multiplies the current stroke width by 5... */
        );
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