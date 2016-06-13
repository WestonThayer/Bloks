// Bloks wrap pageItems. BlokAdapter provides functions to help store and retrieve them.

"use strict"

import Blok = require("./blok");
import BlokUserSettings = require("./blok-user-settings");
import BlokContainer = require("./blok-container");
import BlokContainerUserSettings = require("./blok-container-user-settings");
import Css = require("./css");
import Utils = require("./utils");

var JSON2 = require("JSON2");

/** Checks to see if a pageItem is the only thing in Isolation Mode. */
function isDirectlyIsolated(pageItem): boolean {
    if (pageItem && pageItem.parent.name === "Isolation Mode") {
        return true;
    }

    return false;
}

/** Try to get the Blok tag from a pageItem */
function retrieveBlokTag(pageItem: any): { name: string, value: string, remove: any } {
    let blokTag: any = undefined;

    try {
        blokTag = pageItem.tags["BLOKS_data"];
    }
    catch (e) {
        // No action, it's just not a Blok item
    }

    return blokTag;
}

function getBlokTagType(pageItem: any): string {
    let tag = retrieveBlokTag(pageItem);

    if (tag && tag.value) {
        let props = JSON2.parse(tag.value);
        return props.type;
    }

    return undefined;
}

/**
 * Checks to see if a Blok is already attached to the given PageItem.
 *
 * Note: this doesn't care about OOP inheritance. Will not return true
 * for a descendent of Blok.
 *
 * @param pageItem - item to check
 */
export function isBlokAttached(pageItem: any): boolean {
    return getBlokTagType(pageItem) === "Blok";
}

/**
 * Checks to see if the PageItem is the child of a BlokContainer, since
 * any direct child of a BlokContainer is ALWAYS a Blok (except if it's
 * a background). Returns false if the PageItem has a BlokContainer
 * attached to it.
 *
 * @param pageItem - item to check
 */
export function shouldBlokBeAttached(pageItem: any): boolean {
    // Check to see if it SHOULD be a Blok (has a BlokContainer as parent, but not a .bg)
    return !Utils.isKeyInString(pageItem.name, ".bg") &&
        pageItem.parent &&
        isBlokContainerAttached(pageItem.parent) &&
        !isBlokContainerAttached(pageItem);
}

/**
 * Checks to see if a BlokContanier is already attached to the given pageItem.
 *
 * @param pageItem - item to check
 */
export function isBlokContainerAttached(pageItem: any): boolean {
    return getBlokTagType(pageItem) === "BlokContainer";
}

export function getSavedProperty<T>(pageItem: any, name: string): T {
    let tag = retrieveBlokTag(pageItem);

    if (tag && tag.value) {
        let props = JSON2.parse(tag.value);
        return props[name];
    }

    return undefined;
}

export function setSavedProperty<T>(pageItem: any, name: string, value: T): void {
    let tag = retrieveBlokTag(pageItem);

    if (!tag) {
        tag = pageItem.tags.add();
        tag.name = "BLOKS_data";
    }

    let props = {};

    if (tag.value) {
        props = JSON2.parse(tag.value);
    }

    if (props[name] !== value) {
        props[name] = value;

        tag.value = JSON2.stringify(props);
    }
}

/**
 * Create from a pageItem.
 *
 * @param pageItem - art to wrap
 * @param settings - optional user settings to apply. If fixedWidth or fixedHeight is undefined,
 *                   we'll use the art's current dims
 * @returns either a brand new Blok attached to the pageItem, or a cached copy, or undefined
 *          if the parent isn't a BlokContainer, or undefined if the pageItem is the only thing
 *          in Isolation Mode.
 */
export function getBlok(pageItem: any, settings?: BlokUserSettings, skipContainerCheck: boolean = false): Blok {
    if (isDirectlyIsolated(pageItem)) {
        // Isolation Mode means that the parent just can't be a BlokContainer, so we can't fufill the request
        return undefined;
    }

    if (!skipContainerCheck && !isBlokContainerAttached(pageItem.parent)) {
        // If somehow we got unparented from a BlokContainer, the pageItem is not a Blok anymore.
        // Remove it's tag and don't fulfill the request.
        let blokTag = retrieveBlokTag(pageItem);

        if (blokTag) {
            blokTag.remove();
        }

        return undefined;
    }
    
    setSavedProperty<string>(pageItem, "type", "Blok");

    let blok = new Blok(pageItem);

    if (settings) {
        blok.setUserSettings(settings);
    }

    return blok;
}

/**
 * Create from a pageItem.
 *
 * @param pageItem - art to wrap
 * @param settings - optional user settings to apply
 * @returns either a brand new Blok attached to the pageItem, or a
 * cached copy.
 */
export function getBlokContainer(pageItem: any, settings?: BlokContainerUserSettings): BlokContainer {
    let isNew = !isBlokContainerAttached(pageItem);

    setSavedProperty<string>(pageItem, "type", "BlokContainer");

    let blok = new BlokContainer(pageItem);

    if (settings) {
        blok.setUserSettings(settings);
    }
    else if (isNew) {
        // If this is brand new, we need to configure some default values
        blok.setUserSettings(new BlokContainerUserSettings());
    }

    return blok;
}