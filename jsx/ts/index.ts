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
    eventObj.type = "microsoft.design.bloks.JsxExceptionRaised";
    eventObj.data = ex.toString();
    eventObj.dispatch();
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

            if (!BlokAdapter.isBlokAttached(pageItem)) {
                throw new Error("We're not updating a Blok!");
            }

            BlokAdapter.getBlok(pageItem, settings);
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
            let groupPageItem = app.activeDocument.groupItems.add();
            groupPageItem.name = "<BlokGroup>";

            sel.forEach((pageItem) => {
                pageItem.move(groupPageItem, ElementPlacement.PLACEATEND);
            });

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
 *             or there's just a single non-Blok object selected
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

        let selection = app.activeDocument.selection;

        if (selection.length === 0) {
            // No operations available
        }
        else if (selection.length === 1) {
            let pageItem = selection[0];

            if (BlokAdapter.isBlokAttached(pageItem)) {
                let blok = BlokAdapter.getBlok(pageItem);

                ret.action = 2;
                ret.blok = blok.getUserSettings();
            }
            else if (BlokAdapter.isBlokContainerAttached(pageItem)) {
                let blokContainer = BlokAdapter.getBlokContainer(pageItem);

                ret.action = 1;
                ret.blok = blokContainer.getUserSettings();
            }
            else {
                // Can't do anything with just a single non-Blok item
            }
        }
        else {
            // The only thing you can do with multiple items is group them
            ret.action = 3;
        }

        return JSON2.stringify(ret);
    }
    catch (ex) {
        raiseException(ex);
    }
}