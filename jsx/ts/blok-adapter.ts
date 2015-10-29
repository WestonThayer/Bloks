// Bloks wrap pageItems. BlokAdapter provides functions to help store and retrieve them.

"use strict"

import Blok = require("./blok");
import BlokUserSettings = require("./blok-user-settings");
import BlokContainer = require("./blok-container");
import BlokContainerUserSettings = require("./blok-container-user-settings");
import Css = require("./css");

var JSON2 = require("JSON2");

/** Try to get the Blok tag from a pageItem */
function retrieveBlokTag(pageItem: any): { name: string, value: string } {
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
 * Checks to see if a Blok is already attached to the given pageItem.
 *
 * @param pageItem - item to check
 */
export function isBlokAttached(pageItem: any): boolean {
    return getBlokTagType(pageItem) === "Blok";
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

    props[name] = value;

    tag.value = JSON2.stringify(props);
}

/**
 * Create from a pageItem.
 *
 * @param pageItem - art to wrap
 * @param settings - optional user settings to apply. If fixedWidth or fixedHeight is undefined,
 *                   we'll use the art's current dims
 * @returns either a brand new Blok attached to the pageItem, or a cached copy
 */
export function getBlok(pageItem: any, settings?: BlokUserSettings): Blok {
    setSavedProperty<string>(pageItem, "type", "Blok");

    let blok = new Blok(pageItem);

    if (settings) {
        blok.setUserSettings(settings);
    }

    // Record the initial dimensions if none were provided
    let r = blok.getRect();

    if (blok.getFixedWidth() === undefined) {
        blok.setFixedWidth(r.getWidth());
    }

    if (blok.getFixedHeight() === undefined) {
        blok.setFixedHeight(r.getHeight());
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