#ifndef __AI110UID__
#define __AI110UID__

/*
 *        Name:	AI110UID.h
 *		$Id $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 11.0 Unique ID Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2003-2007 Adobe Systems Incorporated.
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

/** @file AI110UID.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI110UIDPoolSuite						kAIUIDPoolSuite
#define kAIUIDPoolSuiteVersion1					AIAPI_VERSION(2)
#define kAI110UIDPoolSuiteVersion				kAIUIDPoolSuiteVersion1
#define kAI110UIDPoolVersion					kAI110UIDPoolSuiteVersion

#define kAI110UIDSuite							kAIUIDSuite
#define kAIUIDSuiteVersion2						AIAPI_VERSION(3)
#define kAI110UIDSuiteVersion					kAIUIDSuiteVersion2
#define kAI110UIDVersion						kAI110UIDSuiteVersion

#define kAI110UIDREFSuite						kAIUIDREFSuite
#define kAIUIDREFSuiteVersion2					AIAPI_VERSION(3)
#define kAI110UIDREFSuiteVersion				kAIUIDREFSuiteVersion2
#define kAI110UIDREFVersion						kAI110UIDREFSuiteVersion

#define kAI110UIDUtilsSuite						kAIUIDUtilsSuite
#define kAIUIDUtilsSuiteVersion4				AIAPI_VERSION(4)
#define kAI110UIDUtilsSuiteVersion				kAIUIDUtilsSuiteVersion4
#define kAI110UIDUtilsVersion					kAI110UIDUtilsSuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/


/**
	The unique id suites provide facilities for creating, querying and
	managing unique ids and references to those ids.

	A unique id is an object that can be stored in a container such as
	a dictionary or an array. Given a unique id it is possible to find
	its container. One particularly useful place to store a unique id is
	in the dictionary of an art object. Given such an id it is possible
	to find the associated art object. In fact art object names are
	ultimately stored as specially encoded unique ids in their associated
	art object dictionaries.

	Unique ids have three important properties. 1) Each id is unique within
	a given pool of ids. 2) Each id has a name which is also unique within
	that pool. 3) Each id can be stored in at most one container. 
	
	AIUIDRef:

	Unique ids are subclasses of container entries. This allows
	them to be stored within dictionaries and arrays. The AIEntry suite
	provides methods to convert between AIEntryRef and AIUIDRef. A unique id
	may not be put into more than one container or more than once in a single
	container. Any attempt to do so will result in the error kUIDNotUnique.

	AIUIDREFRef:

	A reference to a unique id. Unique id references are subclasses of container
	entries. This allows them to be stored within dictionaries and arrays. The
	AIEntry suite provides methods to convert between AIEntryRef and AIUID.
 */

typedef struct AI110UIDPoolSuite {

	// reference count maintenance.
	AIAPI ASInt32 (*AddRef) ( void* pool );
	AIAPI ASInt32 (*Release) ( void* pool );

	/** Get a name pool by its name. At present there is a single pool for
	XML unique id names. This pool is returned regardless of the name
	supplied. */
	AIAPI AIErr (*GetPool) ( const char* name, AINamePoolRef* pool );

	/** Make a new unique id with the given name from the pool. If no name is
	specified then the pool will manufacture a name which is guaranteed
	not to be in use. If the name is specified then it must conform to the
	syntax imposed by the pool and must not be in use. UIDs are reference
	counted. */
	AIAPI AIErr (*NewUID) ( AINamePoolRef pool, const char* name, AIUIDRef* uid );

	/** Make a new reference to the unique id in the pool with the given name.
	If no name is specified then the pool will manufacture a name which is
	guaranteed not to be in use. If the name is specified then it must conform to
	the syntax imposed by the pool and must either not be in use of must be
	in use as a name for a UID or UIDREF. UIDREFs are reference counted. */
	AIAPI AIErr (*NewUIDREF) ( AINamePoolRef pool, const char* name, AIUIDREFRef* uidref );

	/** Make a new unique id based on the given name from the pool. A name that is
	guaranteed to be unique is automatically generated from the base name. If
	the base name is specified then it must conform to the syntax imposed by the
	pool. UIDs are reference counted. */
	AIAPI AIErr (*NewUIDFromBase) ( AINamePoolRef pool, const char* base, AIUIDRef* uid );

} AI110UIDPoolSuite;

/**
	APIs for working with unique ids.
*/
typedef struct AI110UIDSuite {

	// reference count maintenance.
	AIAPI ASInt32 (*AddRef) ( void* uid );
	AIAPI ASInt32 (*Release) ( void* uid );

	/** Returns true if the UID is currently stored within some container */
	AIAPI AIBoolean (*IsInUse) ( AIUIDRef uid );

	/** Returns the pool to which the uid's name belongs. The result is NULL if the
	uid is not valid. */
	AIAPI void (*GetPool) ( AIUIDRef uid, AINamePoolRef* pool );

	/** Returns the name of the uid. The result is NULL if the uid is not valid. */
	AIAPI const char* (*GetName) ( AIUIDRef uid );

	/** Get an entry for the container in which the uid is currently
	stored. A NULL reference is returned if the uid is not stored
	in a container. */
	AIAPI AIEntryRef (*GetContainer) ( AIUIDRef uid );

	/** Make a new reference to the unique id. UIDREFs are reference counted. */
	AIAPI AIErr (*NewUIDREF) ( AIUIDRef uid, AIUIDREFRef* ruidref );

} AI110UIDSuite;


/**
	APIs for working with references to unique ids.
*/
typedef struct AI110UIDREFSuite {

	// reference count maintenance.
	AIAPI ASInt32 (*AddRef) ( void* uidref );
	AIAPI ASInt32 (*Release) ( void* uidref );

	/** Returns true if the UIDREF is currently stored within some container */
	AIAPI AIBoolean (*IsInUse) ( AIUIDREFRef uidref );

	/** Returns the pool to which the UIDREF's name belongs. The result is NULL if the
	UIDREF is not valid. */
	AIAPI void (*GetPool) ( AIUIDREFRef uidref, AINamePoolRef* pool );

	/** Returns the name of the UIDREF. The result is NULL if the UIDREF is not valid. */
	AIAPI const char* (*GetName) ( AIUIDREFRef uidref );

	/** Get an entry for the container in which the UIDREF is currently
	stored. A NULL reference is returned if the UIDREF is not stored
	in a container. */
	AIAPI AIEntryRef (*GetContainer) ( AIUIDREFRef uidref );

	/** Get the unique id referred to. NULL if there is none. */
	AIAPI void (*GetUID) ( AIUIDREFRef uidref, AIUIDRef* uid );

} AI110UIDREFSuite;


/**
	convenience APIs for working with art object UIDs.
*/
typedef struct AI110UIDUtilsSuite {

	/** Get the unique id of the art object. If the object has no UID and create
		is TRUE then a machine generated UID will be assigned to the object. */
	AIAPI AIErr (*GetArtUID) ( AIArtHandle art, AIBoolean create, AIUIDRef* uid );
	/** Set the unique id of the art object replacing its current id if any. */
	AIAPI AIErr (*SetArtUID) ( AIArtHandle art, AIUIDRef uid );
	/** Transfer the id from the source to the destination object. The id
		of the source art is set to NULL. */
	AIAPI AIErr (*TransferArtUID) ( AIArtHandle srcart, AIArtHandle dstart );

	/** Get a new UIDREF for the art object. The object will be assigned a uid if
		it does not already have one. */
	AIAPI AIErr (*NewArtUIDREF) ( AIArtHandle art, AIUIDREFRef* uidref );
	/** Get the art object referenced by the UIDREF. If the UIDREF is associated
		with a text story (sequence of linked text frames) then the first frame
		of the story is returned. */
	AIAPI AIErr (*GetReferencedArt) ( AIUIDREFRef uidref, AIArtHandle* art );

	/** Get the UID name of the art object. An empty string indicates no id
		is assigned. */
	AIAPI AIErr (*GetArtUIDName) ( AIArtHandle art, char* buffer, ASInt32 bufsize );
	/** Set the UID name of the art object. Returns an error if the id is
		already in use. */
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

	/** Get the unique id of the story associated with the art object. The
		object must be of type AIArtType::kTextFrameArt. If the story has no
		UID and create is TRUE then a machine generated UID will be assigned
		to the story. */
	AIAPI AIErr (*GetStoryUID) (AIArtHandle art, AIBoolean create, AIUIDRef* ruid);
	/** Set the unique id of the story associated with the art object. The
		object must be of type AIArtType::kTextFrameArt. */
	AIAPI AIErr (*SetStoryUID) ( AIArtHandle art, AIUIDRef uid );
	/** Transfer the id from the story of the source object to the story of
		the destination object. The id of the source story is set to null. */
	AIAPI AIErr (*TransferStoryUID) ( AIArtHandle srcart, AIArtHandle dstart );
	/** Get a new UIDREF for the story associated with the art object. The
		art object must be of type AIArtType::kTextFrameArt. When the UID
		reference is passed to GetReferencedArt() it will return the first
		frame of the story no matter which frame was used to create the
		reference. */
	AIAPI AIErr (*NewStoryUIDREF) ( AIArtHandle art, AIUIDREFRef* uidref );

	/** Transfer the unique id of the story associated with the text frame
		to the art object. Any type of art object may be supplied including
		a text frame. After the transfer the story will no longer have an id. */
	AIAPI AIErr (*TransferStoryUIDToArt) ( AIArtHandle frame, AIArtHandle art );
	/** Transfer the unique id of the art object to the story associated with
		the text frame. Any type of art object can be supplied including a
		text fame. After the transfer the story will no longer have an id. */
	AIAPI AIErr (*TransferArtUIDToStory) ( AIArtHandle art, AIArtHandle frame );

} AI110UIDUtilsSuite;

#include "AIHeaderEnd.h"


#endif
