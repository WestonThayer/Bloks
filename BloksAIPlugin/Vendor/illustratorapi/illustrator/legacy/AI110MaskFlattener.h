#ifndef __AI110MaskFlattener__
#define __AI110MaskFlattener__

/*
 *        Name:	AI110MaskFlattener.h
 *   $Revision: 1 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 11.0 Mask Flattener Suite.
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
#ifndef __AIMaskFlattener__
#include "AIMaskFlattener.h"
#endif


#include "AIHeaderBegin.h"

/** @file AI110MaskFlattener.h */

/*******************************************************************************
 **
 **	Suite name and version
 **
 **/

#define kAIMaskFlattenerSuite					"AI Mask Flattener Suite"
#define kAIMaskFlattenerSuiteVersion2			AIAPI_VERSION(2)
#define kAI110MaskFlattenerSuiteVersion			kAIMaskFlattenerSuiteVersion2

/*******************************************************************************
 **
 **	Suite
 **
 **/

/**
	The transparency flattening APIs provide facilities for flattening
	transparent artwork into an equivalent collection of opaque artwork.
 */
typedef struct {

	AIAPI AIErr (*FlattenArt)(AIArtSet artSet, AIFlatteningOptions *options, short paintOrder, AIArtHandle prep);
	AIAPI AIErr (*CreateTemporaryFlatteningLayer)(AILayerHandle *layer);
	AIAPI AIErr (*FlattenDocumentToLayer)(AILayerHandle layer);
	AIAPI AIErr (*RemoveTemporaryFlatteningLayer)();
	AIAPI AIErr (*IsTemporaryFlatteningLayer)(AILayerHandle layer, AIBoolean *flattening);
	AIAPI AIErr (*ReportError)(AIErr error);
	AIAPI AIErr (*CollectDocumentFlatteningInfo)(AIFlatteningInfoReceiver receiver, void* receiverdata);
	
} AI110MaskFlattenerSuite;


#include "AIHeaderEnd.h"


#endif
