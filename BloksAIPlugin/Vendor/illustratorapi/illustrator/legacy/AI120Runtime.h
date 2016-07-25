#ifndef __AI120Runtime__
#define __AI120Runtime__

/*
 *        Name:	AI120Runtime.h
 *     Purpose:	Adobe Illustrator Runtime Environment.
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

#include "AIRuntime.h"

#include "AIHeaderBegin.h"

/** @file AI120Runtime.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAI120RuntimeSuite			kAIRuntimeSuite
#define kAIRuntimeSuiteVersion8		AIAPI_VERSION(8)
#define kAI120RuntimeSuiteVersion	kAIRuntimeSuiteVersion8

/*******************************************************************************
 **
 **	Suite
 **
 **/

struct AI120RuntimeSuite {

	AIAPI AIErr (*GetAppName) ( AIAppName *name );
	AIAPI AIErr (*GetAppFileSpecification) ( ai::FilePath &file );
	AIAPI AIErr (*GetUserName) ( AIUserName *name );
	AIAPI AIErr (*GetUserOrganization) ( AIUserOrganization *organization );
	AIAPI AIErr (*GetUserSerialNumber) ( AIUserSerialNumber *serialNumber );
	AIAPI AIErr (*GetAppNameSpace) ( AINameSpace **space );
	AIAPI AIErr (*GetAppStringPool) ( AIStringPool **pool );
	AIAPI ASInt32 (*GetAppFreeMem) ( void );
	AIAPI AIErr (*ShowAppAboutBox) ( void );
	AIAPI ASInt32 (*GetSystemVersion) ( void );
	AIAPI AIBoolean (*GetIsSystemMacOSX) ( void );
	AIAPI ASInt32 (*GetAppMajorVersion) ( void );
	AIAPI ASInt32 (*GetAppMinorVersion) ( void );
	AIAPI ASInt32 (*GetAppRevisionVersion) ( void );
	AIAPI AIErr (*GetAppNameUS) ( ai::UnicodeString& name );
	AIAPI AIErr (*GetUserNameUS) ( ai::UnicodeString& name );
	AIAPI AIErr (*GetUserOrganizationUS) ( ai::UnicodeString& organization );
	AIAPI AIErr (*GetDefaultScript) ( AIFaceScript *script);
	AIAPI AIBoolean (*GetIsHonestyBuild) ( void );
	AIAPI AIBoolean (*GetIsProductTryAndDie) ( void );
};


#include "AIHeaderEnd.h"

#endif  // __AI120Runtime__
