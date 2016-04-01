"use strict";

/**
 * Options set for CSS layout.
 */
class LayoutOpts {
    public useCachedWidth: boolean;
    public useCachedHeight: boolean;

    constructor() {
        this.useCachedWidth = false;
        this.useCachedHeight = false;
    }
}

export = LayoutOpts;