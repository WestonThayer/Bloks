#ifndef __AI110DrawArt__
#define __AI110DrawArt__

/*
 *        Name:	AI110DrawArt.h
 *   $Revision: $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 11.0 Draw Art Suite.
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

#ifndef __AIDrawArt__
#include "AIDrawArt.h"
#endif

#include "AIHeaderBegin.h"

/** @file AI110DrawArt.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI110DrawArtSuite			"AI Draw Art Suite"
#define kAIDrawArtSuiteVersion6		AIAPI_VERSION(6)
#define kAI110DrawArtSuiteVersion	kAIDrawArtSuiteVersion6
#define kAI110DrawArtVersion		kAIDrawArtSuiteVersion

/*******************************************************************************
 **
 **	Types
 **
 **/

/*******************************************************************************
 **
 **	Suite
 **
 **/

/**
	The draw art suite APIs can be used to draw Illustrator artwork to an
	output port (drawing surface). The port can either be contained within
	a window in the UI or it can be an offscreen drawing surface being used
	to rasterize artwork. There are a considerable number of options for
	controlling the drawing process.
 */
typedef struct {

	/** Draw artwork as specified by the AIDrawArtData parameter. */
	AIAPI AIErr (*DrawArt)( AIDrawArtData *data );
	/** Draw a color swatch as specified by the AIDrawColorData parameter. */
	AIAPI AIErr (*DrawColorSwatch)( AIDrawColorData *data );
	/** This method can only be called from the code that responds to an annotator's draw
		annotations message. It causes the highlighting annotations for the specified art
		object to be drawn using the specified color. */
	AIAPI AIErr (*DrawHilite)( AIArtHandle art, AIRGBColor* color );
	/** A convenience API for drawing a thumbnail of the art object to the AGM port with
		the specified bounds. */
	AIAPI AIErr (*DrawThumbnail) ( AIArtHandle art, void* port, AIRealRect* dstrect );

} AI110DrawArtSuite;


#include "AIHeaderEnd.h"


#endif
