#ifndef __AI100MatchingArt__
#define __AI100MatchingArt__

/*
 *        Name:	AIMatchingArt.h
 *   $Revision: 4 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator 10.0 Matching Art Suite.
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

#define kAI100MatchingArtSuite		kAIMatchingArtSuite
#define kAIMatchingArtSuiteVersion4	AIAPI_VERSION(4)
#define kAI100MatchingArtVersion	kAIMatchingArtSuiteVersion4


/*******************************************************************************
 **
 **	Suite
 **
 **/

typedef struct AI100MatchingArtSuite {

	/* Get the art matching the given criteria and on the current layer list. */
	AIAPI AIErr (*GetSelectedArt) ( AIArtHandle ***matches, long *numMatches );
	AIAPI AIErr (*GetMatchingArt) ( AIMatchingArtSpec *specs, short numSpecs,
			AIArtHandle ***matches, long *numMatches );

	// new to Illustrator 9.0
	/* Get the art matching the given criteria and on the given layer list. */
	AIAPI AIErr (*GetSelectedArtFromLayerList) ( AILayerList list, AIArtHandle ***matches,
			long *numMatches );
	AIAPI AIErr (*GetMatchingArtFromLayerList) ( AILayerList list, AIMatchingArtSpec *specs,
			short numSpecs, AIArtHandle ***matches, long *numMatches );

	// new to Illustrator 10.0
	/* Get the art used to determine the current path style, displayed in the color
	   palette. This is a convenience function, since the current path style is now
	   determined not just by the targeted or selected objects, but rather by a combination
	   of both. The art returned may include text runs as well as objects inside of
	   graphs. */
	AIAPI AIErr (*GetArtForCurrentPathStyle) ( AIArtHandle ***matches, long *numMatches );

	// This function can be used to avoid some setup if there is nothing selected
	AIAPI AIBoolean (*IsSomeArtSelected) ( void );
		/* Returns simply whether or not there are some art objects selected, in art editing mode.
			(If you want to know whether there is a text editing selection, call HasTextSelection
			in the AIText suite. IsArtSelected will return false when there is a text editing
			selection and when there is nothing selected at all.
		*/

	// Test searchArt and its descendants if it is a group or other container against the specs.
	// If the kMatchDictionaryArt flag is set, will also search the dictionaries of searchArt
	// and any of its descendants. This is useful for when only certain parts of the artwork
	// are of interest, or when the searchArt is not in the regular artwork, e.g., if it is the
	// definition art of a pattern, brush, or symbol.
	AIAPI AIErr (*GetMatchingArtFromArt) ( AIArtHandle searchArt, AIMatchingArtSpec *specs,
			short numSpecs, AIArtHandle ***matches, long *numMatches );

} AI100MatchingArtSuite;


#include "AIHeaderEnd.h"

#endif
