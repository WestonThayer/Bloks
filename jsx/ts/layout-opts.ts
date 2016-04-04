"use strict";

import Rect = require("./rect");

/**
 * Options set for CSS layout.
 */
class LayoutOpts {
    public useCachedWidth: boolean;
    public useCachedHeight: boolean;
    public desiredContainerRect: Rect;

    constructor() {
        this.useCachedWidth = false;
        this.useCachedHeight = false;
    }
}

export = LayoutOpts;