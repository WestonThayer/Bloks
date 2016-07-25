/*
 *        Name:	AI5xAPISupport.h
 *   $Revision: 1 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 6.0 Artwork Object Suite.
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

#ifndef __AI5xAPISupport__
#define __AI5xAPISupport__

#ifndef __AITypes__
#include "AITypes.h"
#endif

#include "AIHeaderBegin.h"



/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI5xAPISupportSuite		"AI 5x API Support Suite"
#define kAI5xAPISupportSuiteVersion	AIAPI_VERSION(2)



/*******************************************************************************
 **
 **	Suite
 **
 **/

typedef struct {

	AIAPI AIErr (*Get5xFunctions) ( ISAType architecture, const void **AI5xFunctions);

} AI5xAPISupportSuite;

#include "AIHeaderEnd.h"


#endif
