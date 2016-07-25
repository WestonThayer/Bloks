#ifndef __AI110Runtime__
#define __AI110Runtime__

/*
 *        Name:	AIRuntime.h
 *   $Revision: 11 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 10.0 Runtime Environment.
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

/** @file AI11.0Runtime.h */

/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAI110RuntimeSuite		"AI Runtime Suite"
#define kAIRuntimeSuiteVersion4	AIAPI_VERSION(4)
#define kAIRuntimeSuiteVersion5	AIAPI_VERSION(5)
#define kAIRuntimeSuiteVersion6	AIAPI_VERSION(6)
#define kAIRuntimeSuiteVersion7	AIAPI_VERSION(7)
#define kAI110RuntimeSuiteVersion	kAIRuntimeSuiteVersion7
#define kAI110RuntimeVersion		kAI110RuntimeSuiteVersion

/*******************************************************************************
 **
 **	Types
 **
 **/

typedef char *AI110AppName;
typedef char *AI110AppVersion;
typedef char *AI110UserName;
typedef char *AI110UserOrganization;
typedef char *AI110UserSerialNumber;


/*******************************************************************************
 **
 **	Suite
 **
 **/

typedef struct {

	AIAPI AIErr (*GetAppName) ( AI110AppName *name );
	AIAPI AIErr (*GetAppVersion) ( AI110AppVersion *version );

	AIAPI AIErr (*GetUserName) ( AI110UserName *name );
	AIAPI AIErr (*GetUserOrganization) ( AI110UserOrganization *organization );
	AIAPI AIErr (*GetUserSerialNumber) ( AI110UserSerialNumber *serialNumber );

	AIAPI AIErr (*GetAppNameSpace) ( AINameSpace **space );
	AIAPI AIErr (*GetAppStringPool) ( AIStringPool **pool );

} AIRuntimeSuite4;

typedef struct {

	AIAPI AIErr (*GetAppName) ( AI110AppName *name );
	AIAPI AIErr (*GetAppVersion) ( AI110AppVersion *version );

	AIAPI AIErr (*GetUserName) ( AI110UserName *name );
	AIAPI AIErr (*GetUserOrganization) ( AI110UserOrganization *organization );
	AIAPI AIErr (*GetUserSerialNumber) ( AI110UserSerialNumber *serialNumber );

	AIAPI AIErr (*GetAppNameSpace) ( AINameSpace **space );
	AIAPI AIErr (*GetAppStringPool) ( AIStringPool **pool );

	AIAPI long (*GetAppFreeMem) ( void );

} AIRuntimeSuite5;

typedef struct {

	AIAPI AIErr (*GetAppName) ( AI110AppName *name );
	AIAPI AIErr (*GetAppVersion) ( AI110AppVersion *version );

	AIAPI AIErr (*GetUserName) ( AI110UserName *name );
	AIAPI AIErr (*GetUserOrganization) ( AI110UserOrganization *organization );
	AIAPI AIErr (*GetUserSerialNumber) ( AI110UserSerialNumber *serialNumber );

	AIAPI AIErr (*GetAppNameSpace) ( AINameSpace **space );
	AIAPI AIErr (*GetAppStringPool) ( AIStringPool **pool );

	/**
		 GetAppFreeMem will always return the amount of physical RAM on the machine.
		 If really doesn't make a lot of sense on virtual memory systems.
		 Most clients calling this are trying to get an upper bound on how much
		 memory they can use. The amount of physical RAM is as good a value as any.
	*/
	AIAPI long (*GetAppFreeMem) ( void );

	AIAPI AIErr (*ShowAppAboutBox) ( void );

} AIRuntimeSuite6;

struct AI110RuntimeSuite {

	/** You can use the application name to verify that your plug–in is running in a
		supported host application. You may also use the name and serial number to
		key your plug–in to an installed application. You should not modify the
		string returned by GetAppName. */
	AIAPI AIErr (*GetAppName) ( AI110AppName *name );
	/** Get the version number string of the host application running the plug–in.
		(AIAppVersion is a char *). While ideally all versions of the same host
		application supporting a suite would have identical behavior, it is possible
		that subtle differences will occur. A plug–in needing to special case its
		behavior should be able to rely on the argument returned by this call. 
		This call has been removed in AI12 and replaced with GetAppMajorVersion, 
		GetAppMinorVersion and GetAppRevisionVersion */
	AIAPI AIErr (*GetAppVersion) ( AI110AppVersion *version );

	/** When Illustrator is first installed it asks for a user name, organization, and
		serial number. This function returns a pointer to the registered user's name
		(a C string). You should not modify the string returned by GetUserName() */
	AIAPI AIErr (*GetUserName) ( AI110UserName *name );
	/** When Illustrator is first installed it asks for a user name, organization, and
		serial number. This function returns a pointer to the registered user's organization
		(a C string). You should not modify the string returned by GetUserOrganization(). */
	AIAPI AIErr (*GetUserOrganization) ( AI110UserOrganization *organization );
	/** When Illustrator is first installed it asks for a user name, organization, and
		serial number. This function returns a pointer to the registered user's application
		serial number (as a C string). You should not modify the string
		returned by GetUserSerialNumber(). */
	AIAPI AIErr (*GetUserSerialNumber) ( AI110UserSerialNumber *serialNumber );

	/** While a plug–in can create it's own name space in which it can store arbitrary
		data, it can also access the application's name space. Among other
		things, the application keeps its preferences here. Your plug–in should probably
		not modify the application's existing name space data directly, but it
		can create new data within it for some reason. */
	AIAPI AIErr (*GetAppNameSpace) ( AINameSpace **space );
	/** While a plug–in can create it's own string pool in which it can store and
		compare strings, it can also access the application's pool. The runtime data
		for a host is actually stored in this string pool and string pointers returned
		by the runtime suite functions are from the string pool. */
	AIAPI AIErr (*GetAppStringPool) ( AIStringPool **pool );

	/**	 GetAppFreeMem will always return the amount of physical RAM on the machine.
		 If really doesn't make a lot of sense on virtual memory systems.
		 Most clients calling this are trying to get an upper bound on how much
		 memory they can use. The amount of physical RAM is as good a value as any. */
	AIAPI long (*GetAppFreeMem) ( void );

	/** Show the about box. */
	AIAPI AIErr (*ShowAppAboutBox) ( void );
	
	/** Get the version of the OS the application is running on. See #AISystemOSVersion. */
	AIAPI long (*GetSystemVersion) ( void );
	/** True if the OS is Mac OS X. */
	AIAPI AIBoolean (*GetIsSystemMacOSX) ( void );
};


#include "AIHeaderEnd.h"


#endif
