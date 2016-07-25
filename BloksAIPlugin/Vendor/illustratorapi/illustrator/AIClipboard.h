#ifndef __AIClipboard__
#define __AIClipboard__

/*
 *        Name:	AIClipboard.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Clipboard Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2015 Adobe Systems Incorporated.
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

/** @file AIClipboard.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIClipboardSuite			"AI Clipboard Suite"
#define kAIClipboardSuiteVersion4		AIAPI_VERSION(4)	// In AI 20.0
// latest version
#define kAIClipboardSuiteVersion		kAIClipboardSuiteVersion4
#define kAIClipboardVersion			kAIClipboardSuiteVersion

/** @ingroup Callers
	The clipboard caller. See \c #AIClipboardSuite. */
#define kCallerAIClipboard 				"AI Clipboard"

/** @ingroup Selectors
	Execute a clipboard operation.
	The \c option field of the \c #AIClipboardMessage is either
	\c #kClipboardCopy or \c #kClipboardPaste. Perform the
	requested operation on the data in the \c ClipboardData field.
		\li For paste, the data in the message is in a format handled
			by your plug-in. Read the data and convert it to artwork in
			the current document, but do not delete the data.
		\li For copy, convert the data to the format your plug-in handles,
			and store a pointer to the result in the \c ClipboardData field
			of the message.
	*/
#define kSelectorAIGoClipboard				"AI Go"

/** @ingroup Selectors
	Prepare clipboard data asynchronously.
	The \c option field of the \c #AIClipboardAsyncMessage is currently
	\c #kClipboardCopy only.
*/
#define kSelectorAIPrepareAsyncClipboard				"AI Prepare Async"

/** @ingroup Selectors
	Check if you can copy the data in the current document to your format.
	Return \c #kNoErr if you can and \c #kCantCopyErr
	if you cannot. The \c #AIClipboardMessage does not contain meaningful data. */
#define kSelectorAICanCopyClipboard		"AI Can Copy"
/** @ingroup Selectors
	Requests a duplicate of the data in the \c ClipboardData field of
	\c #AIClipboardMessage, which is in a format your plug-in handles.
	Make a copy, replace the \c ClipboardData with the copy,
	and return \c #kNoErr. If you cannot make the copy, return an error code.
*/
#define kSelectorAICloneClipboard			"AI Clone"
/** @ingroup Selectors
	Delete the data in the \c ClipboardData field of the
	\c #AIClipboardMessage, which is in a format your plug-in handles.   */
#define kSelectorAIDisposeClipboard		"AI Dispose"

/** Option flags for registering a clipboard format handler with
	\c #AIClipboardSuite::AddClipboard(), specifies which operations
	are supported.
	*/
enum AIClipboardFormatOptions {
	/** This format knows how to copy to the clipboard. */
	kClipboardCopy						=	(1<<1),
	/** This format knows how to paste from the clipboard. */
	kClipboardPaste						=	(1<<2),
	/** This format cannot copy data to the clipboard.
		If set, user cannot enable the preference
		for copying data on exit. This is needed because
		the \c kClipboardCopy flag is also used internally
		to track the state of the user preference.
	*/
	kClipboardCannotCopy				=	(1<<3)
};

/** Data-preparation status values for asynchronous clipboard write operations.
See \c #AIClipboardSuite::SetClipboardDataAsyncStatus() and
\c #AIClipboardSuite::GetClipboardDataAsyncStatus(). */
enum AIClipboardDataAsyncStatus{

	/** Default sentinel value */
	kAICBAsyncStatus_None = 0,

	/** Clipboard data is in the process of preparation. */
	kAICBAsyncStatus_InProgress,

	/** Clipboard data preparation is cancelled by user. */
	kAICBAsyncStatus_Cancelled,

	/** Clipboard data preparation has encountered some error. */
	kAICBAsyncStatus_Error,

	/** Clipboard data preparation is successful. */
	kAICBAsyncStatus_Success,

	/** Clipboard data preparation has timed out
	because the asynchronous operation failed to respond. */
	kAICBAsyncStatus_Timeout
};

/** @ingroup Errors
	Return from \c kSelectorAICanCopyClipboard if you cannot perform copy. */
#define kCantCopyErr		'CLP?'


/*******************************************************************************
 **
 ** Types
 **
 **/

/** Identifies a registered clipboard format handler. */
typedef struct _t_AIClipboardOpaque *AIClipboardHandle;

/** Identifies a resource type. */
typedef ai::uint32 DDType;

/** Data used to register a clipboard format handler. See
	\c #AIClipboardSuite::AddClipboard(). */
typedef struct {
	/** The format name, such as "myCompany File Format" or "Rich Text Format"*/
	const char* clipboardName;
	/** In Windows, the OLE data type, such as \c CF_TEXT or \c CF_BITMAP */
	ai::int32 OleType;
	/** In Mac OS, the unique data resource type (\c ResType),
		such as \c 'TEXT' or \c 'PICT'. Check \c AIDragDropTypes.h
		to make sure it is unique.
		*/
	DDType uniqueType;
} AIClipboardData;


/** The message structure received when the clipboard format handler's main
	entry point receives a message with caller \c #kCallerAIClipboard */
typedef struct {
	/** The message data */
	SPMessageData d;
	/** The clipboard object. */
	AIClipboardHandle Clipboard;
	/** The clipboard data */
	AIStream ClipboardData;
	/** The supported clipboard operations.
		A logical OR of \c #AIClipboardFormatOptions values. */
	ai::int32 option;
} AIClipboardMessage;

/** The message structure received when the clipboard format handler's main
entry point receives a message with caller \c #kCallerAIClipboard and
selector \c #kSelectorAIPrepareAsyncClipboard. */
struct AIClipboardAsyncMessage{

	/** The message data. */
	SPMessageData d;

	/** The clipboard object. */
	AIClipboardHandle Clipboard;

	/** The supported clipboard operations,
	a logical OR of \c #AIClipboardFormatOptions values. */
	ai::int32 option;  // Currently, only kClipboardCopy is supported.
};

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
		\c #kAIClipboardSuite and \c #kAIClipboardVersion.
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

	/** Sets the data-preparation status of an asynchronous clipboard write operation.
	@param Clipboard The clipboard handler reference.
	@param asyncOperationStatus The status of clipboard data,
	an \c #AIClipboardDataAsyncStatus value.
	*/
	AIAPI AIErr(*SetClipboardDataAsyncStatus) (AIClipboardHandle Clipboard, ai::int32 asyncOperationStatus);

	/** Retrieves the data-preparation status of an asynchronous clipboard write operation.
	@param Clipboard The clipboard handler reference.
	@param asyncOperationStatus [out] A buffer in which to return the status of clipboard data,
	an \c #AIClipboardDataAsyncStatus value.
	*/
	AIAPI AIErr(*GetClipboardDataAsyncStatus) (AIClipboardHandle Clipboard, ai::int32& asyncOperationStatus);

	/** Sets the value to show in the progress bar during an asynchronous clipboard write operation.
	Calls \c #ResetClipboardDataAsyncOperationTimer() internally.
	@param Clipboard The clipboard handler reference.
	@param current A number between 0 and the specified maximum that represents how far the operation has progressed.
	@param max The maximum value, representing 100% progress.
	@param progressText A text message to display in the progress bar.
	*/
	AIAPI AIErr(*SetClipboardDataAsyncProgress) (AIClipboardHandle Clipboard, size_t current, size_t max, const ai::UnicodeString& progressText);

	/** Sets a timeout for an asynchronous clipboard write operation.
	If the async operation does not communicate with the parent process within this period,
	it is assumed that the process has encountered some error, and the operation is aborted.
	@param Clipboard The clipboard handler reference.
	@param timeout A number of seconds.  <<??>>
	*/
	AIAPI AIErr(*SetClipboardDataAsyncTimeout) (AIClipboardHandle Clipboard, AIReal timeout);

	/** Resets the timeout timer to 0. A client should use this to tell Illustrator that the async process
	is still alive, and the clipboard write operation should continue.
	@param Clipboard The clipboard handler reference.
	*/
	AIAPI AIErr(*ResetClipboardDataAsyncOperationTimer) (AIClipboardHandle Clipboard);


} AIClipboardSuite;

#include "AIHeaderEnd.h"


#endif
