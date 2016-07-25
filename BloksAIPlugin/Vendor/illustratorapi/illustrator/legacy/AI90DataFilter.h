#ifndef __AI90DataFilter__
#define __AI90DataFilter__

/*
 *        Name:	AI90DataFilter.h
 *   $Revision: 6 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 9.0 Data Filter Suite.
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

#include "AIDataFilter.h"

#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI90DataFilterSuite				"AI Data Filter Suite"
#define kAIDataFilterSuiteVersion3		AIAPI_VERSION(3)
#define kAI90DataFilterVersion			kAIDataFilterSuiteVersion3


/*******************************************************************************
 **
 **	Suite
 **
 **/

/* Illustrator 9.0 Data Filter Suite */
typedef struct _AI90DataFilterSuite {

	AIAPI AIErr (*LinkDataFilter) ( AIDataFilter *prev, AIDataFilter *next );
	AIAPI AIErr (*UnlinkDataFilter) ( AIDataFilter *next, AIDataFilter **prev );
	AIAPI AIErr (*ReadDataFilter) ( AIDataFilter *filter, char *store, long *count );
	AIAPI AIErr (*WriteDataFilter) ( AIDataFilter *filter, char *store, long *count );
	AIAPI AIErr (*SeekDataFilter) ( AIDataFilter *filter, long *count );
	AIAPI AIErr (*MarkDataFilter) ( AIDataFilter *filter, long *count );
	AIAPI AIErr (*NewBufferDataFilter) ( long size, AIDataFilter **filter );
	AIAPI AIErr (*NewHexdecDataFilter) ( char *state, long shift, AIDataFilter **filter );
	AIAPI AIErr (*NewBlockDataFilter) ( void *address, long size, AIDataFilter **filter );

	// creates a random access data filter that reads and writes to Illustrator's
	// VM. this can be used to create a temporary file that is paged to and from
	// memory as needed. if initialsize is given then the initial VM stream is
	// created with that size causing the end of the stream to be set to that size.
	AIAPI AIErr (*NewVMDataFilter) ( long initialsize, AIDataFilter **filter );

	// creates an ASCII85 encode/decode data filter. statestr indicates
	// whether the filter is encoding or decoding according to whether
	// it is "write" or "read".
	AIAPI AIErr (*NewA85DataFilter) ( char *statestr, char* prefix, AIDataFilter **filter );

	// creates a ZLib compression/decompression data filter. statestr indicates
	// whether the filter is compressing or decompressing according to whether
	// it is "write" or "read".
	AIAPI AIErr (*NewZDataFilter) ( char *statestr, AIDataFilter **filter );

} AI90DataFilterSuite;


#include "AIHeaderEnd.h"


#endif
