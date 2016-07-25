#ifndef __AI90Placed__
#define __AI90Placed__

/*
 *        Name:	AI90Placed.h
 *   $Revision: 24 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 9.0 Placed Object Suite.
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

#include "AI110Placed.h"

#include "AIHeaderBegin.h"

/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAI90PlacedSuite			"AI Placed Suite"
#define kAIPlacedSuiteVersion4	AIAPI_VERSION(4)
#define kAI90PlacedSuiteVersion	kAIPlacedSuiteVersion4
#define kAI90PlacedVersion		kAI90PlacedSuiteVersion

/*******************************************************************************
 **
 **	Suite
 **
 **/

typedef struct AI90PlacedSuite {

	AIAPI AIErr (*GetPlacedMatrix) ( AIArtHandle placed, AIRealMatrix *matrix );
	AIAPI AIErr (*SetPlacedMatrix) ( AIArtHandle placed, AIRealMatrix *matrix );
	AIAPI AIErr (*GetPlacedBoundingBox) ( AIArtHandle placed, AIRealRect *bbox );
	AIAPI AIErr (*SetPlacedObject) ( AIArtHandle placed, AIArtHandle *group );
	AIAPI AIErr (*CountPlacedCustomColors) ( AIArtHandle art, long *count );
	AIAPI AIErr (*GetNthPlacedCustomColorName) ( AIArtHandle art, long num, char *name, int maxlen );
	AIAPI AIErr (*MakePlacedObjectNative) ( AIArtHandle placed, AIArtHandle *native );
	AIAPI AIErr (*GetPlacedType) ( AIArtHandle placed, short *pPlacedType );
	AIAPI AIErr (*GetPlacedChild) ( AIArtHandle placed, AIArtHandle *group );
	AIAPI AIErr (*ExecPlaceRequest)( AI110PlaceRequestData *pPlaceRequestData );
	AIAPI AIErr (*GetPlacedFilePathFromArt)( AIArtHandle placed, char *pszPath, int iMaxLen );
	AIAPI AIErr (*ConcatPlacedMatrix) ( AIArtHandle placed, AIRealMatrix *concat );

} AI90PlacedSuite;


#include "AIHeaderEnd.h"


#endif

