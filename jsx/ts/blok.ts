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

    /** Trigger a layout of our container */
    public invalidate(): void {
        this.getContainer().invalidate();
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

        let isScaleRequested = aiDeltaX !== 100 || aiDeltaY !== 100;

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

            // Track all BlokSettings so we don't lose things like fixedWidth/fixedHeight
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
        }
        else {
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