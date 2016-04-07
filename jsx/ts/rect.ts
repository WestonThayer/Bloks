"use strict"

import Utils = require("./utils");

/**
 * Represents a rectangle in screen coordinate space.
 *
 *                | (-y)
 *                |
 *  (-x)          |             (+x)
 *  --------------------------------
 *                |
 *                |
 *                | (+y)
 */
class Rect {
    private x1: number;
    private y1: number;
    private x2: number;
    private y2: number;

    /**
     * @param bounds - an array of 4 numbers, left, top, right, bottom
     * @constructor
     */
    constructor(bounds: number[]) {
        this.x1 = bounds[0];
        this.y1 = bounds[1];
        this.x2 = bounds[2];
        this.y2 = bounds[3];
    }

    public getLeft(): number {
        return this.x1;
    }

    public getTop(): number {
        return this.y1;
    }

    public getRight(): number {
        return this.x2;
    }

    public getBottom(): number {
        return this.y2;
    }

    public getX(): number {
        return this.x1;
    }
    /** Update the x position without changing width */
    public setX(value: number): void {
        let delta = value - this.x1;
        this.x1 = value;
        this.x2 += delta;
    }

    public getY(): number {
        return this.y1;
    }
    /** Update the y position without changing height */
    public setY(value: number): void {
        let delta = value - this.y1;
        this.y1 = value;
        this.y2 += delta;
    }

    public getWidth(): number {
        return Math.abs(this.x1 - this.x2);
    }
    /** Update the width without adjusting the x position */
    public setWidth(value: number): void {
        this.x2 = this.x1 + value;
    }

    public getHeight(): number {
        return Math.abs(this.y1 - this.y2);
    }
    /** Update the height without adjusting the y position */
    public setHeight(value: number): void {
        this.y2 = this.y1 + value;
    }

    public equals(rect: Rect): boolean {
        if (Utils.nearlyEqual(this.x1, rect.x1) &&
            Utils.nearlyEqual(this.y1, rect.y1) &&
            Utils.nearlyEqual(this.x2, rect.x2) &&
            Utils.nearlyEqual(this.y2, rect.y2)) {
            return true;
        }

        return false;
    }
}

export = Rect;