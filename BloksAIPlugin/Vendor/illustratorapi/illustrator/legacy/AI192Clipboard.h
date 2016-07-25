#ifndef __AI192Clipboard__
#define __AI192Clipboard__

/*
 *        Name:	AI192Clipboard.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Clipboard Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2016 Adobe Systems Incorporated
 * All Rights Reserved.

 * NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the
 * terms of the Adobe license agreement accompanying it.  If you have received this file from a
 * source other than Adobe, then your use, modification, or distribution of it requires the prior
 * written permission of Adobe.
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

#include "AIClipboard.h"

#include "AIHeaderBegin.h"

/** @file AIClipboard.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAI192ClipboardSuite			"AI Clipboard Suite"
#define kAI192ClipboardSuiteVersion3		AIAPI_VERSION(3)

#define kAI192ClipboardSuiteVersion		kAI192ClipboardSuiteVersion3
#define kAI192ClipboardVersion			kAI192ClipboardSuiteVersion

/*******************************************************************************
 **
 **	Suite
 **
 **/

/**	@ingroup Suites
	The clipboard suite enables plug-ins to register new clipboard format handlers.
	The handler's main entry point will then receive messages requesting it to
	copy data to and from the clipboard as needed. The messages have caller
	\c #kCallerAIClipboard. The possible selectors are:

	\li \c #kSelectorAIGoClipboard
	\li \c #kSelectorAICanCopyClipboard
	\li \c #kSelectorAICloneClipboard
	\li \c #kSelectorAIDisposeClipboard


	Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAI192ClipboardSuite and \c #kAI192ClipboardVersion.
*/
typedef struct {

	/** Registers a new clipboard format handler.
			@param self This plug-in.
			@param data The types of clipboard data handled.
			@param options The capabilities of the format handler.
				A logical OR of \c #AIClipboardFormatOptions values.
			@param Clipboard [out] A buffer in which to return the clipboard handler reference.
		*/
	AIAPI AIErr (*AddClipboard) ( SPPluginRef self, AIClipboardData *data,
		ai::int32 options, AIClipboardHandle *Clipboard );
	/** Unregisters a clipboard format handler.
			@param Clipboard The clipboard handler reference.
		*/
	AIAPI AIErr (*RemoveClipboard) (AIClipboardHandle Clipboard);

	/** Retrieves the registered name of a clipboard format handler.
			@param Clipboard The clipboard handler reference.
			@param name [out] A buffer in which to return the name.
		*/
	AIAPI AIErr (*GetClipboardName) (AIClipboardHandle Clipboard, const char* *name);

	/** Retrieves the Windows OLE type of the data handled by the format handler.
			@param Clipboard The clipboard handler reference.
			@param OleType [out] A buffer in which to return the OLE data type.
		*/
	AIAPI AIErr (*GetClipboardOleType) (AIClipboardHandle Clipboard, ai::int32* OleType);

	/** Retrieves the plug-in reference for the plug-in supplying the format handler.
			@param Clipboard The clipboard handler reference.
			@param plugin [out] A buffer in which to return the plug-in reference.
		*/
	AIAPI AIErr (*GetClipboardPlugin) (AIClipboardHandle Clipboard, SPPluginRef *plugin);

	/** Retrieves the Mac OS resource type of the data handled by the format handler.
			@param Clipboard The clipboard handler reference.
			@param uniqueType [out] A buffer in which to return the data resource type.
		*/
	AIAPI AIErr (*GetClipboardType) (AIClipboardHandle Clipboard, DDType *uniqueType);

	/** Retrieves the options describing the capabilities of the format handler.
			@param Clipboard The clipboard handler reference.
			@param options [out] A buffer in which to return the capabilities of the
				format handler. A logical OR of \c #AIClipboardFormatOptions values.
		*/
	AIAPI AIErr (*GetClipboardOptions) (AIClipboardHandle Clipboard, ai::int32 *options);

	/** Sets the options describing the capabilities of the format handler.
			@param Clipboard The clipboard handler reference.
			@param options The capabilities of the format handler.
				A logical OR of \c #AIClipboardFormatOptions values.
		*/
	AIAPI AIErr (*SetClipboardOptions) (AIClipboardHandle Clipboard, ai::int32 options);

	/** Counts the number of registered clipboard format handlers.  Use with
		\c #GetNthClipboard() to iterate through handlers.
			@param count [out] A buffer in which to return the number of handlers.
		*/
	AIAPI AIErr (*CountClipboards) (ai::int32 *count);

	/** Retrieves a clipboard format handler by position index. Use with
		\c #CountClipboards() to iterate through handlers.
			@param n The index, in the range <code>[0..numHandlers-1]</code> .
			@param Clipboard [out] A buffer in which to return the clipboard handler reference.*/
	AIAPI AIErr (*GetNthClipboard) (ai::int32 n, AIClipboardHandle *Clipboard);

} AI192ClipboardSuite;

#include "AIHeaderEnd.h"

#endif
