"use strict";

/**
 * Options set for CSS layout.
 */
class LayoutOpts {
    public useCachedWidth: boolean;
    public useCachedHeight: boolean;
    public useCachedTextInfo: boolean;

    constructor() {
        this.useCachedWidth = false;
        this.useCachedHeight = false;
        this.useCachedTextInfo = false;
    }
}

export = LayoutOpts;