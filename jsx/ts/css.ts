"use strict"

/**
 * Converts from UPPERCASE_ENUM_NAME to uppercase-enum-name.
 *
 * @param value - ex: MyEnum[MyEnum.VALUE_ONE]
 * @returns ex: value-one
 */
export function enumStringToCssString(value: string): string {
    return value.toLowerCase().replace("_", "-");
}

/**
 * Converts from lowercase-enum-name to LOWERCASE_ENUM_NAME.
 * @param value - ex: lowercase-enum-name
 * @returns ex: LOWERCASE_ENUM_NAME
 */
export function cssStringToEnumString(value: string): string {
    return value.replace("-", "_").toUpperCase();
}

/** CSS flexbox alignment values */
export enum Alignments {
    FLEX_START,
    CENTER,
    FLEX_END,
    STRETCH,
}

/** CSS flexbox flex-direction. We only support row and column for simplicity. */
export enum FlexDirections {
    ROW,
    COLUMN,
}

/**
 * CSS justify-content. We only support flex-start and space-between.
 * Other options wouldn't make sense for Illustrator since they require the idea
 * of a container that can be larger than it's contents (padding). Illustrator
 * doesn't know how to draw the UI handles for that.
 */
export enum Justifications {
    FLEX_START,
    SPACE_BETWEEN,
}

/** CSS flex-wrap. We don't support wrap-reverse. */
export enum FlexWraps {
    NOWRAP,
    WRAP,
}