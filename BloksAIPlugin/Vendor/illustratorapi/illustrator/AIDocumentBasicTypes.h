/*************************************************************************
*
* ADOBE CONFIDENTIAL
*
* Copyright 2008 Adobe
*
* All Rights Reserved.
*
* NOTICE: Adobe permits you to use, modify, and distribute this file in
* accordance with the terms of the Adobe license agreement accompanying
* it. If you have received this file from a source other than Adobe,
* then your use, modification, or distribution of it requires the prior
* written permission of Adobe.
*
**************************************************************************/
//
//  AIDocumentBasicTypes.h
//
//  TritiumLib.mp.64
//
//  Created by Anukriti Bajpai on 13/02/20.
//

#ifndef AIDocumentBasicTypes_h
#define AIDocumentBasicTypes_h

#include "AIBasicTypes.h"

/** Ruler unit values, see \c #AIDocumentSuite::GetDocumentRulerUnits() */
enum AIDocumentRulerUnitValue {
    kUnknownUnits = 0,
    /** inches */
    kInchesUnits,
    /** centimeters */
    kCentimetersUnits,
    /** points */
    kPointsUnits,
    /** picas */
    kPicasUnits,
    /** millimeters */
    kMillimetersUnits,
    /** pixels */
    kPixelsUnits,
    /** Q units */
    kQUnits,
    /** feet-inch */
    kFeetInchesUnits,
    /** meters */
    kMetersUnits,
    /** yards */
    kYardsUnits,
    /** feet */
    kFeetsUnits,
    /**last */
    kLastUnit = kFeetsUnits
};

/** The document color model used when creating a new document or opening
    a document, set in \c #AINewDocumentPreset::docColorMode.*/
typedef enum
{
    kAIUnknownColorModel = -1,
    /** Grayscale (Unimplemented. If specified, an RGB document is created.) */
    kAIGrayColorModel = 0,
    /** RGB */
    kAIRGBColorModel,
    /** CMYK */
    kAICMYKColorModel
} AIColorModel;

/** The preferred grid style for a new document,
    set in \c #AINewDocumentPreset::docTransparencyGrid.  */
typedef enum
{
    /** No grid */
    kAITransparencyGridNone = 0,
    /** Light gray lines */
    kAITransparencyGridLight,
    /** Medium gray lines */
    kAITransparencyGridMedium,
    /** Dark gray lines */
    kAITransparencyGridDark,
    /** Red lines */
    kAITransparencyGridRed,
    /** Orange lines */
    kAITransparencyGridOrange,
    /** Green lines */
    kAITransparencyGridGreen,
    /** Blue lines */
    kAITransparencyGridBlue,
    /** Purple lines */
    kAITransparencyGridPurple
} AITransparencyGrid;

/** The preferred preview mode for a new document,
    set in \c #AINewDocumentPreset::docPreviewMode.  */
typedef enum
{
    /* The default preview mode */
    kAIPreviewModeDefault = 0,
    /* Pixel preview mode */
    kAIPreviewModePixelPreview,
    /* Overprint preview mode */
    kAIPreviewModeOverprintPreview
} AIPreviewMode;

/** Raster resolution values for creating a new document,
    set in \c #AINewDocumentPreset::docRasterResolution.
    Values are in pixels-per-inch. This becomes the
    Raster Effect Settings value for the document. */
typedef enum
{
    /** Low or screen resolution, 72 PPI.  This is the default. */
    kAIRasterResolutionScreen = 0,
    /** Medium resolution, 150 PPI. */
    kAIRasterResolutionMedium,
    /** High resolution, 300 PPI. */
    kAIRasterResolutionHigh
} AIRasterResolution;

/** Artboard Layout for placing artboards while creating a new document,
set in \c #AINewDocumentPreset::docArtboardLayout.*/
typedef enum
{
    /** Arrange artboards in grid by row pattern*/
    kAIArtboardLayoutGridByRow  = 0 ,
    /** Arrange artboards in grid by column pattern*/
    kAIArtboardLayoutGridByCol,
    /** Arrange artboards in a single row*/
    kAIArtboardLayoutRow,
    /** Arrange artboards in a single column*/
    kAIArtboardLayoutCol,
    /** Arrange artboards in grid by row pattern from right to left*/
    kAIArtboardLayoutRLGridByRow,
    /** Arrange artboards in grid by column pattern from right to left*/
    kAIArtboardLayoutRLGridByCol,
    /** Arrange artboards in single row from right to left*/
    kAIArtboardLayoutRLRow
}AIArtboardLayout;

/** Color models that can be used to specify artwork colors
    for a specific document. See \c #AIDocumentSuite::GetDocumentColorModel() */
enum AIDocumentColorModelValue {
    kDocUnknownColor = -1,
    kDocGrayColor = 0,
    kDocRGBColor,
    kDocCMYKColor
};

/** Document targeting types.
    See \c #AIDocumentSuite::GetDocumentTargeting() (Not yet implemented.) */
enum {
    kDocTargetGroups,
    kDocTargetLeaves,
    kDocTargetPainted,
    kDocTargetExplicit
};

/** A \e book \e color is one of the named spot colors defined in files
    installed in the "Presets/Color Books" directory.
    The appearance definition of a book color specifies how to simulate
    the appearance of the spot ink when the physical ink is not available.

    This mode value indicates whether new book colors added to
    a document should use the standard or legacy appearance definition. It affects
    new spot colors that are added from a swatch library, by placing a file, or
    by cut and paste. See \c #AIDocumentSuite::GetDocumentSpotColorMode() and
    \c #AIDocumentSuite::GetDocumentSpotColorMode().

    @note Illustrator does not enforce the mode setting for new spot colors.
    However, the import code automatically resolves spot color conflicts.
    */
enum AISpotColorMode {
    /** The legacy definition matches prior versions of Illustrator,
        typically given using CMYK.*/
    kAILegacySpotColorMode = 0,
    /** The standard definition is the most accurate, typically given
        using Lab.*/
    kAIStandardSpotColorMode = 1,
    kAIDummySpotColorMode = 0xFFFFFFFF
};

#endif /* AIDocumentBasicTypes_h */
