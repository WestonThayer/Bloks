#ifndef __AI90Context__
#define __AI90Context__

/*
 *        Name:	AI90Context.h
 *   $Revision: 1 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 6.0-9.0 Runtime Context Environment.
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

#ifndef __AIContext__
#include "AIContext.h"
#endif


#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAI90AppContextSuite		"AI Context Suite"
#define kAIAppContextSuiteVersion2	AIAPI_VERSION(2)
#define kAI90AppContextVersion		kAIAppContextSuiteVersion2


/*******************************************************************************
 **
 **	Suite
 **
 **/

typedef struct {

	AIAPI AIErr (*GetPlatformAppWindow) ( AIWindowRef *appWindow );

	AIAPI AIErr (*PushAppContext) ( SPPluginRef plugin, AIAppContextHandle *appContext );
	AIAPI AIErr (*PopAppContext) ( AIAppContextHandle appContext );

	AIAPI AIErr (*MacGetAppQDGlobal) ( void **appQD );

} AI90AppContextSuite;


#include "AIHeaderEnd.h"


#endif
