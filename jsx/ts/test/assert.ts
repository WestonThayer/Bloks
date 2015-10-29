"use strict";

export function isTrue(value: boolean): void {
    if (!value) {
        throw new Error("Value is not true!");
    }
}

export function areEqual(one: any, two: any): void {
    if (one !== two) {
        throw new Error(one + " is not equal to " + two);
    }
}