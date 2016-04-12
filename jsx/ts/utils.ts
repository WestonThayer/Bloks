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

/**
 * Detects whether the key is space delimited in the given string. For example, if
 * the key is ".spacer":
 *     ".spacer" -> true
 *     ".spacer thing" -> true
 *     ".spacerthing" -> false
 *     "thing .spacer" -> true
 *     "thing.spacer" -> false
 *
 * @param name - the string to search
 * @param key - the string to search for
 */
export function isKeyInString(name: string, key: string): boolean {
    if (!name) {
        return false;
    }

    if (name === key) { // exact match
        return true;
    }
    else if (name.indexOf(key, 0) !== -1) {
        if (name.indexOf(key + " ", 0) === 0 || // start of the string
            name.indexOf(" " + key) === ((name.length - key.length) - 1) || // end of the string
            name.indexOf(" " + key + " ", 0) !== -1) { // inside of the string
            return true;
        }
    }

    return false;
}