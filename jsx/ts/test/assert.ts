"use strict";

import Utils = require("../utils");

export function isTrue(value: boolean): void {
    if (!value) {
        throw new Error("Value is not true!");
    }
}

export function areEqual(one: any, two: any): void {
    if (typeof one === "number" && typeof two === "number") {
        if (!Utils.nearlyEqual(one, two)) {
            throw new Error(one + " is not nearly equal to " + two);
        }
    }
    else if (one !== two) {
        throw new Error(one + " is not equal to " + two);
    }
}