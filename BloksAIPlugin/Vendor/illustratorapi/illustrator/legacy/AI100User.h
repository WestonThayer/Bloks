#ifndef __AI100User__
#define __AI100User__

/*
 *        Name: AI100User.h
 *     Purpose: Adobe Illustrator 10.0 User Utilities Suite.	
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

#include "AIUser.h"

#include "AIHeaderBegin.h"

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI100UserSuite				kAIUserSuite
#define kAIUserSuiteVersion5		AIAPI_VERSION(5)
#define kAI100UserSuiteVersion		kAIUserSuiteVersion5

#define kAIUserSuiteVersion4		AIAPI_VERSION(4)


/*******************************************************************************
 **
 **	Suite
 **
 **/


typedef struct {

	AIAPI AIBoolean (*Cancel) ( void );
	AIAPI void (*UpdateProgress) ( long current, long max );
	AIAPI void (*SetProgressText) ( const char *text );
	AIAPI void (*CloseProgress) ( void );
	AIAPI void (*AIRealToString) ( AIReal value, short precision, unsigned char *string );
	AIAPI void (*StringToAIReal) ( unsigned char *string, AIReal *value );
	AIAPI void (*IUAIRealToString) ( AIReal value, short precision, unsigned char *string );
	AIAPI void (*IUStringToAIReal) ( unsigned char *string, AIReal *value );
	AIAPI void (*IUAIRealToStringUnits) ( AIReal value, unsigned char *string );
	AIAPI void (*IUStringUnitsToAIReal) ( unsigned char *string, AIReal *value );
	AIAPI AIErr (*GetUnitsString) ( short format, unsigned char *string );

	AIAPI AIErr (*AIUnitsToADMUnits) ( short aiUnits, ADMUnits *admUnits);
	AIAPI AIErr (*ADMUnitsToAIUnits) ( ADMUnits admUnits, short *aiUnits);
	AIAPI AIErr (*GetGlobalObjectDisplayName) ( char *name ); //name is modified in place
	
	/*Open the appropriate app to edit the object.  This is only meaningful for
	  Placed and Raster objects, and is equivalent to the user option-double-clicking
	  on the object with the selection tool.  See errors above.*/
	AIAPI AIErr (*EditInOriginalApp) ( AIArtHandle art );

	AIAPI AIErr (*AppIdle) ( void );

	AIAPI void (*DisableProgressCancel) ( void );

} AIUserSuite4;


typedef struct {

	AIAPI AIBoolean (*Cancel) ( void );
	AIAPI void (*UpdateProgress) ( long current, long max );
	AIAPI void (*SetProgressText) ( const char *text );
	AIAPI void (*CloseProgress) ( void );
	AIAPI void (*AIRealToString) ( AIReal value, short precision, unsigned char *string );
	AIAPI void (*StringToAIReal) ( unsigned char *string, AIReal *value );
	AIAPI void (*IUAIRealToString) ( AIReal value, short precision, unsigned char *string );
	AIAPI void (*IUStringToAIReal) ( unsigned char *string, AIReal *value );
	AIAPI void (*IUAIRealToStringUnits) ( AIReal value, unsigned char *string );
	AIAPI void (*IUStringUnitsToAIReal) ( unsigned char *string, AIReal *value );
	AIAPI AIErr (*GetUnitsString) ( short format, unsigned char *string );

	AIAPI AIErr (*AIUnitsToADMUnits) ( short aiUnits, ADMUnits *admUnits);
	AIAPI AIErr (*ADMUnitsToAIUnits) ( ADMUnits admUnits, short *aiUnits);
	AIAPI AIErr (*GetGlobalObjectDisplayName) ( char *name ); //name is modified in place
	
	/*Open the appropriate app to edit the object.  This is only meaningful for
	  Placed and Raster objects, and is equivalent to the user option-double-clicking
	  on the object with the selection tool.  See errors above.*/
	AIAPI AIErr (*EditInOriginalApp) ( AIArtHandle art );

	AIAPI AIErr (*AppIdle) ( void );

	AIAPI void (*DisableProgressCancel) ( void );

	// This method should be called by plugins when a timer or other asynchronous event
	// like updating triggers some action that may  allocate memory.  If it returns false,
	// the plugin should reschedule the action and try again later.  It is not necessary to
	// call this when handling notifications or user events; the plugin should never receive
	// these when it's not ok to allocate memory.
	AIAPI AIBoolean (*OKToAllocateMemory) ( void );

} AI100UserSuite;


#include "AIHeaderEnd.h"


#endif
