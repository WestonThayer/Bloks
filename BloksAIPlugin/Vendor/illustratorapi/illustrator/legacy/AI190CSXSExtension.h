#ifndef _AI190CSXSExtension_H_
#define _AI190CSXSExtension_H_
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

#define kAI190CSXSExtensionSuite			"AI CSXS Extension Suite"
#define kAI190CSXSExtensionSuiteVersion	AIAPI_VERSION(3)
#define kAI190CSXSExtensionVersion		kAICSXSExtensionSuiteVersion

#define kAICSXSExtensionUnloadNotifier	"Extension Unloaded Notifier"

/**
Constants for reporting the status of Creative Suite extensions.
See \c #AICSXSExtensionSuite::GetExtensionState().
*/
enum AI190CSXSExtensionState
{
	/** Extension is not registered in Illustrator. */
	kAI190CSXSExtensionNotRegisteredState,
	/** Extension is registered in Illustrator and ready to load. */
	kAI190CSXSExtensionRegisteredState,
	/** Extension is loaded. */
	kAI190CSXSExtensionLoadedState,
	/** Extension is unloaded. */
	kAI190CSXSExtensionUnLoadedState,
	/** Internal use  */
	kAI190CSXSExtensionMaximumState = 0xffff

};

typedef struct AI190CSXSExtensionNotifierMsg
{
	AI190CSXSExtensionState state;
	const char*			 extensionId;
}AI190CSXSExtensionNotifierMsg;

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
	AIAPI AIErr(*GetExtensionState) (const char* extensionId, ai::int32& state);

	/** Reports whether an extension's main window is currently visible in the UI.
	@param extensionId [in] The unique identifier of the extension.
	@param isVisible [out] True if the extension's main window appears in the UI, false otherwise.
	*/
	AIAPI AIErr(*IsPrimaryStageVisible) (const char* extensionId, AIBoolean& isVisible);

	/** Launches extension of specified extension ID
	@param extensionId [in] The unique identifier of the extension.
	*/
	AIAPI AIErr(*LaunchExtension) (const char* extensionId);

	/** Sends Provided Event To Extension with the provided data
	@param extensionId [in] The unique identifier of the extension.
	@param eventID [in] The unique identifier of the event.
	@param appId [in] The unique identifier of Application.
	@param data [in] data is optional. it can be used to send some data to extension along with the event
	*/
	AIAPI AIErr(*SendEventToExtension) (const char* extensionId, const char* eventID, const char* appId, const char* data);

} AI190CSXSExtensionSuite;

#include "AIHeaderEnd.h"

#endif // _AI190CSXSExtension_H

