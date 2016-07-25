#ifndef _AI180CSXSExtension_H_
#define _AI180CSXSExtension_H_
/*
*		 Name:	_AICSXSExtension_H_
*        Date:	Started 2011
*     Purpose:	Adobe Illustrator CSXS Extension Header.
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 2009 Adobe Systems Incorporated.
* All rights reserved.
*
* NOTICE:  Adobe permits you to use, modify, and distribute this file
* in accordance with the terms of the Adobe license agreement
* accompanying it. If you have received this file from a source other
* than Adobe, then your use, modification, or distribution of it
* requires the prior written permission of Adobe.
*
*/

#ifndef __AITypes__
#include "AITypes.h"
#endif

#include "AIHeaderBegin.h"

/** @file AICSXSExtension.h */

/*******************************************************************************
**
** Constants
**
**/

#define kAI180CSXSExtensionSuite			"AI CSXS Extension Suite"
#define kAI180CSXSExtensionSuiteVersion	AIAPI_VERSION(2)
#define kAI180CSXSExtensionVersion		kAICSXSExtensionSuiteVersion

#define kAI180CSXSExtensionUnloadNotifier	"Extension Unloaded Notifier"

/**
	Constants for reporting the status of Creative Suite extensions.
	See \c #AICSXSExtensionSuite::GetExtensionState().
*/
enum AI180CSXSExtensionState
{
	/** Extension is not registered in Illustrator. */
	kAI180CSXSExtensionNotRegisteredState,
	/** Extension is registered in Illustrator and ready to load. */
	kAI180CSXSExtensionRegisteredState,
	/** Extension is loaded. */
	kAI180CSXSExtensionLoadedState,
	/** Extension is unloaded. */
	kAI180CSXSExtensionUnLoadedState,
	/** Internal use  */
	kAI180CSXSExtensionMaximumState      = 0xffff

};

typedef struct AI180CSXSExtensionNotifierMsg
{
	AI180CSXSExtensionState state;
	const char*			 extensionId;
}AI180CSXSExtensionNotifierMsg;

/*******************************************************************************
**
**	Suite
**
**/

/** @ingroup Suites
	This suite provides access to information about the status of Creative Suite
	extensions that might be loaded into Illustrator.

	Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAICSXSExtensionSuite and \c #kAICSXSExtensionVersion.
*/
typedef struct {

	/** Retrieves the current registration and load state of an extension.
	@param extensionId [in] The unique identifier of the extension.
	@param state [out] A buffer in which to return the current state, an \c #AICSXSExtensionState constant value.
	*/
	AIAPI AIErr (*GetExtensionState) (const char* extensionId, ai::int32& state);

	/** Reports whether an extension's main window is currently visible in the UI.
	@param extensionId [in] The unique identifier of the extension.
	@param isVisible [out] True if the extension's main window appears in the UI, false otherwise.
	*/
	AIAPI AIErr (*IsPrimaryStageVisible) (const char* extensionId, AIBoolean& isVisible);

	/** Launches extension of specified extension ID 
	@param extensionId [in] The unique identifier of the extension.
	*/
	AIAPI AIErr (*LaunchExtension) (const char* extensionId);

} AI180CSXSExtensionSuite;

#include "AIHeaderEnd.h"

#endif //_AICSXSExtension_H_
