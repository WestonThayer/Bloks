#ifndef __AI100DrawArt__
#define __AI100DrawArt__

/*
 *        Name:	AI100DrawArt.h
 *     Purpose:	Adobe Illustrator 10.0 Draw Art Suite.
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

#include "AIDrawArt.h"

#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI100DrawArtSuite			kAIDrawArtSuite
#define kAIDrawArtSuiteVersion5		AIAPI_VERSION(5)
#define kAI100DrawArtSuiteVersion	kAIDrawArtSuiteVersion5


/*******************************************************************************
 **
 **	Types
 **
 **/

typedef struct AI100DrawArtData {
	short version;
	
	AIDrawArtFlags flags;
	AIDrawArtOutputType type;
	AIRealPoint origin;
	AIRealMatrix matrix;
	AIArtHandle art;
	AIRealRect destClipRect;
	AIBoolean eraseDestClipRect; // erase destClipRect before arts are drawn.
	AIArtHandle interruptedArt;

	AIReal greekThreshold;
	AIExtendedRGBColorRec selectionColor;
	
	union {
		AIDrawArtGWorld gWorld;
		AIDrawArtAGMPort port;
	} output;
} AI100DrawArtData;


typedef struct AI100DrawColorData {
	AIDrawArtOutputType type;

	AIDrawColorStyle style;
	AIDrawColorOptions options;
	AIColor color;
	AIRealRect rect;
	AIReal width;							// when style is frame
	
	union {
		AIDrawArtGWorld gWorld;
		AIDrawArtAGMPort port;
	} output;
} AI100DrawColorData;


/*******************************************************************************
 **
 **	Suite
 **
 **/

typedef struct {

	AIAPI AIErr (*DrawArt)( AI100DrawArtData *data );
	AIAPI AIErr (*DrawColorSwatch)( AI100DrawColorData *data );
	AIAPI AIErr (*DrawHilite)( AIArtHandle art, AIRGBColor* color );
	AIAPI AIErr (*DrawThumbnail) ( AIArtHandle art, void* port, AIRealRect* dstrect );

} AI100DrawArtSuite;


#include "AIHeaderEnd.h"


#endif
