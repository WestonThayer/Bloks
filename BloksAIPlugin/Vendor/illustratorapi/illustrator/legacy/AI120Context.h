#ifndef __AI120Context__
#define __AI120Context__

/*
 *        Name:	AI120Context.h
 *   $Revision: 1 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 12.0 Runtime Context Environment.
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

#include "AIContext.h"

#include "AIHeaderBegin.h"

/** @file AIContext.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAI120AppContextSuite		"AI Context Suite"
#define kAIAppContextSuiteVersion3	AIAPI_VERSION(3)
#define kAI120AppContextVersion		kAIAppContextSuiteVersion3


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** Use the Context Suite to save and restore the application context. An application
	context consists of an Artwork context, and an Undo context.

	Product independent plug-ins don’t always know about the application
	context. For example, ADM is host application independent; it knows
	nothing about the application environment in which it is operating in.

	Pushing the application context within an ADM plug-in tells ADM about the
	state of the application at any given time. Your plug-in will want to do this
	in init, drawer, notifier, and tracker procs. For example, if your plug-in has
	an ADM non-modal dialog which only makes changes to itself, you wouldn’t
	need to push the application context. However, if your plug-in makes
	changes to the artwork you will need to push the app context. */
typedef struct {

	/** This function returns the parent application window if called from Windows.
		It does nothing on the Macintosh. */
	AIAPI AIErr (*GetPlatformAppWindow) ( AIWindowRef *appWindow );

	/** Pushes an application context for the calling plug-in if needed. You
		should pass your plug-in's reference in plugin. The value returned in
		appContext must be passed to PopAppContext upon exit.
		
		Note: PushAppContext and PopAppContext should always be used in pairs
		to bracket code that relies on the application context. */
	AIAPI AIErr (*PushAppContext) ( SPPluginRef plugin, AIAppContextHandle *appContext );
	/** This function restores the previous application context. Pass the AIAppContextHandle
		which was returned by PushAppContext().

		Note: PushAppContext and PopAppContext should always be used in pairs
		to bracket code that relies on the application context.	*/
	AIAPI AIErr (*PopAppContext) ( AIAppContextHandle appContext );

	/** No longer needed. */
	AIAPI AIErr (*MacGetAppQDGlobal) ( void **appQD );

	/** Suspends the current API context stack. This is equivalent to popping
		all current open API contexts except that they can later be restored
		by ResumeAppContext(). This API should only be needed prior to some
		operation that may change the current document. */
	AIAPI AIErr (*SuspendAppContext) ( AISuspendedAppContext* appContext );
	/** Resumes the API context stack. The stack is resumed for the document of
		the frontmost window. This might be a different document from the one
		at the time the context stack was suspended. */
	AIAPI AIErr (*ResumeAppContext) ( AISuspendedAppContext appContext, AIDocumentHandle document );

} AI120AppContextSuite;


#include "AIHeaderEnd.h"


#endif
