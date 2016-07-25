#ifndef __AI100MaskFlattener__
#define __AI100MaskFlattener__

/*
 *        Name:	AI100MaskFlattener.h
 *   $Revision: 1 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 10.0 Mask Flattener Suite.
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

/**
	@defgroup AI100MaskFlattenerAPI Transparency Flattening APIs
	
	The transparency flattening APIs provide facilities for flattening
	transparent artwork into an equivalent collection of opaque artwork.

	@{
 */

/*******************************************************************************
 **
 **	Suite name and version
 **
 **/

#define kAI100MaskFlattenerSuite				kAIMaskFlattenerSuite
#define kAIMaskFlattenerSuiteVersion1			AIAPI_VERSION(1)
#define kAI100MaskFlattenerSuiteVersion			kAIMaskFlattenerSuiteVersion1

/*******************************************************************************
 **
 **	Constants
 **
 **/


/*******************************************************************************
 **
 **	Types
 **
 **/

/** Linked EPS object -- indicates that a linked EPS was drawn as a part of
	the artwork to be flattened. Provides the handle to the linked EPS object and a
	boolean indicating whether or not the linked EPS interracts with transparency.
	A linked EPS which does not interract with transparency can be passed
	through to a PostScript device for printing purposes. One which does
	interract needs to be parsed into objects for correct printing.
	
	Since a linked EPS is a placed object a receiver will be sent both this
	snippet and the AIFlatteningInfoPlacedArtObject snippet. The order in
	which these will be sent is not guaranteed. In fact all linked EPS
	snippets will usually be sent as a group at the end. */
typedef struct
{
	AIArtHandle object;
	AIBoolean interacts;
} AI100FlatteningInfoLinkedEPSObject;

/** Placed object -- indicates that a placed object was drawn as a part of
	the artwork to be flattened. */
typedef struct
{
	AIArtHandle object;
} AI100FlatteningInfoPlacedArtObject;

/** The information packet sent to an AIFlatteningInfoReceiver. */
typedef struct
{
	/** Indicates the type of information being sent. */
	AIFlatteningInfoType what;
	/** Contains the information. The valid member is determined based on
		the type of information. */
	union
	{
		AI100FlatteningInfoLinkedEPSObject linkedEPSObject;
		AI100FlatteningInfoPlacedArtObject placedArtObject;
	} x;
} AI100FlatteningInfoSnippet;

/** Prototype for a receiver of flattening information. */
typedef AIErr (*AI100FlatteningInfoReceiver) (void* receiverdata, AI100FlatteningInfoSnippet* snippet);


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** AIMaskFlattenerSuite */
typedef struct {

	AIAPI AIErr (*FlattenArt)(AIArtSet artSet, AIFlatteningOptions *options, short paintOrder, AIArtHandle prep);
	AIAPI AIErr (*CreateTemporaryFlatteningLayer)(AILayerHandle *layer);
	AIAPI AIErr (*FlattenDocumentToLayer)(AILayerHandle layer);
	AIAPI AIErr (*RemoveTemporaryFlatteningLayer)();
	AIAPI AIErr (*IsTemporaryFlatteningLayer)(AILayerHandle layer, AIBoolean *flattening);
	AIAPI AIErr (*ReportError)(AIErr error);

	AIAPI AIErr (*CollectDocumentFlatteningInfo)(AI100FlatteningInfoReceiver receiver, void* receiverdata);

} AI100MaskFlattenerSuite;

/**
	@}
 */


#include "AIHeaderEnd.h"


#endif
