"use strict";

import BlokUserSettings = require("./blok-user-settings");
import Css = require("./css");

/**
 * A simple, serializable container for what the user
 * can set on a BlokContainer.
 */
class BlokContainerUserSettings extends BlokUserSettings {
    public flexDirection: number;
    public justifyContent: number;
    public alignItems: number;
    public flexWrap: number;

    constructor() {
        super();

        this.flexDirection = Css.FlexDirections.ROW;
        this.justifyContent = Css.Justifications.FLEX_START;
        this.alignItems = Css.Alignments.FLEX_START;
        this.flexWrap = Css.FlexWraps.NOWRAP;
    }
}

export = BlokContainerUserSettings;