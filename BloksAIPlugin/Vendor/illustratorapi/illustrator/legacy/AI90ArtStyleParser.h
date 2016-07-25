/*
 *        Name:	AI90ArtStyleParser.h
 *     Purpose:	Adobe Illustrator 9.0 Art Style Parser Suite.
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

#ifndef __AI90ArtStyleParser__
#define __AI90ArtStyleParser__


/*******************************************************************************
 **
 **	Imports
 **
 **/

#include "AIArtStyleParser.h"

#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI90ArtStyleParserSuite			kAIArtStyleParserSuite
#define kAIArtStyleParserSuiteVersion2		AIAPI_VERSION(2)
#define kAI90ArtStyleParserSuiteVersion		kAIArtStyleParserSuiteVersion2


/*******************************************************************************
 **
 **	Suite
 **
 **/

/* Suite for parsing and editing styles on art objects */
typedef struct {

	// Allocate and delete a parser
	AIAPI AIErr (*NewParser) ( AIStyleParser* parser );
	AIAPI AIErr (*DisposeParser) ( AIStyleParser parser );

	// Initialize a style parser
	AIAPI AIErr (*ParseStyle) ( AIStyleParser parser, AIArtStyleHandle artStyle );
	AIAPI AIErr (*MergeStyleIntoParser) ( AIStyleParser parser, AIArtStyleHandle artStyle );
	AIAPI AIBoolean (*IsStyleParseable) ( AIStyleParser parser );
		// Calls to IsStyleParseable make sense only immediately after ParseStyle
	
	// Count the number of elements inside the parser
	AIAPI ASInt32 (*CountPreEffects) ( AIStyleParser parser );
	AIAPI ASInt32 (*CountPostEffects) ( AIStyleParser parser );
	AIAPI ASInt32 (*CountPaintFields) ( AIStyleParser parser );
	AIAPI ASInt32 (*CountEffectsOfPaintField) ( AIParserPaintField paintField );
	
	// Retrieve elements from the parser
	AIAPI AIErr (*GetNthPreEffect) ( AIStyleParser parser, ASInt32 n, AIParserLiveEffect* effect );
	AIAPI AIErr (*GetNthPostEffect) ( AIStyleParser parser, ASInt32 n, AIParserLiveEffect* effect );
	AIAPI AIErr (*GetNthPaintField) ( AIStyleParser parser, ASInt32 n, AIParserPaintField* paintField );
	AIAPI AIErr (*GetNthEffectOfPaintField) ( AIParserPaintField paintField, ASInt32 n,
											  AIParserLiveEffect* effect );
	AIAPI AIErr (*GetStyleBlendField) ( AIStyleParser parser, AIParserBlendField* blendField );
	
	// Insert elements into the parser at specified places and indices. Use index -1 to insert element
	// at the end.
	AIAPI AIErr (*InsertNthPreEffect) ( AIStyleParser parser, ASInt32 n, AIParserLiveEffect effect );
	AIAPI AIErr (*InsertNthPostEffect) ( AIStyleParser parser, ASInt32 n, AIParserLiveEffect effect );
	AIAPI AIErr (*InsertNthPaintField) ( AIStyleParser parser, ASInt32 n, AIParserPaintField paintField );
	AIAPI AIErr (*InsertNthEffectOfPaintField) ( AIStyleParser parser, AIParserPaintField paintField, ASInt32 n,
												 AIParserLiveEffect effect );

	// Remove elements from the parser. The doDelete boolean lets the parser know whether it can
	// dispose of the memory associated with the element. Plugins may not want to have the 
	// memory disposed if they are moving the elements from one position to another.
	AIAPI AIErr (*RemovePreEffect) ( AIStyleParser parser, AIParserLiveEffect effect, AIBoolean doDelete );
	AIAPI AIErr (*RemovePostEffect) ( AIStyleParser parser, AIParserLiveEffect effect, AIBoolean doDelete );
	AIAPI AIErr (*RemovePaintField) ( AIStyleParser parser, AIParserPaintField paintField, AIBoolean doDelete );
	AIAPI AIErr (*RemoveEffectOfPaintField) ( AIStyleParser parser, AIParserPaintField paintField, 
											  AIParserLiveEffect effect, AIBoolean doDelete );
	
	// Simplify the style.
	// RemoveAllEffects removes all the effects in the parser.
	// Simplify removes all the effects and all the paint fields except for the focus fill
	// and focus stroke. Simplify also sets all blends back to normal 100% opaque and places
	// the focus stroke on top of the focus fill.
	AIAPI AIErr (*RemoveAllEffects) ( AIStyleParser parser );
	AIAPI AIErr (*Simplify) ( AIStyleParser parser );
	
	// Miscellaneous utility functions
	AIAPI AIErr (*GetFocusFill) ( AIStyleParser parser, AIParserPaintField* paintField );
	AIAPI AIErr (*GetFocusStroke) ( AIStyleParser parser, AIParserPaintField* paintField );
	AIAPI AIErr (*SetParserFocus) ( AIStyleParser parser, AIParserPaintField paintField );
	AIAPI AIErr (*SetFocus) ( AIArtStyleHandle artStyle, AIStyleParser parser, AIParserPaintField paintField );
		// SetFocus should be called when the given style parser hasn't yet been modified
		// since the call to ParseStyle. The artStyle passed in should be the same one
		// previously passed into ParseStyle. The parser remains linked to the artStyle
		// after this call.
	AIAPI ASInt32 (*GetGroupContentsPosition) ( AIStyleParser parser );
	AIAPI AIErr (*MoveGroupContentsPosition) ( AIStyleParser parser, ASInt32 position );
	
	// CreateNewStyle constructs and returns a new art style handle based on the elements
	// in the given parser. ParseStyle would still need to be called on the new style if
	// a plugin wanted to call SetFocus or EditEffectParameters afterward.
	AIAPI AIErr (*CreateNewStyle) ( AIStyleParser parser, AIArtStyleHandle* artStyle );
	
	// Basic information about the elements in the parser
	AIAPI AIBoolean (*IsStyleVisible) ( AIStyleParser parser );
		// A style is "invisible" if there are no effects, all the paint fields have
		// a none color, and the overall style transparency contains default values.
	AIAPI AIBoolean (*ContainsPaint) ( AIStyleParser parser );
	AIAPI AIBoolean (*ContainsEffects) ( AIStyleParser parser );
	AIAPI AIBoolean (*ContainsTransparency) ( AIStyleParser parser );
	
	// Effect-specific calls
	AIAPI AIErr (*GetLiveEffectHandle) ( AIParserLiveEffect effect, AILiveEffectHandle* liveEffectHandle );
	AIAPI AIErr (*GetLiveEffectParams) ( AIParserLiveEffect effect, AILiveEffectParameters* params );
	AIAPI AIErr (*SetLiveEffectHandle) ( AIParserLiveEffect effect, AILiveEffectHandle liveEffectHandle );
	AIAPI AIErr (*SetLiveEffectParams) ( AIParserLiveEffect effect, AILiveEffectParameters params );
	AIAPI AIErr (*CloneLiveEffect) ( AIParserLiveEffect effect, AIParserLiveEffect* clonedEffect );
	AIAPI AIErr (*EditEffectParameters) ( AIArtStyleHandle artStyle, AIParserLiveEffect effect );
		// EditEffectParameters should be called when the given effect was retrieved from a style
		// parser which hasn't yet been modified since the call to ParseStyle. The artStyle
		// passed in should be the same one previously passed into ParseStyle. The parser remains
		// linked to the artStyle after this call. However, a new style will have been created if
		// the user modifies the parameters, and this new style is neither linked to the parser
		// nor the same one as the original artStyle.
	
	// PaintField-specific calls
	// AIArtStylePaintData currently ignored in GetStroke and SetStroke
	AIAPI AIBoolean (*IsFill) ( AIParserPaintField paintField );
	AIAPI AIBoolean (*IsStroke) ( AIParserPaintField paintField );
	AIAPI AIErr (*GetFill) ( AIParserPaintField paintField, AIFillStyle* fill, AIArtStylePaintData* paintData );
	AIAPI AIErr (*GetStroke) ( AIParserPaintField paintField, AIStrokeStyle* stroke, AIArtStylePaintData* paintData );
	AIAPI AIErr (*SetFill) ( AIParserPaintField paintField, AIFillStyle* fill, AIArtStylePaintData* paintData );
	AIAPI AIErr (*SetStroke) ( AIParserPaintField paintField, AIStrokeStyle* stroke, AIArtStylePaintData* paintData );
	AIAPI AIErr (*GetPaintBlendDictionary) ( AIParserPaintField paintField, AIDictionaryRef blendDict );
	AIAPI AIErr (*SetPaintBlendDictionary) ( AIParserPaintField paintField, AIDictionaryRef blendDict );
	AIAPI ASInt32 (*GetColorPosn) ( AIParserPaintField paintField );
	AIAPI AIErr (*SetColorPosn) ( AIParserPaintField paintField, ASInt32 colorPosn );
	AIAPI AIErr (*ClonePaintField) ( AIParserPaintField paintField, AIParserPaintField* clonedPaintField );
	// PaintFields can contain live effects which substitute for the built-in fill and stroke behaviors
	AIAPI AIErr (*GetPaintLiveEffectInfo) ( AIParserPaintField paintField, AILiveEffectHandle* liveEffectHandle,
											AILiveEffectParameters* params );
	AIAPI AIErr (*SetPaintLiveEffectInfo) ( AIParserPaintField paintField, AILiveEffectHandle liveEffectHandle,
											AILiveEffectParameters params );

	// Transparency-specific calls
	AIAPI AIErr (*GetBlendDictionary) ( AIParserBlendField blendField, AIDictionaryRef blendDict );
	AIAPI AIErr (*SetBlendDictionary) ( AIParserBlendField blendField, AIDictionaryRef blendDict );

} AI90ArtStyleParserSuite;


#include "AIHeaderEnd.h"


#endif
