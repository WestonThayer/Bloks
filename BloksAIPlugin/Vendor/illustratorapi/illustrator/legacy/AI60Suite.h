#ifndef __AI60Suite__
#define __AI60Suite__

/*
 *        Name:	AISuite.h
 *   $Revision: 3 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 6.0 Function Suites.
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

#ifndef __AI60Plugin__
#include "AI60Plugin.h"
#endif

#ifndef __AI60Basic__
#include "AI60Basic.h"
#endif


#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI60SuiteSuite			"AI Suite Suite"
#define kAI60SuiteSuiteVersion	AIAPI_VERSION(3)
#define kAI60SuiteVersion		kAI60SuiteSuiteVersion

#define kLatestInternalVersion	0

#define kSuiteAlreadyExistsErr			'STE='
#define kBadSuiteNameErr				'STNM'
#define kBadSuiteAPIVersionErr			'STAP'
#define kBadSuiteInternalVersionErr		'STIN'


/*******************************************************************************
 **
 **	Types
 **
 **/

typedef struct _t_AISuiteOpaque *AISuiteHandle;


/*******************************************************************************
 **
 ** Suite
 **
 **/

typedef struct {

	AIAPI AIErr (*AcquireSuite) ( char *name, long apiVersion,
				long internalVersion, void **suiteProcs );
	AIAPI AIErr (*ReleaseSuite) ( void *suiteProcs );

	AIAPI AIErr (*AddSuite) ( AIPluginHandle self, char *name, long apiVersion,
				long internalVersion, void *suiteProcs, AISuiteHandle *suite );
	AIAPI AIErr (*GetSuite) ( char *name, long apiVersion,
				long internalVersion, AISuiteHandle *suite );
	AIAPI AIErr (*GetSuiteName) ( AISuiteHandle suite, char **name );
	AIAPI AIErr (*GetSuiteAPIVersion) ( AISuiteHandle suite, long *apiVersion );
	AIAPI AIErr (*GetSuiteInternalVersion) ( AISuiteHandle suite, long *internalVersion );
	AIAPI AIErr (*GetSuiteProcs) ( AISuiteHandle suite, void **suiteProcs );
	AIAPI AIErr (*GetSuiteAcquireCount) ( AISuiteHandle suite, long *acquireCount );
	AIAPI AIErr (*GetSuitePlugin) ( AISuiteHandle suite, AIPluginHandle *plugin );

	AIAPI AIErr (*CountSuites) ( long *count );
	AIAPI AIErr (*GetNthSuite) ( long n, AISuiteHandle *suite );

	AIAPI AIErr (*Undefined) ( void );
	
} AISuiteSuite;


#include "AIHeaderEnd.h"


#endif
