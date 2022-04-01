/*************************************************************************
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 *  Copyright 2018 Adobe Systems Incorporated
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Adobe Systems Incorporated and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to Adobe Systems Incorporated and its
 * suppliers and are protected by all applicable intellectual property
 * laws, including trade secret and copyright laws.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Adobe Systems Incorporated.
 **************************************************************************/

#pragma once
#ifndef __AIRasterTypes__
#define __AIRasterTypes__

namespace ai {
    /** Color models for raster data */
    enum RasterColorSpace {
        /** Flag indicating that the color model has an alpha channel. The alpha
            component appears after the color components. */
        kColorSpaceHasAlpha			= 0x10,

        /** Each pixel value for a gray color space has a single component
            describing a grayscale value. The gray color space is additive so the minimum
            value represents black and the maximum represents white. */
        kGrayColorSpace				= 0,
        /** Each pixel value for a RGB color space has three components which
            represent red, green and blue respectively. The RGB color space is additive. */
        kRGBColorSpace				= 1,
        /** Each pixel value for a CMYK color space has four components which
            represent cyan, magenta, yellow and black respectively. The CMYK color space
            is subtractive. */
        kCMYKColorSpace				= 2,
        /** Not valid as an image type; can occur only in placed linked
            files. See \c #AIPlacedSuite::GetRasterInfo(). */
        kLabColorSpace				= 3,
        /** Each pixel value for a separation color space has a single component
            describing a tint value. The separation color space is subtractive so the minimum
            value represents white and the maximum represents black. */
        kSeparationColorSpace		= 4,
        /** Each pixel value for an NChannel color space has of a variable number of
            components which represent individual channels in the NChannel color space.
            The process components of the color space could be either additive or subtractive.
            The spot components of the color space are subtractive. */
        kNChannelColorSpace			= 5,
        /** Each pixel value for an indexed color space has a single component
            describing an index value into a color lookup table. The number of components
            in the color lookup table depends on the base color space of the indexed
            color space. */
        kIndexedColorSpace			= 6,

        /** A gray color space with an alpha channel. */
        kAlphaGrayColorSpace		= (kGrayColorSpace | kColorSpaceHasAlpha),
        /** An RGB color space with an alpha channel. */
        kAlphaRGBColorSpace			= (kRGBColorSpace  | kColorSpaceHasAlpha),
        /** A CMYK color space with an alpha channel. */
        kAlphaCMYKColorSpace		= (kCMYKColorSpace | kColorSpaceHasAlpha),
        /** A LAB color space with an alpha channel. */
        kAlphaLabColorSpace			= (kLabColorSpace | kColorSpaceHasAlpha),
        /** A separation color space with an alpha channel. */
        kAlphaSeparationColorSpace	= (kSeparationColorSpace | kColorSpaceHasAlpha),
        /** An NChannel color space with an alpha channel. */
        kAlphaNChannelColorSpace	= (kNChannelColorSpace | kColorSpaceHasAlpha),
        /** An indexed color space with an alpha channel. */
        kAlphaIndexedColorSpace		= (kIndexedColorSpace | kColorSpaceHasAlpha),

        kInvalidColorSpace			= 0xFF
    };


    /** Data states for \c #AIRasterLink::datastate. Direct linking of images is deprecated
        (although still supported). Create linked objects using the \c #AIPlacedSuite. */
    enum RasterDataState {
        /** No data is available for the image (for example, when a
            document is opened and the linked file cannot be found). */
        kAIRasterNoData				= 0,
        /** Data is available and is the same data that was read from
            the linked file (that is, it has not been modified since being read). */
        kAIRasterLinkData			= 1,
        /** Data is available and it has been modified since it was read from
            the file (for example, a Photoshop filter might have been run on the image). */
        kAIRasterEditedData			= 2
    };
}

#endif
