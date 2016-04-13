/// <reference path="./typings/noderequire.d.ts" />
/// <reference path="./typings/illustrator.d.ts" />

"use strict"

import Blok = require("./blok");
import Css = require("./css");
import BlokContainerUserSettings = require("./blok-container-user-settings");
import Rect = require("./rect");
import BlokAdapter = require("./blok-adapter");
import Utils = require("./utils");

var JSON2 = require("JSON2");
require("./shim/myshims");
var cssLayout = require("css-layout");

class BlokContainer extends Blok {
    /**
     * DO NOT CALL, use a BlokAdapter method.
     *
     * @param pageItem - art to wrap
     */
    constructor(pageItem: any) {
        super(pageItem);
    }

    /** For css flex-direction */
    public getFlexDirection(): Css.FlexDirections {
        return this.getSavedProperty<Css.FlexDirections>("flexDirection");
    }
    /** For css flex-direction. Cannot be set to undefined */
    public setFlexDirection(value: Css.FlexDirections): void {
        if (value === undefined) {
            throw new TypeError("flex-direction cannot be undefined");
        }

        this.setSavedProperty<Css.FlexDirections>("flexDirection", value);
    }

    /** For css justify-content */
    public getJustifyContent(): Css.Justifications {
        return this.getSavedProperty<Css.Justifications>("justifyContent");
    }
    /** For css justify-content. Cannot be set to undefined */
    public setJustifyContent(value: Css.Justifications): void {
        if (value === undefined) {
            throw new TypeError("justify-content cannot be undefined");
        }

        this.setSavedProperty<Css.Justifications>("justifyContent", value);
    }

    /** For css align-items */
    public getAlignItems(): Css.Alignments {
        return this.getSavedProperty<Css.Alignments>("alignItems");
    }
    /** For css justify-content. Cannot be set to undefined */
    public setAlignItems(value: Css.Alignments): void {
        if (value === undefined) {
            throw new TypeError("align-items cannot be undefined");
        }

        this.setSavedProperty<Css.Alignments>("alignItems", value);
    }

    /** For css flex-wrap */
    public getFlexWrap(): Css.FlexWraps {
        return this.getSavedProperty<Css.FlexWraps>("flexWrap");
    }
    /** For css flex-wrap. Cannot be set to undefined */
    public setFlexWrap(value: Css.FlexWraps): void {
        if (value === undefined) {
            throw new TypeError("flex-wrap cannot be undefined");
        }

        this.setSavedProperty<Css.FlexWraps>("flexWrap", value);
    }

    /** The visible position and size, relative to the parent BlokContainer,
    or to the current artboard if there is no container */
    public /*override*/ getRect(): Rect {
        let actualArtboard = new Rect(Blok.getPageItemBounds(this._pageItem));
        let container = this.getContainer();

        if (container) {
            let actualContainerArtboard = new Rect(Blok.getPageItemBounds(this.getContainer()._pageItem));

            // Translate to coordinates relative to container
            let relativeX = actualArtboard.getX() - actualContainerArtboard.getX();
            let relativeY = actualArtboard.getY() - actualContainerArtboard.getY();

            actualArtboard.setX(relativeX);
            actualArtboard.setY(relativeY);
        }

        return actualArtboard;
    }

    /** Create a settings object reflecting our current state */
    public /*override*/ getUserSettings(): BlokContainerUserSettings {
        let settings = <BlokContainerUserSettings>super.getUserSettings();

        settings.flexDirection = this.getFlexDirection();
        settings.justifyContent = this.getJustifyContent();
        settings.alignItems = this.getAlignItems();
        settings.flexWrap = this.getFlexWrap();

        return settings;
    }

    /** Make our current state match the given user settings */
    public /*override*/ setUserSettings(value: BlokContainerUserSettings): void {
        super.setUserSettings(value);

        this.setFlexDirection(value.flexDirection);
        this.setJustifyContent(value.justifyContent);
        this.setAlignItems(value.alignItems);
        this.setFlexWrap(value.flexWrap);
    }

    /** Return a pre-layout css-layout node for this BlokContainer and all child Bloks */
    public /*override*/ computeCssNode(): any {
        let cssNode = super.computeCssNode();

        // Handle BlokContainer-specific fixed width/height rules
        let w = cssNode.style.width;
        let h = cssNode.style.height;

        if (this.getOverrideWidth() !== undefined) {
            w = this.getOverrideWidth();
            this.setOverrideWidth(undefined);
        }

        if (this.getOverrideHeight() !== undefined) {
            h = this.getOverrideHeight();
            this.setOverrideHeight(undefined);
        }

        cssNode.style.width = undefined;
        cssNode.style.height = undefined;

        if (this.getJustifyContent() === Css.Justifications.SPACE_BETWEEN) {
            if (this.getFlexDirection() === Css.FlexDirections.ROW) {
                cssNode.style.width = w;
            }
            else if (this.getFlexDirection() === Css.FlexDirections.COLUMN) {
                cssNode.style.height = h;
            }
            else {
                throw new Error("Unknown flexDirection!");
            }
        }

        if (this.getFlexWrap() === Css.FlexWraps.WRAP) {
            throw new Error("flexWrap=WRAP not implemented!");
        }

        cssNode.style.flexDirection = Css.enumStringToCssString(Css.FlexDirections[this.getFlexDirection()]);
        cssNode.style.justifyContent = Css.enumStringToCssString(Css.Justifications[this.getJustifyContent()]);
        cssNode.style.alignItems = Css.enumStringToCssString(Css.Alignments[this.getAlignItems()]);
        cssNode.style.flexWrap = Css.enumStringToCssString(Css.FlexWraps[this.getFlexWrap()]);

        cssNode.children = [];

        let blokChildren = this.getChildren();

        blokChildren.forEach((blok) => {
            let childCssNode = blok.computeCssNode();

            // Clear a dim from the child if we're stretching and give ourself
            // a fixed dimension. If even a single Blok child is set to stretch,
            // the BlokContainer must layout with a fixed w/h, otherwise the Blok child
            // has no defined container to stretch in
            if (this.getAlignItems() === Css.Alignments.STRETCH || blok.getAlignSelf() === Css.Alignments.STRETCH) {
                if (this.getFlexDirection() === Css.FlexDirections.ROW) {
                    cssNode.style.height = h;
                    childCssNode.style.height = undefined;
                }
                else if (this.getFlexDirection() === Css.FlexDirections.COLUMN) {
                    cssNode.style.width = w;
                    childCssNode.style.width = undefined;
                }
                else {
                    throw new Error("Unknown FlexDirections value: " + this.getFlexDirection());
                }
            }

            if (blok.getFlex() !== undefined && blok.getFlex() > 0) {
                if (this.getFlexDirection() === Css.FlexDirections.ROW) {
                    cssNode.style.width = w;
                    childCssNode.style.width = undefined;
                }
                else if (this.getFlexDirection() === Css.FlexDirections.COLUMN) {
                    cssNode.style.height = h;
                    childCssNode.style.height = undefined;
                }
                else {
                    throw new Error("Unknown FlexDirections value: " + this.getFlexDirection());
                }
            }

            cssNode.children.push(childCssNode);
        });

        return cssNode;
    }

    /** Trigger a layout */
    public /*override*/ invalidate(): void {
        // Start at the root of our layout tree
        let root = this.getRootContainer();

        let rootNode = root.computeCssNode();
        cssLayout(rootNode);

        root.layout(undefined, rootNode);
    }

    public /*override*/ checkForRelayout(lastSelection: any): void {
        let z = this.getZIndex();
        let cachedZ = this.getCachedZIndex();
        let isZIndexInvalid = cachedZ !== undefined && cachedZ !== z;

        if (this.getCachedChildCount() !== this._pageItem.pageItems.length) {
            // Short circut for new child count
            this.invalidate();
        }
        else {
            let rect = this.getRect();

            let isWidthInvalid = !Utils.nearlyEqual(this.getCachedWidth(), rect.getWidth());
            let isHeightInvalid = !Utils.nearlyEqual(this.getCachedHeight(), rect.getHeight());

            if (isWidthInvalid || isHeightInvalid) {
                let sel = app.activeDocument.selection;

                if ((sel.length === 1 && sel[0] && sel[0] === this._pageItem) &&
                    (lastSelection.length === 1 && lastSelection[0] && lastSelection[0] === this._pageItem)) {
                    // If this was the only thing selected for the past 2 selections and our size changed in
                    // betwen selections, enable some ease-of-use scenarios that attempt to use the new size
                    // the user wants for the BlokContainer

                    // We already have the new size in rect. Now undo their change, our layout will take their
                    // desires into account. Also:
                    //
                    // Illustrator messes with CharacterAttributes size, leading, and horizontalScale
                    // when you scale a GroupItem that contains a TextFrameItem that is AREATEXT (Area Type).
                    // Attempting to fix those values is difficult, since a TextFrameItem can have many
                    // TextRanges, all with different settings. Rather than attempt to store/restore those
                    // values, we just undo the resize, but not before we record our new desired size.
                    app.undo();

                    this.setOverrideWidth(rect.getWidth());
                    this.setOverrideHeight(rect.getHeight());

                    this.invalidate();
                }
                else {
                    this.invalidate();
                }
            }
            else {
                if (isZIndexInvalid) {
                    // We are a Blok child that is at a new z
                    this.invalidate();
                }
                else {
                    // Check to see if one of our Blok children is out of order
                    let children = this.getChildren();
                    let shouldInvalidate = false;

                    for (let i = 0; i < children.length; i++) {
                        let child = children[i];
                        let childZ = child.getZIndex();
                        let cachedChildZ = child.getCachedZIndex();

                        if (cachedChildZ !== undefined && cachedChildZ != childZ) {
                            shouldInvalidate = true;
                        }

                        child.setCachedZIndex(childZ);
                    }

                    if (shouldInvalidate) {
                        this.invalidate();
                    }
                }
            }
        }
        
        // Update z index cache
        this.setCachedZIndex(z);
    }

    /** A (possible) reference to the parent BlokContainer */
    protected /*override*/ getContainer(): BlokContainer {
        let container = undefined;

        try {
            container = super.getContainer();
        }
        catch (ex) { /* It's OK if a BlokContainer isn't nested */ }

        return container;
    }

    public /*override*/ getRootContainer(): BlokContainer {
        let container = super.getRootContainer();

        if (!container) {
            container = this;
        }

        return container;
    }

    /** Get our current set of Blok children */
    protected getChildren(): Blok[] {
        // Update cache
        this.setCachedChildCount(this._pageItem.pageItems.length);

        // sync the order of our children with the reverse z-order or the pageItems
        let sortedChildren: Blok[] = [];

        // low z-index to high z-index
        for (let i = this._pageItem.pageItems.length - 1; i >= 0; i--) {
            let pageItem = this._pageItem.pageItems[i];

            // Forego this check. Just convert all children, always
            /*if (!Blok.isBlokAttached(pageItem)) {
                throw new Error("We have non-Blok children?");
            }*/

            if (!Utils.isKeyInString(pageItem.name, ".bg")) {
                // Check to see if this is a BlokContainer. We'll convert a normal groupItem if it has
                // a specific name. This is mostly to keep test files easy to create
                if (pageItem.name === "<BlokGroup>" ||
                    (pageItem.pageItems && BlokAdapter.isBlokContainerAttached(pageItem))) {
                    sortedChildren.push(BlokAdapter.getBlokContainer(pageItem));
                }
                else {
                    sortedChildren.push(BlokAdapter.getBlok(pageItem));
                }
            }
        }

        return sortedChildren;
    }

    /**
     * PROTECTED: Resize and position all art in this group.
     *
     * @param desired - a rectangle for the new location and size. Possibly ignored
     *                  depending on settings
     * @param rootNode - a matching CSS node with full style and layout information
     * @param skipScaleTransform - if true, don't perform any scale
     */
    public /*override*/ layout(desired: Rect, rootNode: any, skipScaleTransform = false): void {
        // Layout our children
        let children = this.getChildren();

        for (let i = 0; i < children.length; i++) {
            let blok = children[i];
            let node = rootNode.children[i];

            // apply layout
            let blokRect = blok.getRect();
            blokRect.setX(node.layout.left);
            blokRect.setY(node.layout.top);
            blokRect.setWidth(node.layout.width);
            blokRect.setHeight(node.layout.height);

            blok.layout(blokRect, node);
        }

        // Layout the .bg
        if (this._pageItem.pageItems.length > 0 &&
            Utils.isKeyInString(this._pageItem.pageItems[this._pageItem.pageItems.length - 1].name, ".bg")) {
            let bg = this._pageItem.pageItems[this._pageItem.pageItems.length - 1];
            // Hack, we shouldn't be calling the constructor directly, but it's an easy way to get the layout func
            let bgBlok = new Blok(bg);

            bgBlok.layout(
                new Rect([0, 0, rootNode.layout.width, rootNode.layout.height]),
                rootNode,
                false,
                true
            );
        }

        if (desired) {
            // Layout ourselves, but never ask a BlokContainer to scale as part of layout
            super.layout(desired, undefined, true);
        }

        let curR = this.getRect();
        this.setCachedWidth(curR.getWidth());
        this.setCachedHeight(curR.getHeight());
    }

    /** Optional positive number for the number of Bloks this BlokContainer has */
    private getCachedChildCount(): number {
        return this.getSavedProperty<number>("cachedChildCount");
    }
    /** Optional positive number for the number of Bloks this BlokContainer has */
    private setCachedChildCount(value: number): void {
        if (value !== undefined && value < 0) {
            throw new RangeError("Cannot set a negative cached child count!");
        }

        this.setSavedProperty<number>("cachedChildCount", value);
    }

    /** Optional positive number that should be used as the BlokContainer's width in place of the
    real width */
    private getOverrideWidth(): number {
        return this.getSavedProperty<number>("overrideWidth");
    }
    /** Optional positive number that should be used as the BlokContainer's width in place of the
    real width */
    private setOverrideWidth(value: number): void {
        if (value !== undefined && value < 0) {
            throw new RangeError("Cannot set a negative override width!");
        }

        this.setSavedProperty<number>("overrideWidth", value);
    }

    /** Optional positive number that should be used as the BlokContainer's width in place of the
    real height */
    private getOverrideHeight(): number {
        return this.getSavedProperty<number>("overrideHeight");
    }
    /** Optional positive number that should be used as the BlokContainer's width in place of the
    real height */
    private setOverrideHeight(value: number): void {
        if (value !== undefined && value < 0) {
            throw new RangeError("Cannot set a negative override height!");
        }

        this.setSavedProperty<number>("overrideHeight", value);
    }
}

export = BlokContainer;