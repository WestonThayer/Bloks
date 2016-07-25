#ifndef __AI100UID__
#define __AI100UID__

/*
 *        Name:	AI100UID.h
 *		$Id $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 10.0 Unique ID Suite.
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

#include "AIUID.h"


#include "AIHeaderBegin.h"

/** @file AI100UID.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI100UIDUtilsSuite						kAIUIDUtilsSuite
#define kAIUIDUtilsSuiteVersion1				AIAPI_VERSION(3)
#define kAI100UIDUtilsSuiteVersion				kAIUIDUtilsSuiteVersion1


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
	convenience APIs for working with art object UIDs.
*/
typedef struct AI100UIDUtilsSuite {

	/** Get the unique id of the art object. If the object has no UID and create
	is TRUE then a machine generated UID will be assigned to the object. */
	AIAPI AIErr (*GetArtUID) ( AIArtHandle art, AIBoolean create, AIUIDRef* uid );
	/** Set the unique id of the art object replacing its current id if any. */
	AIAPI AIErr (*SetArtUID) ( AIArtHandle art, AIUIDRef uid );
	/** Transfer the id from the source to the destination object */
	AIAPI AIErr (*TransferArtUID) ( AIArtHandle srcart, AIArtHandle dstart );

	/** Get a new UIDREF for the art object. The object will be assigned a uid if
	it does not already have one. */
	AIAPI AIErr (*NewArtUIDREF) ( AIArtHandle art, AIUIDREFRef* uidref );
	/** Get the art object referenced by the UIDREF. */
	AIAPI AIErr (*GetReferencedArt) ( AIUIDREFRef uidref, AIArtHandle* art );

	/** Get the UID name of the art object. An empty string indicates no id
	is assigned. */
	AIAPI AIErr (*GetArtUIDName) ( AIArtHandle art, char* buffer, ASInt32 bufsize );
	/** Set the UID name of the art object. If makeUnique is true then a
	unique id will be manufactured from the name if necessary. */
	AIAPI AIErr (*SetArtUIDName) ( AIArtHandle art, const char* buffer );

	/** Get the name or XML ID of the art object depending on the setting of
	the user preference. isDefaultName may be nil, if not then it is set
	to true if the art object has no name or id and consequently the default
	name for the art was returned. */
	AIAPI AIErr (*GetArtNameOrUID) ( AIArtHandle art, char* buffer, ASInt32 bufsize, ASBoolean* isDefaultName );
	/** Set the name or XML ID of the art object depending on the setting of
	the user preference. Note that names are converted to valid XML IDs
	and then used to specify the XML ID of the object. */
	AIAPI AIErr (*SetArtNameOrUID) ( AIArtHandle art, const char* buffer );

	/** Manufacture a UID based on an existing UID */
	AIAPI AIErr (*MakeUIDFromBase) ( AIUIDRef base, AIUIDRef* uid );
	/** Manufacture a unique name from a base name */
	AIAPI AIErr (*MakeUniqueNameFromBase) ( const char* base, char* buffer, ASInt32 bufsize );

} AI100UIDUtilsSuite;

#include "AIHeaderEnd.h"


#endif
