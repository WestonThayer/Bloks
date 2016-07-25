#ifndef __AI110Array__
#define __AI110Array__

/*
 *        Name:	AI110Array.h
 *		$Id $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 11.0 Array Object Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1999-2007 Adobe Systems Incorporated.
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

#include "AIArray.h"

#include "AIHeaderBegin.h"

/** @file AI110Array.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/


#define kAI110ArraySuite					kAIArraySuite
#define kAIArraySuiteVersion3				AIAPI_VERSION(3)
#define kAI110ArraySuiteVersion				kAIArraySuiteVersion3
#define kAI110ArrayVersion					kAI110ArraySuiteVersion


// Array errors.

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
	An array is a heterogeneous container whose elements are accessed by
	sequential integer indices. Elements can be inserted into and removed
	from the array.

	The elements of an array are called entries and their type is an AIEntryRef.
	Entries can be of various types. There are simple types such as booleans,
	integers, floats, and strings and complex types such as other arrays,
	dictionaries and references to document objects including art objects,
	brushes and styles. This flexibility makes arrays a very flexible and
	poweful container. The AIEntry suite provides methods to construct and
	query entries of different types.

	Arrays can themselves be stored in other containers such as other arrays
	or dictionaries. In particular they can be stored in the dictionaries
	attached to art objects and to the document. When an array is stored in
	one of these places (directly or indirectly) it is read and written as
	a part of the document.

	@see AI110EntrySuite
 */
typedef struct {

	/**
		Create a brand new array. initial reference count is 1.
	*/
	AIAPI AIErr (*CreateArray) ( AIArrayRef* array );


	/**
		Arrays are reference counted. Call Release once you are done with
		an array to free its memory.
	*/
	AIAPI ASInt32 (*AddRef) ( AIArrayRef array );
	/**
		Arrays are reference counted. Call Release once you are done with
		an array to free its memory.
	*/
	AIAPI ASInt32 (*Release) ( AIArrayRef array );


	/**
		Make an exact duplicate of the source array. a deep copy is performed.
	*/
	AIAPI AIErr (*Clone) ( AIArrayRef src, AIArrayRef* dst );
	/**
		Make a copy of the source array replacing the current contents of the array
	*/
	AIAPI AIErr (*Copy) ( AIArrayRef array, AIArrayRef src );


	/**
		Get the size of the array
	*/
	AIAPI ASInt32 (*Size) ( AIArrayRef array );
	/**
		Remove the entry with the given index from the array
	*/
	AIAPI AIErr (*DeleteEntry) ( AIArrayRef array, ASInt32 i );
	/**
		Insert an entry into the array at the given index. the new entry is assigned
		an arbitrary initial value.
	*/
	AIAPI AIErr (*InsertEntry) ( AIArrayRef array, ASInt32 i );


	/**
		Get the type of an array entry
	*/
	AIAPI AIErr (*GetEntryType) ( AIArrayRef array, ASInt32 i, AIEntryType* type );


	/**
		Copy the entry at position1 of array1 to position2 of array2 inserting it
		into the array. the arrays need not be distinct.
	*/
	AIAPI AIErr (*CopyEntry) ( AIArrayRef array1, AIArrayRef array2, ASInt32 position1,
			ASInt32 position2 );
	/**
		Move the entry at position1 of array1 to position2 of array2 removing it
		from array1 and inserting it into array2. the arrays need not be distinct.
		the optional parameter newposition returns the position of the element in
		array2 after the move.
	*/
	AIAPI AIErr (*MoveEntry) ( AIArrayRef array1, AIArrayRef array2, ASInt32 position1,
			ASInt32 position2, ASInt32* newposition );
	/**
		Swap the entry at position1 of array1 with that at position2 in array2. the
		arrays need not be distinct.
	*/
	AIAPI AIErr (*SwapEntries) ( AIArrayRef array1, AIArrayRef array2, ASInt32 position1,
			ASInt32 position2 );


	/**
		Get an art entry
	*/
	AIAPI AIErr (*GetArtEntry) ( AIArrayRef array, ASInt32 i, AIArtHandle* art );
	/**
		Set the value of the entry to be a new art object of the specified type
	*/
	AIAPI AIErr (*NewArtEntry) ( AIArrayRef array, ASInt32 i, short type );


	/**
		Move the art object from the art tree into the array.
	*/
	AIAPI AIErr (*MoveArtToEntry) ( AIArrayRef array, ASInt32 i, AIArtHandle art );
	/**
		Move the art object from the art tree into the array. to remove the art object
		from the array the entry is not deleted but instead is set to an arbitrary value.
	*/
	AIAPI AIErr (*MoveEntryToArt) ( AIArrayRef array, ASInt32 i, short paintOrder,
			AIArtHandle prep, AIArtHandle* art );
	

	/**
		Copy the art object from the art tree into the dictionary.
	*/
	AIAPI AIErr (*CopyArtToEntry) ( AIArrayRef array, ASInt32 i, AIArtHandle art );
	/**
		Copy the art object from the dictionary into the art tree.
	*/
	AIAPI AIErr (*CopyEntryToArt) ( AIArrayRef array, ASInt32 i, short paintOrder,
			AIArtHandle prep, AIArtHandle* art );
	

	/**
		Set the entry of the dictionary to refer to the topmost group of the layer
	*/
	AIAPI AIErr (*SetEntryToLayer) ( AIArrayRef array, ASInt32 i, AILayerHandle layer );
	/**
		insert a new layer whose group is the dictionary entry which must be a group
	*/
	AIAPI AIErr (*SetLayerToEntry) ( AIArrayRef array, ASInt32 i, short paintOrder,
			AILayerHandle prep, AILayerHandle *layer );


	/**
		Get the entry at the given index. returns a nil entry if it does not exist.
	*/
	AIAPI AIEntryRef (*Get) ( AIArrayRef array, ASInt32 i );
	/**
		set the entry at the given index.
	*/
	AIAPI AIErr (*Set) ( AIArrayRef array, ASInt32 i, AIEntryRef entry );


	// the following are convenience APIs for getting and setting entries of the basic types

	/**
		Get boolean
	*/
	AIAPI AIErr (*GetBooleanEntry) ( AIArrayRef array, ASInt32 i, ASBoolean* value );
	/**
		Set boolean
	*/
	AIAPI AIErr (*SetBooleanEntry) ( AIArrayRef array, ASInt32 i, ASBoolean value );

	/**
		Get integer
	*/
	AIAPI AIErr (*GetIntegerEntry) ( AIArrayRef array, ASInt32 i, ASInt32* value );
	/**
		Set integer
	*/
	AIAPI AIErr (*SetIntegerEntry) ( AIArrayRef array, ASInt32 i, ASInt32 value );

	/**
		Get real
	*/
	AIAPI AIErr (*GetRealEntry) ( AIArrayRef array, ASInt32 i, AIReal* value );
	/**
		Set real
	*/
	AIAPI AIErr (*SetRealEntry) ( AIArrayRef array, ASInt32 i, AIReal value );

	/**
		Get string
	*/
	AIAPI AIErr (*GetStringEntry) ( AIArrayRef array, ASInt32 i, const char** value );
	/**
		Set string
	*/
	AIAPI AIErr (*SetStringEntry) ( AIArrayRef array, ASInt32 i, const char* value );

	/**
		Get binary
	*/
	AIAPI AIErr (*GetBinaryEntry) ( AIArrayRef array, ASInt32 i, void* value, ASInt32* size );
	/**
		Set binary
	*/
	AIAPI AIErr (*SetBinaryEntry) ( AIArrayRef array, ASInt32 i, void* value, ASInt32 size );

	/**
		Get dictionary
	*/
	AIAPI AIErr (*GetDictEntry) ( AIArrayRef array, ASInt32 i, AIDictionaryRef* value );
	/**
		Set dictionary
	*/
	AIAPI AIErr (*SetDictEntry) ( AIArrayRef array, ASInt32 i, AIDictionaryRef value );

	/**
		Get array
	*/
	AIAPI AIErr (*GetArrayEntry) ( AIArrayRef array, ASInt32 i, AIArrayRef* value );
	/**
		Set array
	*/
	AIAPI AIErr (*SetArrayEntry) ( AIArrayRef array, ASInt32 i, AIArrayRef value );

} AI110ArraySuite;

#include "AIHeaderEnd.h"


#endif
