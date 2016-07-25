/*
 *        Name:	AI90Pathfinder.h
 *     Purpose:	Adobe Illustrator 9.0 Pathfinder Suite.
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

#ifndef __AI90Pathfinder__
#define __AI90Pathfinder__

/*******************************************************************************
 **
 **	Imports
 **
 **/

#include "AIPathfinder.h"

#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAI90PathfinderSuite		kAIPathfinderSuite
#define kAIPathfinderSuiteVersion3	AIAPI_VERSION(3)
#define kAI90PathfinderSuiteVersion	kAIPathfinderSuiteVersion3
#define kAI90PathfinderVersion		kAI90PathfinderSuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/

typedef struct {

	AIAPI AIErr (*DoUniteEffect) ( AIPathfinderData *data, AIFilterMessage *message );
	AIAPI AIErr (*DoIntersectEffect) ( AIPathfinderData *data, AIFilterMessage *message );
	AIAPI AIErr (*DoExcludeEffect) ( AIPathfinderData *data, AIFilterMessage *message );
	AIAPI AIErr (*DoBackMinusFrontEffect) ( AIPathfinderData *data, AIFilterMessage *message );
	AIAPI AIErr (*DoFrontMinusBackEffect) ( AIPathfinderData *data, AIFilterMessage *message );
	AIAPI AIErr (*DoDivideEffect) ( AIPathfinderData *data, AIFilterMessage *message );
	AIAPI AIErr (*DoOutlineEffect) ( AIPathfinderData *data, AIFilterMessage *message );
	AIAPI AIErr (*DoTrimEffect) ( AIPathfinderData *data, AIFilterMessage *message );
	AIAPI AIErr (*DoMergeEffect) ( AIPathfinderData *data, AIFilterMessage *message );
	AIAPI AIErr (*DoCropEffect) ( AIPathfinderData *data, AIFilterMessage *message );
	AIAPI AIErr (*DoHardEffect) ( AIPathfinderData *data, AIFilterMessage *message );
	AIAPI AIErr (*DoSoftEffect) ( AIPathfinderData *data, AIFilterMessage *message );
	AIAPI AIErr (*DoTrapEffect) ( AIPathfinderData *data, AIFilterMessage *message );

	AIAPI AIErr (*GetHardEffectParameters) ( AIPathfinderData *data, AIFilterMessage *message );
	AIAPI AIErr (*GetSoftEffectParameters) ( AIPathfinderData *data, AIFilterMessage *message );
	AIAPI AIErr (*GetTrapEffectParameters) ( AIPathfinderData *data, AIFilterMessage *message );
	AIAPI AIErr (*GetGlobalOptions) ( AIPathfinderData *data, AIFilterMessage *message );

} AI90PathfinderSuite;


#include "AIHeaderEnd.h"

#endif
