"use strict"

/**
 * Compare two numbers and see if they're within 0.0001 of eachother.
 * From: http://floating-point-gui.de/errors/comparison/
 *
 * @param a any number
 * @param b any number
 */
export function nearlyEqual(a: number, b: number): boolean {
    let epsilon = 0.0001;
    let absA = Math.abs(a);
    let absB = Math.abs(b);
    let diff = Math.abs(a - b);

    if (a === b) {
        return true;
    }
    else if (a === 0 || b === 0 || diff < Number.MIN_VALUE) {
        return diff < (epsilon * Number.MIN_VALUE);
    }
    else {
        return (diff / Math.min((absA + absB), Number.MAX_VALUE)) < epsilon;
    }
}