#ifndef __AI90MatchingArt__
#define __AI90MatchingArt__

/*
 *        Name:	AI90MatchingArt.h
 *   $Revision: 4 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 9.0 Matching Art Suite.
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

#include "AIMatchingArt.h"

#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI90MatchingArtSuite		kAIMatchingArtSuite
#define kAIMatchingArtSuiteVersion3	AIAPI_VERSION(3)
#define kAI90MatchingArtVersion		kAIMatchingArtSuiteVersion3


/*******************************************************************************
 **
 **	Suite
 **
 **/

typedef struct {

	/* Get the art matching the given criteria and on the current layer list. */
	AIAPI AIErr (*GetSelectedArt) ( AIArtHandle ***matches, long *numMatches );
	AIAPI AIErr (*GetMatchingArt) ( AIMatchingArtSpec *specs, short numSpecs,
			AIArtHandle ***matches, long *numMatches );
	
	//new to Illustrator 9.0
	/* Get the art matching the given criteria and on the given layer list. */
	AIAPI AIErr (*GetSelectedArtFromLayerList) ( AILayerList list, AIArtHandle ***matches,
			long *numMatches );
	AIAPI AIErr (*GetMatchingArtFromLayerList) ( AILayerList list, AIMatchingArtSpec *specs,
			short numSpecs, AIArtHandle ***matches, long *numMatches );

} AI90MatchingArtSuite;


#include "AIHeaderEnd.h"

#endif
