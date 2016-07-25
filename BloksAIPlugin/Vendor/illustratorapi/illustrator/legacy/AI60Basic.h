#ifndef __AI60Basic__
#define __AI60Basic__

/*
 *        Name:	AIBasic.h
 *   $Revision: 2 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 6.0 Basic Suite.
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

#ifndef __AITypes__
#include "AITypes.h"
#endif


#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI60BasicSuite		"AI Basic Suite"
#define kAI60BasicSuiteVersion	AIAPI_VERSION(2)
#define kAI60BasicVersion		kAI60BasicSuiteVersion

#define kSuiteNotFoundErr	'STE?'


/*******************************************************************************
 **
 **	Suite
 **
 **/

typedef struct {

	AIAPI AIErr (*AcquireSuite) ( char *name, long version, void **suiteProcs );
	AIAPI AIErr (*ReleaseSuite) ( void *suiteProcs );

} AIBasicSuite;


#include "AIHeaderEnd.h"


#endif
