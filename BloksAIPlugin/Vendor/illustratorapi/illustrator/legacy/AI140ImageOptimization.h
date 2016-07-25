#ifndef __AI140ImageOptimization__
#define __AI140ImageOptimization__

/*
 *	Name:	AI140ImageOptimization.h
 *	Purpose:	Adobe Illustrator Image Optimization Suite
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

/********************************************************************************
 **
 **	Imports
 **
 **/

#ifndef __AITypes__
#include "AITypes.h"
#endif

#ifndef __AIDataFilter__
#include "AIDataFilter.h"
#endif

#ifndef __ASTypes__
#include "ASTypes.h"
#endif

#include "AIRasterize.h"

#include "AIHeaderBegin.h"

/** @file AIImageOptimization.h */

/********************************************************************************
 **
 **	Constants
 **
 **/

#define kAIImageOptSuiteVersion4		AIAPI_VERSION(4)
#define kAI140ImageOptSuiteVersion		kAIImageOptSuiteVersion4
#define kAI140ImageOptVersion			kAI140ImageOptSuiteVersion


/********************************************************************************
**
**	Types
**
**/

struct AI140ImageOptPNGParams {
	/** Version 1 parameters */
	AIImageOptPNGParams versionOneSuiteParams;
	/** When true, antialias text when rasterizing. */
	AIBool8 antialias;
	/** A cropping box for the art. If empty or degenerate, do not crop. */
	AIRealRect cropBox;
	/** When true, rasterize against a transparent background,
	applying no matte color. */
	AIBool8 backgroundIsTransparent;
	/** When background is not transparent, rasterize against this
	matte color. */
	AIRGBColor matteColor;

#ifdef __cplusplus
	/** Constructor for PNG parameters (version 2). */
	AI140ImageOptPNGParams()
		:
	versionOneSuiteParams(),
		antialias(false),	// no text antialiasing
		cropBox(),
		backgroundIsTransparent(true),	// no matte color applied
		matteColor()
	{
		cropBox.top = 0.0; cropBox.left = 0.0; cropBox.bottom = 0.0; cropBox.right = 0.0;
		matteColor.red = 0; matteColor.green = 0; matteColor.blue = 0;
	};
#endif
};

/********************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	These functions allow you to rasterize an art object and
	stream the resulting raster to a data filter in various image formats.
	@see \c #AIDataFilterSuite.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIImageOptSuite and \c #kAIImageOptVersion.
	*/
typedef struct {

	// AIImageOptSuiteVersion1 functions
	/** Rasterize art to GIF format.
			@param aiArt The art object or art tree root.
			@param aiDataFilter The data filter to which to send the resulting raster data.
			@param params How to perform the rasterization.
		*/
	AIAPI AIErr (*AsGIF)(
		AIArtHandle aiArt,
		AIDataFilter* aiDataFilter,
		AIImageOptGIFParams& params);

	/**  Rasterize art to JPEG format.
			@param aiArt The art object or art tree root.
			@param aiDataFilter The data filter to which to send the resulting raster data.
			@param params How to perform the rasterization.
		*/
	AIAPI AIErr (*AsJPEG)(
		AIArtHandle aiArt,
		AIDataFilter* aiDataFilter,
		AIImageOptJPEGParams& params);

	/**  Rasterize art to PNG24 format.
			@param aiArt The art object or art tree root.
			@param aiDataFilter The data filter to which to send the resulting raster data.
			@param params How to perform the rasterization.
		*/
	AIAPI AIErr (*AsPNG)(				// as PNG24
		AIArtHandle aiArt,
		AIDataFilter* aiDataFilter,
		AIImageOptPNGParams& params);

	/**  Rasterize art to ZLIB format.
			@param aiArt The art object or art tree root.
			@param aiDataFilter The data filter to which to send the resulting raster data.
			@param params How to perform the rasterization.
		*/
	AIAPI AIErr (*AsZLIB)(
		AIArtHandle aiArt,
		AIDataFilter* aiDataFilter,
		AIImageOptZLIBParams& params);

	// AIImageOptSuiteVersion2 functions

	/**  Rasterize art to PNG24 format. This differs from \c #AsPNG() in that it
		takes additional parameters and allows you to show a progress bar
		for a lengthy operation.
			@param aiArt The art object or art tree root.
			@param aiDataFilter The data filter to which to send the resulting raster data.
			@param params How to perform the rasterization.
			@param progressProc The procedure to call periodically during a lengthy operation,
				to provide the current progress status and allow the user to cancel.
		*/
	AIAPI AIErr (*MakePNG24)(
		AIArtHandle aiArt,
		AIDataFilter* aiDataFilter,
		AI140ImageOptPNGParams& params,
		AIRasterizeProgressProc progressProc);


	// AIImageOptSuiteVersion3 functions

	/** Creates a color palette for art.
			@param raster The art object.
			@param options The type of palette to create, automatic or custom.
			@param palette [out] A buffer in which to return the palette object.
		*/
	AIAPI AIErr (*CreatePalette) (AIArtHandle raster, const AIPaletteOptions *options, AIColorPaletteHandle *palette);

	/**	Frees the memory associated with a palette object when it is no longer
		needed.
			@param palette The palette object. Upon return, this reference is
				no longer valid.
		*/
	AIAPI AIErr (*DisposePalette) (AIColorPaletteHandle palette);

	/**	Retrieves a color from a color palette.
			@param palette The palette object.
			@param index The position index of the color.
			@param color [out] A buffer in which to return the color object.
		*/
	AIAPI AIErr (*GetPaletteColor) (AIColorPaletteHandle palette, ai::int32 index, AIPaletteColor *color);

	/**	Sets a color in a color palette.
			@param palette The palette object.
			@param index The position index of the color.
			@param color The color object.
		*/
	AIAPI AIErr (*SetPaletteColor) (AIColorPaletteHandle palette, ai::int32 index, AIPaletteColor *color);

	/** Creates an inverse color palette.
			@param palette The palette object.
			@param inverse [out] A buffer in which to return the inverse palette object.
			*/
	AIAPI AIErr (*CreateInversePalette) (AIColorPaletteHandle palette, AIInverseColorPaletteHandle *inverse);

	/**	Frees the memory associated with an inverse palette object when it is
		 no longer needed.
			@param inverse The inverse palette object. Upon return, this reference is
				no longer valid.
		*/
	AIAPI AIErr (*DisposeInversePalette) (AIInverseColorPaletteHandle inverse);

	/**	Retrieves the closest match to a color from an inverse color palette.
			@param palette The inverse palette object.
			@param color A pointer to the color object to match.
			@param index [out] A buffer in which to return the 0-based position
				index of the closest matching color.
		*/
	AIAPI AIErr (*GetPaletteIndex) (AIInverseColorPaletteHandle inverse, const AIPaletteColor *color, ai::int32 *index);

	/** Creates a color palette by posterizing the colors in a list.
			@param colorList The list of colors to be posterized, an array of color objects.
			@param colorListCount The number of color objects in the list.
			@param reduceColorCount The maximum number of colors the resulting palette should contain.
			@param palette [out] A buffer in which to return the palette object.
		*/
	AIAPI AIErr (*CreateReducedPalette) ( AIPaletteColor *colorList, int colorListCount, int reduceColorCount, AIColorPaletteHandle *palette  );
}
AI140ImageOptSuite;


#include "AIHeaderEnd.h"

#endif	// __AIImageOptimization__
