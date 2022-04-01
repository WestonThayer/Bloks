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
#ifndef __AIPlacedTypes__
#define __AIPlacedTypes__

namespace ai{
    /** Methods for positioning and sizing a linked object.
        @see \c #AIPlacedSuite::SetPlaceOptions(), \c #AIPlacedSuite::GetPlaceOptions() */
    enum PlaceMethod {
        /** Preserve original dimensions regardless of bounding box size and transformations. */
        kAsIs,
        /** Fill bounding box while preserving proportions. Can overlap edges in one dimension. */
        kFill,
        /** Fit fully inside bounding box while preserving proportions. */
        kFit,
        /** Fit to bounding box; replaced file preserves bounds but not proportions. */
        kConform,
        /** Fit to bounding box; replaced file preserves transformations and tries to preserve size.
            Default. */
        kReconform
    };

    /** Alignment options for positioning a linked object.
        @see \c #AIPlacedSuite::SetPlaceOptions(), \c #AIPlacedSuite::GetPlaceOptions() */
    enum PlaceAlignment {
        kTopLeft,
        kMidLeft,
        kBotLeft,

        kTopMid,
        kMidMid,
        kBotMid,

        kTopRight,
        kMidRight,
        kBotRight
    };
}
#endif
