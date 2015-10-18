#ifndef __AIUndo__
#define __AIUndo__

/*
 *        Name:	AIUndo.h
 *   $Revision: 6 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Undo Suite.
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

#include "IAIUnicodeString.h"

#include "AIHeaderBegin.h"

/** @file AIUndo.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIUndoSuite			"AI Undo Suite"
#define kAIUndoSuiteVersion		AIAPI_VERSION(7)
#define kAIUndoVersion			kAIUndoSuiteVersion


/** Undo context types. See \c #AIUndoSuite. */
enum AIUndoContextKind {
	/** A standard context results in the addition of a new transaction which
		can be undone/redone by the user */
	kAIStandardUndoContext = 0,
	/** A silent context does not cause redos to be discarded and
		is skipped over when undoing and redoing. An example is a selection change. */
	kAISilentUndoContext,
	/** An appended context is like a standard context, except that
		it is combined with the preceding transaction. It does not
		appear as a separate transaction. Used, for example, to
		collect sequential changes to the color of an object into a
		single undo/redo transaction. */
	kAIAppendUndoContext
};


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suites provides access to the Undo/Redo mechanism. Use these
	functions to revert the artwork state to what it was when your
	plug-in was called, or to set the text of the Undo/Redo menus.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIUndoSuite and \c #kAIUndoVersion.

	@section UndoContext Undo API Contexts

	The \c AIUndoSuite allows you to manipulate the undo \e context for your plug-in.
	Generally, each time Illustrator sends a plug-in a selector, it creates
	an undo context. The record is created before the plug-in is called and
	closed when the plug-in finishes running. The changes made by the plug-in
	are accumulated in this record and make up the undo context. When the user
	chooses Undo from the Edit menu, the changes of the last complete context
	are undone. Redo restores the context changes.

	You can use \c #UndoChanges() to programmatically undo the changes within
	the context Illustrator has made for your plug-in. It cannot undo changes
	outside of this context.

	For plug-in tools, Illustrator handles undo contexts a little differently.
	Instead of generating a context for each selector, it bundles the mouse
	selectors into a single context. This allows a plug-in to undo changes
	it made last time and then modify the document in response to the
	current mouse position. Illustrator then redraws the document when the plug-in
	returns control.

	There are three types of undo context, defined by \c #AIUndoContextKind.
	Illustrator normally establishes a \c #kAIStandardUndoContext, but notifications
	are sent in a \c #kAISilentUndoContext. A plug-in can change the undo context
	type with \c #SetSilent() and \c #SetKind(), but only if the plug-in is \e not
	operating in a nested context (that is, a context created when another plug-in
	is executing). This prevents a plug-in in a nested context from
	modifying the behavior of the outer context.

	Undo entries can be tagged with a string and/or an integer. Only standard
	contexts can be tagged.
*/
typedef struct {

	/** Specifies the localizable text(Unicode String) for Undo and Redo menu items. Illustrator
	uses these strings for the menus as needed.
	@note Illustrator automatically handles the undo mechanism for
	plug-in filters. Filters should not use this function.
	@param undoText	Unicode String text for the Undo menu.
	@param redoText	Unicode String text for the Redo menu.
	*/
	AIAPI AIErr (*SetUndoTextUS) ( const ai::UnicodeString& undoText, const ai::UnicodeString& redoText );

	/** Undoes changes in the current undo context. Clears any changes made
		to the artwork since the undo context of the plug-in was created.  */
	AIAPI AIErr (*UndoChanges) ( void );

	/** Undoes changes in the Action palette. Clears any changes made
		to the Action palette  since the undo context of the plug-in was created.  */
	AIAPI AIErr (*SetActionPaletteUndo) ( void );

	/** @deprecated Obsolete, do not use. */
	AIAPI AIErr (*PurgeAllUndos) ( void );

	/** Marks or unmarks the current API context as being silent for undo purposes.
		See @ref UndoContext.
			@param silent True to set the context to \c #kAISilentUndoContext,
				false to set it to \c #kAIStandardUndoContext.
		*/
	AIAPI AIErr (*SetSilent) ( AIBoolean silent );

	/** Sets the type of the current undo context, but only if the plug-in is \e not
		operating in a nested context (that is, a context created when another plug-in
		is executing). See @ref UndoContext.
			@param kind The new context type, an \c #AIUndoContextKind constant.
		*/
	AIAPI AIErr (*SetKind) ( ai::int32 kind );

	/**
		@deprecated	Use Unicode version \c #SetTagUS() instead.

		Sets a tag string and integer for the undo transaction that is generated
		by the current API context.	Affects only standard undo contexts; see @ref UndoContext.
			@param tagString A descriptive string.
			@param tagInteger An identifying number.
		*/
	AIAPI AIErr (*SetTag) ( char* tagString, ai::int32 tagInteger );

	/** Counts the number of undo and redo transactions that a user can
		perform. Does not count silent or appended transactions. Use with
		\c #GetNthTransactionTag() to iterate through transactions in the
		current undo context.
			@param past [out] A buffer in which to return the number of undo transactions.
			@param future [out] A buffer in which to return the number of redo transactions.

		*/
	AIAPI AIErr (*CountTransactions) ( ai::int32* past, ai::int32* future );

	/**
		@deprecated	Use Unicode version \c #GetNthTransactionTagUS() instead.

		Retrieves a transaction tag by position index from the current undo/redo context.
		Use with \c #CountTransactions() to iterate through transactions in the
		current standard undo context.
			@param n The position index. Positive values indicate undo transactions,
				negative values indicate redo transactions. No transaction is at index 0.
			@param tagString [out] A buffer in which to return the descriptive string.
			@param tagInteger [out] A buffer in which to return the identifying number.
	 	*/
	AIAPI AIErr (*GetNthTransactionTag) ( ai::int32 n, char** tagString, ai::int32* tagInteger );

	/** Reports whether the current API context is marked as silent for undo purposes.
		If the current context is nested, this can return true while the outer
		context is not silent. See @ref UndoContext.
			@param silent [out] A buffer in which to return true if the current undo context
				is silent.
		*/
	AIAPI AIErr (*IsSilent) ( AIBoolean* silent );

	/** Sets a Unicode tag string and integer for the undo transaction that is generated
	by the current API context.	Affects only standard undo contexts; see @ref UndoContext.
	@param tagString A descriptive Unicode string.
	@param tagInteger An identifying number.
	*/
	AIAPI AIErr (*SetTagUS) ( const ai::UnicodeString& tagString, ai::int32 tagInteger );

	/** Retrieves a transaction tag (a Unicode string) by position index from the current undo/redo context.
	Use with \c #CountTransactions() to iterate through transactions in the
	current standard undo context.
	@param n The position index. Positive values indicate undo transactions,
		negative values indicate redo transactions. No transaction is at index 0.
	@param tagString [out] A buffer in which to return the descriptive Unicode string.
	@param tagInteger [out] A buffer in which to return the identifying number.
	*/

	AIAPI AIErr (*GetNthTransactionTagUS) ( ai::int32 n, ai::UnicodeString& tagString, ai::int32* tagInteger );

} AIUndoSuite;


#include "AIHeaderEnd.h"


#endif
