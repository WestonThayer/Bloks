/// <reference path="./typings/noderequire.d.ts" />
/// <reference path="./typings/illustrator.d.ts" />

"use strict";

// Typescript imports
import Rect = require("./rect");
import Css = require("./css");
import BlokAdapter = require("./blok-adapter");
import Blok = require("./blok");
import BlokUserSettings = require("./blok-user-settings");
import BlokContainer = require("./blok-container");
import BlokContainerUserSettings = require("./blok-container-user-settings");
import Utils = require("./utils");

// npm imports
var JSON2: any = require("JSON2");

/**
 * Raise an event to be handled by the CEP layer indicating that there has been
 * an unhandled exception.
 *
 * @param ex The raw exception object
 */
function raiseException(ex) {
    var xLib = new ExternalObject("lib:\PlugPlugExternalObject");
    var eventObj = new CSXSEvent();
    eventObj.type = "com.westonthayer.bloks.events.JsxExceptionRaised";
    eventObj.data = JSON2.stringify(ex);
    eventObj.dispatch();
}

/**
 * Verify that there is a Document object to work with. Returns false
 * if Illustrator doesn't have any documents in focus.
 */
function isActiveDocumentPresent(): boolean {
    try {
        let doc = app.activeDocument;
        return true;
    }
    catch (ex) {
        if (ex.message === "No such element") {
            return false;
        }
        else {
            raiseException(ex);
        }
    }
}

// Global variables
var bloksToBeInvalidated = []; // A cache of Bloks to call invalidate() on when its possible to do so
var lastSelection; // Tracks the most recent result of app.activeDocument.selection

export function checkSelectionForRelayout(): void {
    try {
        if (isActiveDocumentPresent()) {
            let sel = app.activeDocument.selection;

            if (sel.length === 1) {
                let pageItem = sel[0];

                if (pageItem) { // can be undefined when text ranges are selected
                    if (BlokAdapter.shouldBlokBeAttached(pageItem)) {
                        let blok = BlokAdapter.getBlok(pageItem);

                        if (blok) {
                            blok.checkForRelayout(lastSelection);
                        }
                    }
                    else if (BlokAdapter.isBlokContainerAttached(pageItem)) {
                        let blokContainer = BlokAdapter.getBlokContainer(pageItem);
                        blokContainer.checkForRelayout(lastSelection);
                    }
                    else if (pageItem.parent && pageItem.parent.parent && pageItem.parent.parent.name === "Symbol Editing Mode") {
                        // We're editing a Symbol. Special cases to make this important scenario work
                        let symName = pageItem.parent.name;

                        // Use the document's list of symbols to find the Bloks that wrap the symbol
                        for (let i = 0; i < app.activeDocument.symbolItems.length; i++) {
                            let symItem = app.activeDocument.symbolItems[i];

                            if (symItem.symbol.name === symName && BlokAdapter.shouldBlokBeAttached(symItem)) {
                                let blok = BlokAdapter.getBlok(symItem);

                                // Illustrator will refuse to run layout because we're in Symbol Editing Mode, so make a
                                // list of Bloks to invalidate the next chance we get
                                bloksToBeInvalidated.push(blok);
                            }
                        }
                    }
                }
            }
            else {
                // Ensure we're not in any sort of mode where invalidation would fail
                if (app.activeDocument.activeLayer.name !== "Isolation Mode" &&
                    (app.activeDocument.activeLayer.parent &&
                        app.activeDocument.activeLayer.parent.name !== "Symbol Editing Mode")) {

                    // Don't call invalidate on Bloks that share the same root BlokContainer since
                    // that's wasted work
                    let roots = [];

                    bloksToBeInvalidated.forEach((blok: Blok) => {
                        let root = blok.getRootContainer();
                        let alreadyInvalid = false;

                        roots.forEach((r: BlokContainer) => {
                            if (r.equals(root)) {
                                alreadyInvalid = true;
                            }
                        });

                        if (!alreadyInvalid) {
                            roots.push(root);
                            blok.invalidate();
                        }
                    });

                    // Clear the list
                    bloksToBeInvalidated.splice(0, bloksToBeInvalidated.length);
                }
            }

            lastSelection = sel;
        }
    }
    catch (ex) {
        raiseException(ex);
    }
}

export function relayoutSelection(): void {
    try {
        let sel = app.activeDocument.selection;

        if (sel.length === 1) {
            let pageItem = sel[0];

            if (BlokAdapter.shouldBlokBeAttached(pageItem)) {
                let blok = BlokAdapter.getBlok(pageItem);

                if (blok) {
                    blok.invalidate();
                }
            }
            else if (BlokAdapter.isBlokContainerAttached(pageItem)) {
                let blokContainer = BlokAdapter.getBlokContainer(pageItem);
                blokContainer.invalidate();
            }
        }
    }
    catch (ex) {
        raiseException(ex);
    }
}

/**
 * 
 * @param settings
 */
export function updateSelectedBlok(settings: BlokUserSettings): void {
    try {
        let sel = app.activeDocument.selection;

        if (sel.length === 1) {
            let pageItem = sel[0];

            if (!BlokAdapter.shouldBlokBeAttached(pageItem)) {
                throw new Error("We're not updating a Blok!");
            }

            let blok = BlokAdapter.getBlok(pageItem, settings);
            blok.invalidate();
        }
        else {
            throw new Error("Can only update one Blok at a time!");
        }
    }
    catch (ex) {
        raiseException(ex);
    }
}

export function updateSelectedBlokContainer(settings: BlokContainerUserSettings): void {
    try {
        let sel = app.activeDocument.selection;

        if (sel.length === 1) {
            let pageItem = sel[0];

            if (!BlokAdapter.isBlokContainerAttached(pageItem)) {
                throw new Error("We're not updating a BlokContainer!");
            }

            let blokContainer = BlokAdapter.getBlokContainer(pageItem, settings);
            blokContainer.invalidate();
        }
        else {
            throw new Error("Can only update one BlokContainer at a time!");
        }
    }
    catch (ex) {
        raiseException(ex);
    }
}

/**
 * Group the current selection and turn it into a BlokContainer.
 *
 * @param settings - user settings for the container. Child items will take their current dimensions
 */
export function createBlokContainerFromSelection(settings: BlokContainerUserSettings): void {
    try {
        let sel = app.activeDocument.selection;

        if (sel.length > 1) {
            // Find the correct Z order, since adding a new group will put it on top
            // The Illustrator behavior is to insert the group in place of the highest
            // selected item
            let z = 0;
            let par = sel[0].parent; // since zOrderPosition is broken, use the parent's order

            sel.forEach((pageItem) => {
                // Loop last to first (low z to high z)
                for (let i = par.pageItems.length - 1; i >= 0; i--) {
                    if (pageItem === par.pageItems[i]) {
                        // invert i so that it maps to z positioning (where 0 is lowest)
                        let invI = Math.abs(i - (par.pageItems.length - 1));

                        if (invI > z) {
                            z = invI;
                        }
                    }
                }
            });

            z -= sel.length - 1;

            // Add the new group at the hightest z position
            let groupPageItem = par.groupItems.add();
            groupPageItem.name = "<BlokGroup>";

            sel.forEach((pageItem) => {
                pageItem.move(groupPageItem, ElementPlacement.PLACEATEND);
            });

            // Now fix the z order
            groupPageItem.zOrder(ZOrderMethod.SENDTOBACK);

            for (let i = 0; i < z; i++) {
                groupPageItem.zOrder(ZOrderMethod.BRINGFORWARD);
            }

            let blokContainer = BlokAdapter.getBlokContainer(groupPageItem, settings);
            blokContainer.invalidate();
        }
        else {
            throw new Error("Must have multiple items selected to group them!");
        }
    }
    catch (ex) {
        raiseException(ex);
    }
}

/**
 * Check the active document's current selection and report back what
 * Bloks can do with it.
 *
 * @returns a JSON string with two properties:
 *     action: number - a single option of what Bloks can do
 *         0 - no operations available. Either there's nothing selected,
 *             or there's just a single non-Blok object selected, or
 *             a Blok child could be in Isolation Mode
 *         1 - a Blok container is selected, we can modify it
 *         2 - a Blok child is selected, we can modify it
 *         3 - multiple objects are selected, we can create a Blok container
 *     blok: the properties of the selected Blok, if there is one. Otherwise undefined
 */
export function getActionsFromSelection(): { action: number, blok: any } {
    try {
        let ret = {
            action: 0,
            blok: undefined
        };

        if (isActiveDocumentPresent()) {
            let selection = app.activeDocument.selection;

            if (selection.length === 0) {
                // No operations available
            }
            else if (selection.length === 1) {
                let pageItem = selection[0];

                if (pageItem) { // can be undefined for text ranges
                    if (BlokAdapter.shouldBlokBeAttached(pageItem)) {
                        let blok = BlokAdapter.getBlok(pageItem);

                        if (blok) {
                            ret.action = 2;
                            ret.blok = blok.getUserSettings();

                            if (pageItem.typename === "TextFrame" && pageItem.kind === TextType.AREATEXT) {
                                ret.blok.isAreaText = true;
                            }
                        }
                    }
                    else if (BlokAdapter.isBlokContainerAttached(pageItem)) {
                        let blokContainer = BlokAdapter.getBlokContainer(pageItem);

                        ret.action = 1;
                        ret.blok = blokContainer.getUserSettings();

                        if (pageItem.parent && BlokAdapter.isBlokContainerAttached(pageItem.parent)) {
                            ret.blok.isAlsoChild = true;
                        }
                    }
                    else {
                        // Can't do anything with just a single non-Blok item
                    }
                }
            }
            else {
                // The only thing you can do with multiple items is group them
                ret.action = 3;
            }
        }

        return JSON2.stringify(ret);
    }
    catch (ex) {
        raiseException(ex);
    }
}

/**
 * Look for PageItems with ".spacer" in their name and change their opacity.
 *
 * @param opacity - the new opacity value
 */
function changeSpacerOpacity(opacity: number): void {
    try {
        let pageItems = app.activeDocument.pageItems;

        for (let i = 0; i < pageItems.length; i++) {
            let pageItem = pageItems[i];
            let name = pageItem.name;

            if (!name && pageItem.symbol) {
                name = pageItem.symbol.name;
            }

            if (Utils.isKeyInString(name, ".spacer")) {
                try {
                    pageItem.opacity = opacity;
                }
                catch (ex) {
                    if (ex.message === "Target layer cannot be modified") {
                        // That's OK, it's in Isolation Mode. We'll do what we can, the
                        // user can always exit Isolation Mode and try again.
                    }
                    else {
                        throw ex;
                    }
                }
            }
        }
    }
    catch (ex) {
        raiseException(ex);
    }
}

export function hideSpacers(): void {
    changeSpacerOpacity(0.0);
}

export function showSpacers(): void {
    changeSpacerOpacity(100.0);
}