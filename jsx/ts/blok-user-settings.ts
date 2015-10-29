"use strict";

/**
 * A simple, serializable container for what the user
 * can set on a Blok.
 */
class BlokUserSettings {
    public fixedWidth: number;
    public fixedHeight: number;
    public flex: number;
    public alignSelf: number;

    constructor() {
        // Leave everything as undefined
    }
}

export = BlokUserSettings;