#ifndef __AI140Symbol__
#define __AI140Symbol__

/*
 *        Name:	AI140Symbol.h
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Symbol Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1990-2007 Adobe Systems Incorporated.
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

#include "AISymbol.h"

#include "AIHeaderBegin.h"

/** @file AI140Symbol.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAI140SymbolSuite				kAISymbolSuite
#define kAI140SymbolSuiteVersion4		AIAPI_VERSION(4)
#define kAI140SymbolSuiteVersion		kAI140SymbolSuiteVersion4
#define kAI140SymbolVersion				kAI140SymbolSuiteVersion


/*******************************************************************************
 **
 **	AI140SymbolSuite Suite
 **
 **/

typedef struct {

	/** Counts the number of symbol definitions in the global list for the current document.
		Use with \c #GetNthSymbolPattern() to iterate through listed or through listed and
		unlisted symbols.
			@param count [out] A buffer in which to return the number of symbols.
			@param includeUnlisted When true, include unlisted symbols in the count.
				When false, count only listed symbols. See @ref ListedUnlistedSymbols.
		*/
	AIAPI AIErr (*CountSymbolPatterns) ( ai::int32 *count, ASBoolean includeUnlisted );

	/** Retrieves a symbol pattern from the global list for the current document.Use
		with \c #CountSymbolPatterns() to iterate through listed or through listed and
		unlisted symbols.
			@param n The 0-based position index.
			@param symbolPattern [out] A buffer in which to return the symbol reference.
			@param includeUnlisted When true, get both listed and unlisted symbols.
				When false, get only listed symbols. See @ref ListedUnlistedSymbols.
		*/
	AIAPI AIErr (*GetNthSymbolPattern) ( ai::int32 n, AIPatternHandle *symbolPattern, ASBoolean includeUnlisted );

	/** Retrieves a symbol pattern by name from the current document.
			@param name The name string.
			@param symbolPattern [out] A buffer in which to return the symbol reference,
				or a \c NULL object if no such symbol is found.
		*/
	AIAPI AIErr (*GetSymbolPatternByName) ( const ai::UnicodeString& name, AIPatternHandle *symbolPattern );

	/** Retrieves a symbol pattern by name from a specified document.
			@param name The name string.
			@param symbolPattern [out] A buffer in which to return the symbol reference,
				or a \c NULL object if no such symbol is found.
			@param document The document. Use the \c #AIDocumentListSuite
				or \c #AIPathStyleSuite::ImportStyles()	to obtain a document handle.
		*/
	AIAPI AIErr (*GetSymbolByNameFromDocument) ( const ai::UnicodeString& name, AIPatternHandle *symbolPattern,
												   AIDocumentHandle document );

	/** Counts the number of symbol definitions in the global list of a specified document.
		Use with \c #GetNthSymbolPatternFromDocument() to iterate through listed (public) symbols.
			@param count [out] A buffer in which to return the number of symbols.
			@param document The document. Use the \c #AIDocumentListSuite
				or \c #AIPathStyleSuite::ImportStyles()	to obtain a document handle.
		*/
	AIAPI AIErr (*CountSymbolPatternsFromDocument) ( ai::int32* count, AIDocumentHandle document );

	/** Retrieves a symbol pattern from the global list for a specified document.
		Use with \c #CountSymbolPatternsFromDocument() to iterate through listed (public) symbols.
			@param n The 0-based position index.
			@param symbolPattern [out] A buffer in which to return the symbol reference.
			@param document The document. Use the \c #AIDocumentListSuite
				or \c #AIPathStyleSuite::ImportStyles()	to obtain a document handle.
		*/
	AIAPI AIErr (*GetNthSymbolPatternFromDocument) ( ai::int32 n, AIPatternHandle *symbolPattern,
													 AIDocumentHandle document );

	/** Creates a new symbol definition from specified source art, which is copied as
		the defining art for the new symbol.
			@param newSymbolPattern [out] A buffer in which to return the new symbol reference.
			@param definitionArt The source art, or \c NULL to create a symbol whose definition
				is an empty group.
 			@param unlisted When true, make the new symbol unlisted. Use \c #SetSymbolPatternName()
				to name unlisted symbols. See @ref ListedUnlistedSymbols.
 		*/
	AIAPI AIErr (*NewSymbolPattern) ( AIPatternHandle *newSymbolPattern, AIArtHandle definitionArt, ASBoolean unlisted );

	/** Creates a new listed symbol definition from selected art, which is copied as the
		defining art for the new symbol. If no art is selected, creates a symbol
		whose definition is an empty group.
			@param symbolPattern [out] A buffer in which to return the new symbol reference.
		*/
	AIAPI AIErr (*NewSymbolPatternFromSel) ( AIPatternHandle *symbolPattern );

	/** Creates a new listed symbol definition from selected art, which is copied as the
		defining art for the new symbol, and reports the bounds of the selected art.
		(You cannot call \c #AIArtSuite::GetArtBounds() for the symbol pattern art after
		defining it, because the definition art is copied and moved.) Use to insert an
		instance of the new symbol in place of the selection.
			@param symbolPattern [out] A buffer in which to return the new symbol reference.
			@param selectionBounds [out] A buffer in which to return the bounding box
				of the selected art.
		*/
	AIAPI AIErr (*NewSymbolPatternFromSelGetBounds) ( AIPatternHandle *symbolPattern, AIRealRect *selectionBounds );

	/** Deletes a symbol definition.
			@param symbolPattern The symbol reference.
        
            @return The error \c #kCantDeleteSymbolUsedInLiveEffectsErr if the symbol pattern is used in a Live Effect.
                    The error \c #kBadParameterErr if NULL is passed.
		*/
	AIAPI AIErr (*DeleteSymbolPattern) ( AIPatternHandle symbolPattern );

	/** Reports whether a symbol is still known to the system. A symbol reference can
		change if you retain it between message. To ensure a valid reference, get
		the reference from the \c #kAIArtSymbolSetChangedNotifier.
		(Note that this function returns a boolean value, not an error code.)
			@param symbolPatter The symbol reference.
			@return True if the symbol is a valid reference.
		 */
	AIAPI AIBoolean (*ValidateSymbolPattern) ( AIPatternHandle symbolPattern );


	// Functions for examining and modifying a symbol definition

	/** Retrieves a copy of the definition art of a symbol. YOu can examine or
		duplicate the returned art, but cannot edit it.
			@param pattern The symbol pattern reference.
			@param art [out] A buffer in which to return the definition art.
		*/
	AIAPI AIErr (*GetSymbolPatternArt) ( AIPatternHandle pattern, AIArtHandle *art );

	/** Creates a copy of a symbol pattern's definition artwork and places it
		into the current document at the center of the current view, at the current
		layer and using the current insertion mode. It is the equivalent of using
		a simple Paste command.
			@param symbolPattern The symbol pattern reference.
			@return The error \c #kUntouchableLayerErr if the current layer or
				current insertion group is locked or hidden.
			@see \c #AIPatternSuite::GetPattern()
			@note To get an editable copy of a symbol, it is better to use
				\c #AIDictionarySuite::NewArtEntry() to create a group that
				is not in the artwork tree, insert the definition copy into that
				using \c #CopySymbolPatternArt(), and then delete the dictionary entry.
				This avoids modifying the art tree and triggering unneeded synchronization
				and change notifications. This technique is often used by export filters
				to make systematic adjustments to Illustrator art before converting
				it to an easy-to-export form.
		*/
	AIAPI AIErr (*PasteSymbolPatternArt) ( AIPatternHandle symbolPattern );

	/** Creates a copy of a symbol pattern's definition artwork and places it
		into the current document at a specified place in the paint order.
			@param symbolPattern The symbol pattern reference.
			@param paintOrder The paint order position, relative to the \c prep object,
				an \c #AITypes::AIPaintOrder value.
			@param prep The prepositional art object for the paint order.
			@param newArt [out] Optional. A buffer in which to return the new art object.
		*/
	AIAPI AIErr (*CopySymbolPatternArt) ( AIPatternHandle symbolPattern,
								short paintOrder, AIArtHandle prep, AIArtHandle *newArt );

	/** Creates a copy of source art and makes it the defining art for a symbol. Updates
		any existing instances of the symbol.
			@param symbolPattern The symbol pattern reference.
			@param definitionArt The source art.
		*/
	AIAPI AIErr (*SetSymbolPatternArt) ( AIPatternHandle symbolPattern, AIArtHandle definitionArt );

	/** Copies selected art and makes it the defining art for a symbol. Updates
		any existing instances of the symbol.
			@param symbolPattern The symbol pattern reference.
			@see \c #AIPatternSuite::SetPattern()
		*/
	AIAPI AIErr (*SetSymbolPatternFromSel) ( AIPatternHandle symbolPattern );


	// The functions below use C strings. If you have or want Pascal strings, you can
	// also get and set the name of a symbol using GetPatternName and SetPatternName
	// from AIPattern.h.

	/** Retrieves the name of a symbol.
			@param symbolPattern The symbol pattern reference.
			@param name [out] A buffer in which to return the name string. Truncates
				a name that is too long to fit in the buffer.
			@return \c #kNameTooLongErr error if the name was truncated.
		*/
	AIAPI AIErr (*GetSymbolPatternName) ( AIPatternHandle symbolPattern, ai::UnicodeString& name );

	/** Sets the name of a symbol.
			@param name The new name string.
			@return \c #kNameTooLongErr error if the name length exceeds \c #kMaxSymbolNameLength.
		 		<br> \c #kInvalidNameErr error if the name contains illegal characters,
		 		is of zero length, or consists entirely of spaces.
				<br> \c #kNameInUseErr if the name is already used for another symbol.
		 		<br> In any error case, the symbol name remains unchanged.
			@see \c #SetSymbolPatternBaseName()
		 	 */
	AIAPI AIErr (*SetSymbolPatternName) ( AIPatternHandle symbolPattern, const ai::UnicodeString& name );

	/** Strips any hidden characters from the end of a symbol name to create
		a displayable string.
			@param name [in, out] The symbol name string, which is modified in place.
		*/
	AIAPI AIErr (*GetSymbolPatternDisplayName) ( ai::UnicodeString& name );

	/** Sets the name of a symbol, appending numbers to a name string that is
		already in use to make it unique. If the name string is very long,
		it can be truncated before the numbers are appended.
			@param symbolPattern The symbol pattern reference.
			@param name The new name string.
		*/
	AIAPI AIErr (*SetSymbolPatternBaseName) ( AIPatternHandle symbolPattern, ai::UnicodeString& name );

	/** Creates a new symbol instance in the center of the current document view.
			@param symbolPattern The symbol pattern reference.
			@param paintOrder The paint order position, relative to the \c prep object,
				an \c #AITypes::AIPaintOrder value.
			@param prep The prepositional art object for the paint order.
			@param newArt [out] A buffer in which to return the new instance,
				an art object of type \c #kSymbolArt.
			@return \c #kBadParameterErr error if there are no symbols defined
				in the current document.
		*/
	AIAPI AIErr (*NewInstanceCenteredInView) ( AIPatternHandle symbolPattern,
								short paintOrder, AIArtHandle prep, AIArtHandle *newArt );

	/** Creates a new symbol instance with its center at a specified location.
			@param symbolPattern The symbol pattern reference.
			@param center The location, in page coordinates.
			@param paintOrder The paint order position, relative to the \c prep object,
				an \c #AITypes::AIPaintOrder value.
			@param prep The prepositional art object for the paint order.
			@param newArt [out] A buffer in which to return the new instance,
				an art object of type \c #kSymbolArt.
			@return \c #kBadParameterErr error if there are no symbols defined
				in the current document.
		*/
	AIAPI AIErr (*NewInstanceAtLocation) ( AIPatternHandle symbolPattern, AIRealPoint center,
								short paintOrder, AIArtHandle prep, AIArtHandle *newArt );

	/** Creates a new symbol instance with a specified transformation matrix.
			@param symbolPattern The symbol pattern reference.
			@param transform The transformation matrix.
			@param paintOrder The paint order position, relative to the \c prep object,
				an \c #AITypes::AIPaintOrder value.
			@param prep The prepositional art object for the paint order.
			@param newArt [out] A buffer in which to return the new instance,
				an art object of type \c #kSymbolArt.
			@return \c #kBadParameterErr error if there are no symbols defined
				in the current document.
		*/
	AIAPI AIErr (*NewInstanceWithTransform) ( AIPatternHandle symbolPattern, AIRealMatrix *transform,
								short paintOrder, AIArtHandle prep, AIArtHandle *newArt );

	/** Retrieves the symbol pattern definition of a symbol instance.
			@param symbolArt The symbol instance, an art object of type \c #kSymbolArt.
			@param symbolPattern [out] A buffer in which to return the symbol pattern reference.
		*/
	AIAPI AIErr (*GetSymbolPatternOfSymbolArt) ( AIArtHandle symbolArt, AIPatternHandle *symbolPattern );

	/** Sets the symbol pattern definition of a symbol instance.
			@param symbolArt The symbol instance, an art object of type \c #kSymbolArt.
			@param symbolPattern The symbol pattern reference.
		*/
	AIAPI AIErr (*SetSymbolPatternOfSymbolArt) ( AIArtHandle symbolArt, AIPatternHandle symbolPattern );

	/** Retrieves the transformation matrix that Illustrator uses to transform specified symbol art
		into a symbol instance.
			@param symbolArt The symbol instance, an art object of type \c #kSymbolArt.
			@param transform [out] A buffer in which to return the transformation matrix.
 			@see \c #AIHardSoftSuite for a discussion of coordinate systems.
			@note	Use \c #AIHardSoftSuite::AIRealMatrixRealSoft() and
					\c #AIHardSoftSuite::AIRealMatrixRealHard() to translate between
					the hard and soft forms of the matrix (\e not
					\c #AIHardSoftSuite::AIRealMatrixHarden() and
					\c #AIHardSoftSuite::AIRealMatrixSoften(), which affect
					only the tx ty components).
			*/
	AIAPI AIErr (*GetHardTransformOfSymbolArt) ( AIArtHandle symbolArt, AIRealMatrix *transform );

	/** Sets the application transformation matrix for a symbol instance.
			@param symbolArt The symbol instance, an art object of type \c #kSymbolArt.
			@param transform The new transformation matrix.
 			@see \c #GetHardTransformOfSymbolArt()
 		*/
	AIAPI AIErr (*SetHardTransformOfSymbolArt) ( AIArtHandle symbolArt, AIRealMatrix *transform );

	/** Retrieves the transformation matrix that a plug-in can use to transform to transform
		specified symbol art into a symbol instance (using the \c #AITransformArtSuite).
			@param symbolArt The symbol instance, an art object of type \c #kSymbolArt.
			@param transform [out] A buffer in which to return the transformation matrix.
 			@see \c #AIHardSoftSuite for a discussion of coordinate systems.
		*/
	AIAPI AIErr (*GetSoftTransformOfSymbolArt) ( AIArtHandle symbolArt, AIRealMatrix *transform );

	/** Sets the plug-in transformation matrix for a symbol instance.
			@param symbolArt The symbol instance, an art object of type \c #kSymbolArt.
			@param transform The new transformation matrix.
 			@see \c #GetSoftTransformOfSymbolArt()
 		*/
	AIAPI AIErr (*SetSoftTransformOfSymbolArt) ( AIArtHandle symbolArt, AIRealMatrix *transform );

	/**	Expands a symbol instance and places the resulting art into the artwork tree.
		The function preserves the appearance, not the editability, of the symbol
		definition.
			\li If the instance transformation matrix is a simple placement matrix,
				this is equivalent to \c #BreakLinkToSymbol().
			\li If the matrix includes a scale, rotation, shear, or reflection,
				the function expands any appearances or plug-in groups inside
				the symbol definition, then applies the matrix.
			\li If the matrix includes a shear or a non-uniform scale, the function
				expands strokes before applying the matrix.
			@param symbolArt The symbol instance, an art object of type \c #kSymbolArt.
				This object is not deleted.
			@param paintOrder The paint order position, relative to the \c prep object,
				an \c #AITypes::AIPaintOrder value.
			@param prep The prepositional art object for the paint order.
			@param expandedArt [out] Optional. A buffer in which to return the new art object.
		*/
	AIAPI AIErr (*InsertExpandedSymbolArt) ( AIArtHandle symbolArt,
												short paintOrder, AIArtHandle prep, AIArtHandle *expandedArt );

	/** Reports whether a symbol definition is listed. See @ref ListedUnlistedSymbols.
		(Note that this function returns a boolean value, not an error code.)
			@param symbolPattern The symbol pattern reference.
			@return True if the symbol pattern is listed.
		*/
	AIAPI AIBoolean (*IsSymbolPatternListed) ( AIPatternHandle symbolPattern );

	/** Makes a symbol definition listed. See @ref ListedUnlistedSymbols.
			@param symbolPattern The symbol pattern reference.
		*/
	AIAPI AIErr (*MakeSymbolPatternListed) ( AIPatternHandle symbolPattern );

	/** Makes a symbol definition unlisted. See @ref ListedUnlistedSymbols.
			@param symbolPattern The symbol pattern reference.
		*/
	AIAPI AIErr (*UnlistSymbolPattern) ( AIPatternHandle symbolPattern );

   	/**	Sorts the listed symbols in the global list of symbols, alphabetically by name.
 		See @ref ListedUnlistedSymbols.
 		*/
  	AIAPI AIErr (*SortListedSymbolPatterns) ( void );

	/** Moves a listed symbol to a specific index position in the global list of symbols.
		Increments the position of the symbol previously at that index, and of all
		subsequent listed symbols. See @ref ListedUnlistedSymbols.
			@param symbolPattern The symbol pattern reference.
			@param index The new 0-based index position, or -1 to move to the
				end of the list.
		*/
	AIAPI AIErr (*MoveSymbolPatternInList) ( AIPatternHandle symbolPattern, int index );

	/** Reports whether an art object uses a specified symbol in a specified way.
		(Note that this function returns a boolean value, not an error code.)
			@param art The art object, or \c NULL to search the entire artwork tree.
				In this case, the search includes descendants regardless of the
				value of the \c #kSearchDescendants flag.
			@param searchScope The scope of the search, a logical OR of \c #AISymbolSearchScope
				bit flags.
			@param targetSymbol	The symbol reference, or \c NULL to search for any symbol.
			@param oneFoundSymbol [out] Optional. When \c targetSymbol is \c NULL, a buffer
				in which to return a single matching symbol found within the search scope,
				or \c NULL if more than one matching symbol is found.

			@note \c oneFoundSymbol is used by the Symbols palette to decide which symbol to select.
   				If an object uses multiple symbols, nothing is selected. The scope for this
   				type of usage should not include \c #kSearchNestedSymbolPatterns. For example, if
   				symbol A's definition includes symbol B, and the user selects an instance of
   				symbol A, symbol A should be selected in the palette. If the user selects
   				a particle set containing instances of both symbol A and symbol B,
   				neither symbol should be selected in the palette.

			@param allFoundSymbols [out] Optional. When \c targetSymbol is \c NULL,  a buffer
				 in which to return the handle of an array of matching symbols, of size \c foundCount.
				 This memory is allocated by the function, and you must free it using
				 \c #AIMdMemorySuite::MdMemoryDisposeHandle().

				 If no art object is specified, you can still specify the output array. This is how
  				the "Select All Unused" command in the Symbols palette is implemented.

				 If an art object is specified, use this array to examine patterns
				 that are referenced by a plug-in group that puts multiple symbols in its dictionary,
				 such as a particle set.
			@param foundCount [out] When \c targetSymbol is \c NULL, a buffer in which to
				return the size of the \c allFoundSymbols array.
			@param globalObjectUsage Not implemented.
			@return True if	any matching symbols are found.
		*/
	AIAPI AIBoolean (*ArtUsesSymbolPattern) ( AIArtHandle art, short searchScope, AIPatternHandle targetSymbol,
											AIPatternHandle *oneFoundSymbol,
											AIPatternHandle ***allFoundSymbols, int *foundCount,
											int *globalObjectUsage);

	/**	Creates a copy of a symbol's definition artwork, transforms it
		using the matrix of a symbol instance, and places it into the
		current document at a specified place in the paint order. Transfers
		attributes from the symbol instance to the transformed art.

		Does not do any internal expansion of strokes, active styles or plug-in groups
		inside the symbol definition, even when a rotational or shear transform is applied.
		Preserves the full structure and editability of the	symbol definition,
		at the cost of sometimes not preserving the appearance of the instance.

		This is the equivalent of calling \c #CopySymbolPatternArt() and then performing
		the transformation using the \c #AITransformArtSuite, but is more efficient.
		If the instance matrix is a simple placement matrix, this is equivalent to
		\c #InsertExpandedSymbolArt().

			@param symbolArt The symbol instance, an art object of type \c #kSymbolArt.
				This object is not deleted.
			@param paintOrder The paint order position, relative to the \c prep object,
				an \c #AITypes::AIPaintOrder value.
			@param prep The prepositional art object for the paint order.
			@param expandedArt [out] Optional. A buffer in which to return the new art object.
		*/
	AIAPI AIErr (*BreakLinkToSymbol) ( AIArtHandle symbolArt,
												short paintOrder, AIArtHandle prep, AIArtHandle *expandedArt );

	/**	Retargets a symbol pattern, fill pattern, or brush pattern for the current document.
		Creates a new pattern if needed, with the same definition art and a unique name based on
		the source pattern's name. All other global objects (colors, patterns, brushes, styles,
		 and so on) used indirectly in the definition are similarly retargeted, using
		an existing object if one matches and creating a new one otherwise.

		In this context, a listed symbol never matches an unlisted one, even if it has
		the same name and definition.

       	Use for drag-and-drop between library palettes and the main document palette.
		 	@param srcPattern A symbol pattern, fill pattern, or brush pattern reference.
			@param dstPattern [out] A buffer in which to return the new pattern, or
				an existing pattern in the current document with the same name and definition,
				or the source pattern if it was already in the current document.

			@note Fill patterns are usually retargeted indirectly using the
				\c #AIPathStyleSuite, and brush patterns using the \c #AIObjectSetSuite.
			 @see \c #AIPatternSuite, \c #AIObjectSetSuite::RetargetForCurrentDocument(),
				\c #AIPathStyleSuite::RetargetForCurrentDoc()
			*/
	AIAPI AIErr (*RetargetForCurrentDocument) ( AIPatternHandle srcPattern, AIPatternHandle *dstPattern );

	// New for Illustrator 11:

	/** Creates a copy of a symbol pattern's definition artwork, converts it to outline
		using specified options, and places the result into the current document
		at a specified place in the paint order.
			@param symbolPattern The symbol pattern reference.
			@param paintOrder The paint order position, relative to the \c prep object,
				an \c #AITypes::AIPaintOrder value.
			@param prep The prepositional art object for the paint order.
			@param newArt [out] Optional. A buffer in which to return the new art object, or
				a \c NULL object if no outline can be generated.
			@param convertToOutlineOptions Option flags for conversion, a logical OR of these values:
					<br> \c #kOutlineExpandAppearance
					<br> \c #kOutlineEliminateUnpainted
					<br> \c #kOutlineAddStrokes
					<br> \c #kOutlineSubtractStrokes
					<br> \c #kOutlineAlwaysIncludeFillArea
					<br> \c #kOutlineAlwaysStrokeStraightLines
		*/
	AIAPI AIErr (*CopySymbolPatternOutline) ( AIPatternHandle symbolPattern,
		short paintOrder, AIArtHandle prep, AIArtHandle *newArt, ai::int32 convertToOutlineOptions );

	/** Expands a symbol definition, outlines the symbol definition, applies the instance
		transformation to the outlined definition art. and finally places the transformed
		outline art into the artwork tree.
			@param symbolArt The symbol instance, an art object of type \c #kSymbolArt.
				This object is not deleted.
			@param paintOrder The paint order position, relative to the \c prep object,
				an \c #AITypes::AIPaintOrder value.
			@param prep The prepositional art object for the paint order.
			@param expandedArt [out] Optional. A buffer in which to return result art.
			@param convertToOutlineOptions Option flags for conversion, a logical OR of these values:
					<br> \c #kOutlineExpandAppearance
					<br> \c #kOutlineEliminateUnpainted
					<br> \c #kOutlineAddStrokes
					<br> \c #kOutlineSubtractStrokes
					<br> \c #kOutlineAlwaysIncludeFillArea
					<br> \c #kOutlineAlwaysStrokeStraightLines
			@see \c #InsertExpandedSymbolArt()
		*/
	AIAPI AIErr (*InsertSymbolArtOutline) ( AIArtHandle symbolArt,
		short paintOrder, AIArtHandle prep, AIArtHandle *expandedArt, ai::int32 convertToOutlineOptions );

	/** Retrieves a cached outline for a symbol pattern, if one has been generated for a given
		set of conversion options. You can examine or duplicate the returned outline art, but cannot edit it.
			@param symbolPattern The symbol pattern reference.
			@param outlineArt [out] A buffer in which to return	the cached outline art, or \c NULL
				if no cached outline has been generated for the given options.
			@param convertToOutlineOptions Option flags for conversion, a logical OR of these values:
					<br> \c #kOutlineExpandAppearance
					<br> \c #kOutlineEliminateUnpainted
					<br> \c #kOutlineAddStrokes
					<br> \c #kOutlineSubtractStrokes
					<br> \c #kOutlineAlwaysIncludeFillArea
					<br> \c #kOutlineAlwaysStrokeStraightLines
		*/
	AIAPI AIErr (*PeekCachedPatternOutline) ( AIPatternHandle symbolPattern, AIArtHandle *outlineArt, ai::int32 convertToOutlineOptions );

	// New for Illustrator 13:

	/** Sets a symbol definition from selected art, and reports the bounds of the selected art.
			@param symbolPattern The symbol pattern reference.
			@param selectionBounds [out] Optional. A buffer in which to return the bounding box
				of the selected art.
			@see \c #NewSymbolPatternFromSelGetBounds.
		*/
	AIAPI AIErr (*SetSymbolPatternFromSelGetBounds) ( AIPatternHandle symbolPattern, AIRealRect *selectionBounds );


	/** Sets the symbol export type for a symbol pattern, to use when exporting the
	    symbol to Flash.
			@param symbolPattern The symbol pattern reference.
			@param exportType	 The Flash export type.
		*/
	AIAPI AIErr (*SetSymbolExportType) ( AIPatternHandle symbolPattern, AISymbolFlashExportType exportType);

	/** Retrieves the symbol export type for a symbol pattern, used when exporting the symbol
	    to Flash. 
			@param symbolPattern The symbol pattern reference.
			@param exportType [out]	 The Flash export type.
		*/
	AIAPI AIErr (*GetSymbolExportType) ( AIPatternHandle symbolPattern, AISymbolFlashExportType *exportType);

	
	/** Sets the symbol registration point for a symbol pattern. to use when exporting the
	symbol to Flash.
	@param symbolPattern		The symbol pattern reference.
	@param registrationPoint	The Flash registration point.
	*/
	AIAPI AIErr (*SetSymbolRegistrationPoint) ( AIPatternHandle symbolPattern, AISymbolRegistrationPoint registrationPoint);

	/** Retrieves the symbol registration point for a symbol pattern, used when exporting the symbol
	to Flash. 
	@param symbolPattern			The symbol pattern reference.
	@param registrationPoint [out]	The Flash registration type.
	*/
	AIAPI AIErr (*GetSymbolRegistrationPoint) ( AIPatternHandle symbolPattern, AISymbolRegistrationPoint *registrationPoint);
	
	/** Sets the symbol "Enable guides for 9-slice scaling" option for a symbol pattern,
		to use when exporting the symbol to Flash.
	@param symbolPattern		The symbol pattern reference.
			@param enableGuides	 True to turn 9-slice scaling on, false to turn it off.
	*/
	AIAPI AIErr (*SetSymbolEnableGuides) ( AIPatternHandle symbolPattern, AIBoolean enableGuides);

	/** Retrieves the symbol "Enable guides for 9-slice scaling" option for a symbol pattern,
		used when exporting the symbol to Flash.
	@param symbolPattern			The symbol pattern reference.
			@param enableGuides [out]	A buffer in which to return true if
				9-slice scaling is on, false if it is off.
	*/
	AIAPI AIErr (*GetSymbolEnableGuides) ( AIPatternHandle symbolPattern, AIBoolean *enableGuides);

	/** Sets the symbol scaling grid for 9-slice scaling for a symbol pattern,
		to be used when exporting the symbol to Flash.
	@param symbolPattern		The symbol pattern reference.
			@param slice9Grid		The rectangular area of the center slice.
	*/
	AIAPI AIErr (*SetSymbol9SliceGrid) ( AIPatternHandle symbolPattern, AIRealRect slice9Grid);

	/** Retrieves the symbol scaling grid for 9-slice scaling for a symbol pattern,
		used when exporting the symbol to Flash.
	@param symbolPattern			The symbol pattern reference.
			@param slice9Grid [out]		A buffer in which to return the rectangular area of the center slice.
	*/
	AIAPI AIErr (*GetSymbol9SliceGrid) ( AIPatternHandle symbolPattern, AIRealRect *slice9Grid);

	// Symbol editing workflow (new in AI13/CS3)

	/** Starts an editing session for a symbol pattern.

    	Invokes isolation mode on a copy of the prototype of the pattern, and places the
		copy on the artboard. If a symbol art is specified, the copy is placed in the same 
		location as the symbol instance, hiding the original. Otherwise, the copy is placed in the 
		center of the artboard.

		You can start nested editing sessions for nested symbols.

		Editing changes are signaled with \c #AILayerList::kAIIsolationModeChangedNotifier
		and \c #AILayerList::kAIBeforeIsolationModeChangedNotifier. Use \c #ValidateSymbolEditingArt()
		to validate the art being edited.

		@post Use \c #EndEditingSymbolDefinition() to end the editing session, optionally updating
		the symbol pattern's prototype with the changes in the copy before returning it to
       	the artboard.

		@post Use \c #ExitSymbolEditMode() to force all symbol editing sessions to end without
		saving any changes.

			@param symbolPattern The symbol pattern reference.
			@param symbolArt Optional. A symbol art object whose definition needs to be edited.
		*/
	AIAPI AIErr (*SetEditingSymbolDefinition) ( AIPatternHandle symbolPattern, AIArtHandle symbolArt);

	/** Ends an editing session for a symbol pattern, allowing you to apply or discard the changes
		made during the session. The corresponding symbol instance that was hidden when
	    setting the symbol in edit mode is made visible.
			@param symbolPattern The symbol pattern reference.
			@param updateSymbol True to apply the edits to the pattern, false to discard the editing
				changes and restore the original symbol pattern.
			@pre \c #SetEditingSymbolDefinition()
		*/
	AIAPI AIErr (*EndEditingSymbolDefinition) ( AIPatternHandle symbolPattern, AIBoolean updateSymbol);

	/** Reports whether symbol edit mode is active.
		(Note that this function returns a boolean value, not an error code.)
			@return True if at least one symbol pattern is being edited, false otherwise.
		*/
	AIAPI AIBoolean (*GetSymbolEditMode) ();

	/** Ends all current symbol editing sessions, restoring the original symbol pattern
		prototypes to the artboard and discarding all changes made while editing.

		To save any changes, and to restore the per-symbol editing state information,
		use \c #EndEditingSymbolDefinition() for each symbol being edited.
			@pre \c #SetEditingSymbolDefinition()
		*/
	AIAPI AIErr (*ExitSymbolEditMode) ( );

	/** Reports whether a symbol pattern is currently being edited.
		(Note that this function returns a boolean value, not an error code.)
			@param symbolPattern The symbol pattern reference.
			@return True if at the symbol pattern is being edited, false otherwise.
		*/
	AIAPI AIBoolean (*EditingSymbolPattern) (AIPatternHandle symbolPattern);

	/** Reports whether an art object represents the prototype of a symbol pattern that is
		currently being edited, and if true, optionally returns the pattern being edited.
			@param art			 The art object reference.
			@param symbolPattern [out] Optional. A buffer in which to return the symbol pattern.
			@return True if the art object does represent the prototype of a symbol pattern that is
				currently being edited, false otherwise.
		*/
	AIAPI AIBoolean (*IsSymbolEditingArtType) ( AIArtHandle art, AIPatternHandle *symbolPattern);

	/** Validates the editing art object that represents the prototype of a
		symbol pattern that is being edited.
		The editing art could become invalid due to operations such as duplicate or delete.
		If the symbol pattern's editing art is not a valid art object, looks under the parent
		for an art object whose state represents the editing art of the given symbol pattern,
		and sets it as the valid editing art. If there is no valid art object under the parent,
		creates an empty group and sets it as the valid editing art.

		Use this in response to the \c #AILayerList::kAIBeforeIsolationModeChangedNotifier,
		with the information received by calling \c #AIIsolationModeSuite::GetIsolatedArtAndParents().
			@param symbolPattern The symbol pattern reference.
			@param editingArtParent	Parent object that contains the editing art. 
		*/
	AIAPI AIErr (*ValidateSymbolEditingArt) ( AIPatternHandle symbolPattern, AIArtHandle editingArtParent);


} AI140SymbolSuite;


#include "AIHeaderEnd.h"


#endif
