#ifndef __AI100Symbol__
#define __AI100Symbol__

/*
 *        Name:	AI100Symbol.h
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 10.0 Symbol Suite.
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


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAI100SymbolSuite			kAISymbolSuite
#define kAISymbolSuiteVersion1		AIAPI_VERSION(1)
#define kAI100SymbolSuiteVersion	kAISymbolSuiteVersion1


/*******************************************************************************
 **
 **	AISymbol Suite (legacy AI 10 version)
 **
 **/

// This suite is exported by the core, so it should always be available.
typedef struct {

	// Functions for examining and managing the set of symbols
	AIAPI AIErr (*CountSymbolPatterns) ( long *count, ASBoolean includeUnlisted );
	AIAPI AIErr (*GetNthSymbolPattern) ( long n, AIPatternHandle *symbolPattern, ASBoolean includeUnlisted );
												// This is a zero-based index.
												// (See note at bottom for a discussion of listed vs unlisted.)
	AIAPI AIErr (*GetSymbolPatternByName) ( char *name, AIPatternHandle *symbolPattern );
  
	AIAPI AIErr (*GetSymbolByNameFromDocument) ( char* name, AIPatternHandle *symbolPattern,
												   AIDocumentHandle document );
	AIAPI AIErr (*CountSymbolPatternsFromDocument) ( long* count, AIDocumentHandle document );
	AIAPI AIErr (*GetNthSymbolPatternFromDocument) ( long n, AIPatternHandle *symbolPattern,
													 AIDocumentHandle document );

	AIAPI AIErr (*NewSymbolPattern) ( AIPatternHandle *newSymbolPattern, AIArtHandle definitionArt, ASBoolean unlisted );
												// If definitionArt is not null, it will be copied as the
												// defining art. If it is null, then the definition will
												// be an empty group. (We do not bother making a
												// checkerboard pattern like NewPattern does.)
												// (See note at bottom for a discussion of listed vs unlisted.)
	AIAPI AIErr (*NewSymbolPatternFromSel) ( AIPatternHandle *symbolPattern );
												// If something is selected, it will be copied as the
												// defining art. If nothing is selected, then the definition
												// will be an empty group. (You don't get a choice of unlisted
												// on this one - symbols defined from the selected art are assumed
												// to be permanent.)
	AIAPI AIErr (*NewSymbolPatternFromSelGetBounds) ( AIPatternHandle *symbolPattern, AIRealRect *selectionBounds );
												// Like NewSymbolPatternFromSel except that it returns the bounds
												// of the selected art used to define the symbol (which cannot be
												// obtained by calling GetArtBounds on the symbol pattern art after
												// defining it, because like patterns and brush patterns the copied
												// definition art gets moved to a standardized location.) It could
												// be obtained by getting all the selected objects and unioning up
												// their bounds, but since NewSymbolPatternFromSel knows the bounds
												// anyway it is easy to hand it back. This is mainly intended for
												// clients who want to insert an instance of the symbol in place
												// of the selection after it is created.

	AIAPI AIErr (*DeleteSymbolPattern) ( AIPatternHandle symbolPattern );
	AIAPI AIBoolean (*ValidateSymbolPattern) ( AIPatternHandle symbolPattern );
												// Is this symbol still known to the system?
												// (It should never be necessary to use this if you don't
												// hang onto the AIPatternHandle between messages, or if
												// you process the kAIArtSymbolSetChangedNotifier.)

	// Functions for examining and modifying a symbol definition
	AIAPI AIErr (*GetSymbolPatternArt) ( AIPatternHandle pattern, AIArtHandle *art );
												// This 'peeks' at the actual symbol definition.
												// The art returned cannot be edited, just examined or duplicated!!
	AIAPI AIErr (*PasteSymbolPatternArt) ( AIPatternHandle symbolPattern );
												// analogous to GetBrushPattern & GetPattern
												// (I just don't think 'Get' is a very intuitive
												// name for inserting a copy of the defining art
												// into the current layer or insertion group.)
												// Especially since we use GetPatternArt to mean
												// peek at the real definition.
	AIAPI AIErr (*CopySymbolPatternArt) ( AIPatternHandle symbolPattern,
												short paintOrder, AIArtHandle prep, AIArtHandle *newArt );
												// paintOrder, prep and newArt have the same meaning as DuplicateArt
												// in the AIArt suite.
												// The recommended way to get an editable copy of a symbol definition
												// is not to use PasteSymbolPatternArt, but rather to use NewArtEntry
												// from the AIDictionary suite to create a group that isn't in the
												// artwork, insert the definition copy into that, and then delete
												// the dictionary entry. That way you don't modify the art tree
												// and trigger irrelevant synchronization, change notifications, etc.
												// (This is often used by export filters that need to make systematic
												// adjustments to Illustrator art before getting it in an easy-to-export
												// form.)

	AIAPI AIErr (*SetSymbolPatternArt) ( AIPatternHandle symbolPattern, AIArtHandle definitionArt );
												// Copy the definitionArt as the new symbol definition.
												// Any existing instances of the symbol will be updated.   
	AIAPI AIErr (*SetSymbolPatternFromSel) ( AIPatternHandle symbolPattern );
												// Analogous to SetBrushPattern and SetPattern.
												// Again, I just think that 'Set' isn't very intuitive for something
												// that copies the selected art.

	// The functions below use C strings. If you have or want Pascal strings, you can
	// also get and set the name of a symbol using GetPatternName and SetPatternName
	// from AIPattern.h.
	AIAPI AIErr (*GetSymbolPatternName) ( AIPatternHandle symbolPattern, char *name, int bufferSize );
		// If the actual symbol name is too long to fit in the buffer, it will be filled
		// with a truncated form of the name and kNameTooLongErr will be returned.
	AIAPI AIErr (*SetSymbolPatternName) ( AIPatternHandle symbolPattern, char *name );
		// If the name length exceeds kMaxSymbolNameLength then kNameTooLongErr will be returned
		// If the name contains illegal characters, is of zero length, or consists entirely of spaces,
		// then kInvalidNameErr will be returned. In either case, the symbol will retain the original name.
		// If the name is already used for another symbol, then kNameInUseErr will be returned 
	AIAPI AIErr (*GetSymbolPatternDisplayName) ( char *name );
		// strips any hidden characters from the end of a name. The name is modified in place.
	AIAPI AIErr (*SetSymbolPatternBaseName) ( AIPatternHandle symbolPattern, char *name );
		// Like SetSymbolPatternName, except if the given name is already used, the name will be changed
		// by appending numbers until a unique name is generated. (If the name is very long and already
		// in use, then the prefix may be truncated before appending numbers, but this is unlikely to
		// happen since kSymbolMaxNameLength is so large.)

	// Functions for creating, examining and modifying symbol instances (art objects of type kSymbolArt)
	AIAPI AIErr (*NewInstanceCenteredInView) ( AIPatternHandle symbolPattern,
								short paintOrder, AIArtHandle prep, AIArtHandle *newArt );
	AIAPI AIErr (*NewInstanceAtLocation) ( AIPatternHandle symbolPattern, AIRealPoint center,
								short paintOrder, AIArtHandle prep, AIArtHandle *newArt );
	AIAPI AIErr (*NewInstanceWithTransform) ( AIPatternHandle symbolPattern, AIRealMatrix *transform,
								short paintOrder, AIArtHandle prep, AIArtHandle *newArt );

	// You can also use NewArt from the AIArt suite, which is like NewInstanceCenteredInView where
	// the symbolPattern is the first one in the set. (It will return kBadParameterErr if there are
	// no symbols defined in the current document.)

	AIAPI AIErr (*GetSymbolPatternOfSymbolArt) ( AIArtHandle symbolArt, AIPatternHandle *symbolPattern );
	AIAPI AIErr (*SetSymbolPatternOfSymbolArt) ( AIArtHandle symbolArt, AIPatternHandle symbolPattern );

	// Return the matrix used internally by Illustrator to transform the SymbolPatternArt into an instance
	AIAPI AIErr (*GetHardTransformOfSymbolArt) ( AIArtHandle symbolArt, AIRealMatrix *transform );
	AIAPI AIErr (*SetHardTransformOfSymbolArt) ( AIArtHandle symbolArt, AIRealMatrix *transform );

	// Return the matrix that can be used by a plugin to transform the SymbolPatternArt into an instance
	// (If you are going to be using the TransformArt suite, this is the matrix you want.)
	AIAPI AIErr (*GetSoftTransformOfSymbolArt) ( AIArtHandle symbolArt, AIRealMatrix *transform );
	AIAPI AIErr (*SetSoftTransformOfSymbolArt) ( AIArtHandle symbolArt, AIRealMatrix *transform );

	// You can also translate between the two forms of the matrix using AIRealMatrixRealSoft
	// and AIRealMatrixRealHard from the AIHardSoft suite. (Do not use AIRealMatrixHarden and
	// AIRealMatrixSoften, which harden/soften only the tx ty components.) 

	AIAPI AIErr (*InsertExpandedSymbolArt) ( AIArtHandle symbolArt,
												short paintOrder, AIArtHandle prep, AIArtHandle *expandedArt );
												// paintOrder, prep and newArt have the same meaning as DuplicateArt
												// in the AIArt suite.
												// If the instance matrix is a simple placement matrix, then this
												// function is equivalent to BreakLinkToSymbol, see below. If the
												// instance matrix includes a scale, rotation, shear or reflection
												// then it expands any appearances or plugin groups inside the symbol
												// definition, followed by a transformation by the instance matrix.
												// Also if the instance matrix includes a shear or a non-uniform
												// scale, it expands strokes before applying the instance matrix.
												// This routine thus preserves appearance of the instance at the
												// cost of preserving the original editability of the symbol definition.  
												// Does not delete symbolArt.

	// Functions for listing, unlisting and sorting listed symbols
	AIAPI AIBoolean (*IsSymbolPatternListed) ( AIPatternHandle symbolPattern );
	AIAPI AIErr (*MakeSymbolPatternListed) ( AIPatternHandle symbolPattern );
	AIAPI AIErr (*UnlistSymbolPattern) ( AIPatternHandle symbolPattern );

	AIAPI AIErr (*SortListedSymbolPatterns) ( void );
	AIAPI AIErr (*MoveSymbolPatternInList) ( AIPatternHandle symbolPattern, int index );
											// Make the listed symbolPattern have the given index
											// Use -1 to move to end of list

	// Function for examining symbol usage
	AIAPI AIBoolean (*ArtUsesSymbolPattern) ( AIArtHandle art, short searchScope, AIPatternHandle targetSymbol,
											AIPatternHandle *oneFoundSymbol,
											AIPatternHandle ***allFoundSymbols, int *foundCount,
											int *globalObjectUsage);
		/* Check to see whether the given art object uses the targetSymbol.
			searchScope is a bit vector; see the flags defined above

			If the art object is null, then the entire artwork is searched. In this case,
			the kSearchDescendants flag is assumed even if it is not on in the searchScope,
			because it is meaningless to search the whole artwork unless you look inside layer groups.

			The targetSymbol can be null; if so the art is searched for any symbol usage
			If the targetSymbol is not null, then the remaining three parameters are all ignored!

			The oneFoundSymbol pointer can also be null. It is ignored if targetSymbol is not null.
			If targetSymbol is null, and oneFoundSymbol is not null, and the art object uses exactly
				one symbol within the scope searched, then *oneFoundSymbol will be returned as that symbol.
			If it uses multiple symbols, the function returns true but *oneFoundSymbol is returned null.
			If it uses multiple symbols and allFoundSymbols is non-null, then *allFoundSymbols is returned
				as a handle to an array of all those symbols and *foundCount. Like the AIMatchingArt
				suite, the memory is allocated by ArtUsesSymbolPattern, and must be freed by the
				calling plugin using MdMemoryDisposeHandle.
			*oneFoundSymbol is mostly intended for the Symbols palette to decide which symbol to select,
				and if an object uses multiple symbols then nothing is selected. The searchScope in this
				type of usage should not include kSearchNestedSymbolPatterns, because if symbol A's
				definition includes symbol B, and the user selects an instance of symbol A, we want
				to consider symbol A to be selected. But if they select a particle set containing
				instances of both symbol A and symbol B, we want to select neither symbol in the palette. 
			*allFoundSymbols with a null art object is mostly intended for implementing the
				"Select All Unused" command in the Symbols palette.
			*allFoundSymbols with a non-null art object is mostly intended for examining which symbol
				patterns are referenced by a plugin group that puts multiple symbols in its dictionary,
				such as a particle set.

			If globalObjectUsage is not null, we additionally report whether the symbol was found inside
				graph designs or inside other symbols. (This does not affect the searchScope, so if there
				was a non-null input art object, any non-zero return value will mean that it was found
				inside a graph design or symbol that was used in that object.)
		*/

	AIAPI AIErr (*BreakLinkToSymbol) ( AIArtHandle symbolArt,
												short paintOrder, AIArtHandle prep, AIArtHandle *expandedArt );
										// paintOrder, prep and newArt have the same meaning as DuplicateArt
										// in the AIArt suite.
										// Like CopySymbolPatternArt for the symbolArt's symbolPattern
										// followed by a transformation by the instance matrix, but
										// more efficient than using the TransformArt suite since
										// it is all done internally. Also transfers attributes from
										// the symbol instance to the transformed defintion.
										// If the instance matrix is a simple placement matrix, then this
										// function is equivalent to InsertExpandedSymbolArt, see above,
										// since neither function does any deep expansion when the matrix
										// is simple. But this function does not do any internal expansion
										// of strokes, active styles or plugin groups inside the symbol
										// definition even when a rotational or shear transform is applied
										// to the instance. Since transforming an object containing such
										// active elements is not always visually identical to transforming
										// what it "looks like", this routine preserves the full structure
										// and editability of the symbol definition, at the cost of sometimes
										// not preserving the appearance of the instance.  
										// Does not delete symbolArt.

	AIAPI AIErr (*RetargetForCurrentDocument) ( AIPatternHandle srcPattern, AIPatternHandle *dstPattern );
		/*	Analogous to functions by the same name in AIArtStyle, AIObjectSet and AIPathStyle.
			Intended primarily for drag-and-drop between library palettes and the main document
			palette.

			This function can be safely used with fill patterns and brush patterns as well as
			with symbol patterns (see the AIPattern and AIBrushPattern suites.) Therefore the
			description below refers to "patterns". This should be taken to mean a symbol pattern
			if passed a symbol pattern, a fill pattern if passed a fill pattern, etc.

			The function was not needed for fill patterns because they are usually retargetted
			indirectly using the AIPathStyle suite, and it was not needed for brush patterns
			because they are usually retargetted indirectly using the AIObjectSet suite. But
			there is no corresponding data structure that wraps around a symbol pattern in
			a palette.

			If the srcPattern is in the current document, just returns it back.
			If the srcPattern is not in the current document, but there is already a pattern
			   in the current document with the same name and the same definition, returns the
			   handle to that pattern.
			If the srcPattern is not in the current document and there is no pattern with the
			   same name and definition, then it creates a new pattern in the current document
			   with the same definition art, and a name based on the srcPattern's name (possibly
			   appending numbers if the srcPattern's name is assigned to a pattern in the current
			   document with a different definition.) All other global objects (colors, patterns,
			   brushes, styles, etc.) used indirectly in the definition are similarly retargetted,
			   using an existing object if one matches and creating a new one otherwise.

			For purposes of determining sameness, a listed symbol never matches an unlisted one,
			even if they otherwise have the same name and definition.
		*/

} AI100SymbolSuite;


#include "AIHeaderEnd.h"


#endif
