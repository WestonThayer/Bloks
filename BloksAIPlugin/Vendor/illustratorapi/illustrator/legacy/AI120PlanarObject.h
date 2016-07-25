#ifndef __AI120PlanarObject__
#define __AI120PlanarObject__

/*
 *        Name:	AI120PlanarObject.h
 *     Purpose:	Adobe Illustrator 12.0 Planar Object Suite.
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

#include "AIPlanarObject.h"

#include "AIHeaderBegin.h"

/** @file AI120PlanarObject.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI120PlanarObjectSuite					kAIPlanarObjectSuite
#define kAIPlanarObjectSuiteVersion1			AIAPI_VERSION(1)
#define kAI120PlanarObjectSuiteVersion			kAIPlanarObjectSuiteVersion1

/*******************************************************************************
 **
 **	Suite
 **
 **/


/** APIs for creating, populating and querying attributes of a Planar Object plugin group. */
typedef struct {

	AIAPI AIPlanarObjectHandle (*NewPlanarObject) ( const AIRealMatrix* matrix, const AIGapOptions* gapOptions );

	AIAPI AIErr (*AddPath) (
			AIPlanarObjectHandle object, int segmentCount, AIPathSegment *segments,
			AIArtStyleHandle *leftFill, AIArtStyleHandle *rightFill, AIArtStyleHandle *stroke,
			AIBoolean closed );

	AIAPI AIErr (*AddPathUniform) (
			AIPlanarObjectHandle object, int segmentCount, AIPathSegment *segments,
			AIArtStyleHandle leftFill, AIArtStyleHandle rightFill, AIArtStyleHandle stroke,
			AIBoolean closed );

	AIAPI AIErr (*Abandon) ( AIPlanarObjectHandle object );

	AIAPI AIErr (*CreateArt) ( AIPlanarObjectHandle object, short paintOrder, AIArtHandle prep, AIArtHandle *newArt );

	AIAPI AIBoolean (*IsPlanarArtObject) ( AIArtHandle art );

	AIAPI AIErr (*ComplexConversionCanceled) ( AIBoolean fromPlanarMap, ASInt32 pathOrEdgeCount,
											const AIGapOptions* gapOptions, AIBoolean *warningDisplayed /*output*/ );

} AI120PlanarObjectSuite;


#include "AIHeaderEnd.h"


#endif	// __AI120PlanarObject__
