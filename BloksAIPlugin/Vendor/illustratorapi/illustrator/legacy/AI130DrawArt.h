#ifndef __AI130DrawArt__
#define __AI130DrawArt__

/*
 *        Name:	AI1300DrawArt.h
 *   $Revision: $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Draw Art Suite.
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

#ifndef	__AI140DrawArt__
#include "AI140DrawArt.h"
#endif

#include "AIHeaderBegin.h"

/** @file AI30DrawArt.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI130DrawArtSuite				kAIDrawArtSuite
#define kAIDrawArtSuiteVersion7		AIAPI_VERSION(7)
#define kAI130DrawArtSuiteVersion		kAIDrawArtSuiteVersion7
#define kAI130DrawArtVersion		kAI130DrawArtSuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/
/* Illustrator 13.0 DrawArt suite */
typedef struct {

	AIAPI AIErr (*DrawArt)( AI140DrawArtData *data, const AIColorConvertOptions& options );

	AIAPI AIErr (*BeginDrawArt)( AI140DrawArtData * data, const AIColorConvertOptions& options, AIDrawArtFlags flags );

	AIAPI AIErr (*EndDrawArt)( AI140DrawArtData *data, const AIColorConvertOptions& options );

	AIAPI AIErr (*DrawColorSwatch)( AIDrawColorData *data );

	AIAPI AIErr (*DrawHilite)( AIArtHandle art, AIRGBColor* color);

	AIAPI AIErr (*DrawThumbnail) ( AIArtHandle art, void* port, AIRealRect* dstrect );

} AI130DrawArtSuite;


#include "AIHeaderEnd.h"


#endif	//__AI130DrawArt__
