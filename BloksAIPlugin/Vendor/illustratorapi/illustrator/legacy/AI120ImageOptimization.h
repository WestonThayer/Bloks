#ifndef __AI120ImageOptimization__
#define __AI120ImageOptimization__

/*
 *	Name:	AI120ImageOptimization.h
 *	Purpose:	Adobe Illustrator 12.0 Image Optimization Suite
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



/*******************************************************************************
**
**	Imports
**
**/
#include "AIImageOptimization.h"

#include "AIHeaderBegin.h"

/** @file AI120ImageOptimization.h */

/*******************************************************************************
**
**	Constants
**
**/
#define kAIImageOptSuiteVersion1 AIAPI_VERSION(1)
#define kAIImageOptSuiteVersion2 AIAPI_VERSION(2)
#define kAIImageOptSuiteVersion3 AIAPI_VERSION(3)

/*******************************************************************************
**
**	Suite
**
**/


// version 3
typedef struct {

	AIAPI AIErr (*AsGIF)(
		AIArtHandle aiArt,
		AIDataFilter* aiDataFilter,
		AIImageOptGIFParams& params);

	AIAPI AIErr (*AsJPEG)(
		AIArtHandle aiArt,
		AIDataFilter* aiDataFilter,
		AIImageOptJPEGParams& params);

	AIAPI AIErr (*AsPNG)(				
		AIArtHandle aiArt,
		AIDataFilter* aiDataFilter,
		AIImageOptPNGParams& params);

	AIAPI AIErr (*AsZLIB)(
		AIArtHandle aiArt,
		AIDataFilter* aiDataFilter,
		AIImageOptZLIBParams& params);

	AIAPI AIErr (*MakePNG24)(
		AIArtHandle aiArt,
		AIDataFilter* aiDataFilter,
		AI140ImageOptPNGParams& params,
		AIRasterizeProgressProc progressProc);

	AIAPI AIErr (*CreatePalette) (AIArtHandle raster, const AIPaletteOptions *options, AIColorPaletteHandle *palette);
	AIAPI AIErr (*DisposePalette) (AIColorPaletteHandle palette);

	AIAPI AIErr (*GetPaletteColor) (AIColorPaletteHandle palette, long index, AIPaletteColor *color);
	AIAPI AIErr (*SetPaletteColor) (AIColorPaletteHandle palette, long index, AIPaletteColor *color);

	AIAPI AIErr (*CreateInversePalette) (AIColorPaletteHandle palette, AIInverseColorPaletteHandle *inverse);
	AIAPI AIErr (*DisposeInversePalette) (AIInverseColorPaletteHandle inverse);

	AIAPI AIErr (*GetPaletteIndex) (AIInverseColorPaletteHandle inverse, const AIPaletteColor *color, long *index);

}
AI120ImageOptSuite;


#include "AIHeaderEnd.h"

#endif	// __AI120ImageOptimization__
