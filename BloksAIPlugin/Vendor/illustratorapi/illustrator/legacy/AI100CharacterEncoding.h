#ifndef __AI100CharacterEncoding__
#define __AI100CharacterEncoding__

/*
 *        Name:	AI100CharacterEncoding.h
 *		$Id $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 10.0 Character Encoding Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2001-2007 Adobe Systems Incorporated.
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

#include "AICharacterEncoding.h"

#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI100CharacterEncodingSuite				kAICharacterEncodingSuite
#define kAICharacterEncodingSuiteVersion1			AIAPI_VERSION(1)
#define kAI100CharacterEncodingSuiteVersion			kAICharacterEncodingSuiteVersion1


/*******************************************************************************
 **
 **	Suite
 **
 **/


typedef struct _AI100CharacterEncodingSuite {

	// Converts the contents of the source buffer from the source encoding to
	// the destination encoding. srcBuffer is assumed to contain srcLength bytes
	// of data. dstBuffer is assumed to be large enough to contain dstSize bytes
	// and dstLength returns the actual number of bytes of converted data.
	AIAPI AIErr (*ConvertBuffer) (
			const void* srcBuffer, long srcLength, AICharacterEncoding srcEncoding,
			void* dstBuffer, long dstSize, AICharacterEncoding dstEncoding,
			long* dstLength);

} AI100CharacterEncodingSuite;


#include "AIHeaderEnd.h"


#endif
