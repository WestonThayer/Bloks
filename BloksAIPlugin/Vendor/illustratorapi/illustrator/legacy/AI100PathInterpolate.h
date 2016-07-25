#ifndef __AI100PathInterp__
#define __AI100PathInterp__

/*
 *      Name:		AIPathInterpolate.h
 * 		Purpose:	Adobe Illustrator 10.0 Path Interpolation Suite.
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

#include "AIPathInterpolate.h"

#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI100PathInterpolateSuite			kAIPathInterpolateSuite
#define kAIPathInterpolateSuiteVersion1		AIAPI_VERSION(1)
#define kAI100PathInterpolateVersion		kAIPathInterpolateSuiteVersion1



/*******************************************************************************
 **
 **	Types
 **
 **/

// See the most recent version of AIPathInterpolate.h for the following typedefs:

// struct AIKnot
// struct AIFlattenedPath;
// struct AIAnchorIdentifier;
// struct AIPathInstallData;
// struct _t_AIStyleInterpolator* AIStyleInterpolator;
// ASErr (*PostInstallCB)( AIArtHandle art, AIPathInstallData *installData );


/*******************************************************************************
 **
 **	Suite
 **
 **/

// Illustrator 9.0 and 10.0 Path Interpolation Suite
// (AI 8.0 version was same through MeasurePathSegments. The suite version was not bumped for AI 9.0)

// For comments on suite functions, see most recent version of AIPathInterpolate.h
typedef struct {

	AIAPI AIErr (*SmoothColorBlendSteps) ( AIArtHandle startPath, AIArtHandle endPath,
										AIReal densityLimit, short *steps );

	AIAPI AIErr (*GetPathSelectedSegmentCount) ( AIArtHandle path, short *count );
	AIAPI AIErr (*PathSelectionToAnchorIDs) ( AIArtHandle path, short count, AIAnchorIdentifier *anchorIDs );
	AIAPI AIErr (*PathSelectionToSegNumbers) ( AIArtHandle path, short count, short *selectedPoints );

	AIAPI AIErr (*SelectAnchorPoints) ( AIArtHandle path, short count, short *selectPoints );

	AIAPI AIErr (*InsertInterpolants) ( AIArtHandle startPath,
										AIArtHandle endPath,
										AIRealPoint	*substituteCenter,
										AIArtHandle useStyleFromPath,
										short steps,
										short numMatchPairs, short *matches1, short *matches2,
										AIPathInstallData *installData,
										PostInstallCB clientCallback);

	AIAPI AIErr (*MeasurePathSegments) ( AIArtHandle path,
										short ixStart, short count,
										AIReal *segLengths,
										AIReal flatness );

	// New for AI 9:
	AIAPI AIErr (*NewStyleInterpolator) ( AIStyleInterpolator* interpolator, AIArtHandle styleSource0, AIArtHandle styleSource1 );
	// Free memory for a style interpolator.
	AIAPI AIErr (*DisposeStyleInterpolator) ( AIStyleInterpolator interpolator );

	AIAPI AIErr (*ApplyInterpolatedStyle) ( AIStyleInterpolator interpolator, AIArtHandle targetArt, AIReal fraction );

	AIAPI AIErr (*NewArtStyleInterpolator) ( AIStyleInterpolator* interpolator, AIArtStyleHandle style0, AIArtStyleHandle style1 );
	AIAPI AIErr (*GetInterpolatedArtStyle) ( AIStyleInterpolator interpolator, AIReal fraction, AIArtStyleHandle* result );

} AI100PathInterpolateSuite;


#include "AIHeaderEnd.h"


#endif
