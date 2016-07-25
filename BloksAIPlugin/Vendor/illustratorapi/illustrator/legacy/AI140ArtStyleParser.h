#ifndef __AI140ArtStyleParser__
#define __AI140ArtStyleParser__

/*
 *        Name:	AI140ArtStyleParser.h
 *     Purpose:	Adobe Illustrator Art Style Parser Suite.
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

#include "AIArtStyleParser.h"

#include "AIHeaderBegin.h"

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI140ArtStyleParserSuite			kAIArtStyleParserSuite
#define kAIArtStyleParserSuiteVersion5		AIAPI_VERSION(5)
#define kAI140ArtStyleParserSuiteVersion	kAIArtStyleParserSuiteVersion5


/*******************************************************************************
 **
 **	Suite
 **
 **/

/* Illustrator 14.0 Art Style Parser Suite */
typedef struct {
	AIAPI AIErr (*NewParser) ( AIStyleParser* parser );

	AIAPI AIErr (*DisposeParser) ( AIStyleParser parser );

	AIAPI AIErr (*ParseStyle) ( AIStyleParser parser, AIArtStyleHandle artStyle );

	AIAPI AIErr (*MergeStyleIntoParser) ( AIStyleParser parser, AIArtStyleHandle artStyle );

	AIAPI AIBoolean (*IsStyleParseable) ( AIStyleParser parser );

	AIAPI ai::int32 (*CountPreEffects) ( AIStyleParser parser );

	AIAPI ai::int32 (*CountPostEffects) ( AIStyleParser parser );

	AIAPI ai::int32 (*CountPaintFields) ( AIStyleParser parser );

	AIAPI ai::int32 (*CountEffectsOfPaintField) ( AIParserPaintField paintField );

	AIAPI AIErr (*GetNthPreEffect) ( AIStyleParser parser, ai::int32 n, AIParserLiveEffect* effect );

	AIAPI AIErr (*GetNthPostEffect) ( AIStyleParser parser, ai::int32 n, AIParserLiveEffect* effect );

	AIAPI AIErr (*GetNthPaintField) ( AIStyleParser parser, ai::int32 n, AIParserPaintField* paintField );

	AIAPI AIErr (*GetNthEffectOfPaintField) ( AIParserPaintField paintField, ai::int32 n,
		AIParserLiveEffect* effect );

	AIAPI AIErr (*GetStyleBlendField) ( AIStyleParser parser, AIParserBlendField* blendField );

	AIAPI AIErr (*InsertNthPreEffect) ( AIStyleParser parser, ai::int32 n, AIParserLiveEffect effect );

	AIAPI AIErr (*InsertNthPostEffect) ( AIStyleParser parser, ai::int32 n, AIParserLiveEffect effect );

	AIAPI AIErr (*InsertNthPaintField) ( AIStyleParser parser, ai::int32 n, AIParserPaintField paintField );

	AIAPI AIErr (*InsertNthEffectOfPaintField) ( AIStyleParser parser, AIParserPaintField paintField, ai::int32 n,
												 AIParserLiveEffect effect );

	AIAPI AIErr (*RemovePreEffect) ( AIStyleParser parser, AIParserLiveEffect effect, AIBoolean doDelete );

	AIAPI AIErr (*RemovePostEffect) ( AIStyleParser parser, AIParserLiveEffect effect, AIBoolean doDelete );

	AIAPI AIErr (*RemovePaintField) ( AIStyleParser parser, AIParserPaintField paintField, AIBoolean doDelete );

	AIAPI AIErr (*RemoveEffectOfPaintField) ( AIStyleParser parser, AIParserPaintField paintField,
											  AIParserLiveEffect effect, AIBoolean doDelete );

	AIAPI AIErr (*RemoveAllEffects) ( AIStyleParser parser );

	AIAPI AIErr (*Simplify) ( AIStyleParser parser );

	AIAPI AIErr (*GetFocusFill) ( AIStyleParser parser, AIParserPaintField* paintField );

	AIAPI AIErr (*GetFocusStroke) ( AIStyleParser parser, AIParserPaintField* paintField );

	AIAPI AIErr (*SetParserFocus) ( AIStyleParser parser, AIParserPaintField paintField );

	AIAPI AIErr (*SetFocus) ( AIArtStyleHandle artStyle, AIStyleParser parser, AIParserPaintField paintField );

	AIAPI ai::int32 (*GetGroupContentsPosition) ( AIStyleParser parser );

	AIAPI AIErr (*MoveGroupContentsPosition) ( AIStyleParser parser, ai::int32 position );

	AIAPI AIErr (*CreateNewStyle) ( AIStyleParser parser, AIArtStyleHandle* artStyle );

	AIAPI AIBoolean (*IsStyleVisible) ( AIStyleParser parser );

	AIAPI AIBoolean (*ContainsPaint) ( AIStyleParser parser );

	AIAPI AIBoolean (*ContainsEffects) ( AIStyleParser parser );

	AIAPI AIBoolean (*ContainsTransparency) ( AIStyleParser parser );

	AIAPI AIErr (*GetLiveEffectHandle) ( AIParserLiveEffect effect, AILiveEffectHandle* liveEffectHandle );

	AIAPI AIErr (*GetLiveEffectParams) ( AIParserLiveEffect effect, AILiveEffectParameters* params );

	AIAPI AIErr (*SetLiveEffectHandle) ( AIParserLiveEffect effect, AILiveEffectHandle liveEffectHandle );

	AIAPI AIErr (*SetLiveEffectParams) ( AIParserLiveEffect effect, AILiveEffectParameters params );

	AIAPI AIErr (*CloneLiveEffect) ( AIParserLiveEffect effect, AIParserLiveEffect* clonedEffect );

	AIAPI AIErr (*EditEffectParameters) ( AIArtStyleHandle artStyle, AIParserLiveEffect effect );

	AIAPI AIBoolean (*IsFill) ( AIParserPaintField paintField );

	AIAPI AIBoolean (*IsStroke) ( AIParserPaintField paintField );

	AIAPI AIErr (*GetFill) ( AIParserPaintField paintField, AIFillStyle* fill, AIArtStylePaintData* paintData );

	AIAPI AIErr (*GetStroke) ( AIParserPaintField paintField, AIStrokeStyle* stroke, AIArtStylePaintData* paintData );

	AIAPI AIErr (*SetFill) ( AIParserPaintField paintField, AIFillStyle* fill, AIArtStylePaintData* paintData );

	AIAPI AIErr (*SetStroke) ( AIParserPaintField paintField, AIStrokeStyle* stroke, AIArtStylePaintData* paintData );

	AIAPI AIErr (*GetPaintBlendDictionary) ( AIParserPaintField paintField, AIDictionaryRef blendDict );

	AIAPI AIErr (*SetPaintBlendDictionary) ( AIParserPaintField paintField, AIDictionaryRef blendDict );

	AIAPI ai::int32 (*GetColorPosn) ( AIParserPaintField paintField );

	AIAPI AIErr (*SetColorPosn) ( AIParserPaintField paintField, ai::int32 colorPosn );

	AIAPI AIErr (*ClonePaintField) ( AIParserPaintField paintField, AIParserPaintField* clonedPaintField );

	AIAPI AIErr (*GetPaintLiveEffectInfo) ( AIParserPaintField paintField, AILiveEffectHandle* liveEffectHandle,
											AILiveEffectParameters* params );
	AIAPI AIErr (*SetPaintLiveEffectInfo) ( AIParserPaintField paintField, AILiveEffectHandle liveEffectHandle,
											AILiveEffectParameters params );
	AIAPI AIErr (*GetBlendDictionary) ( AIParserBlendField blendField, AIDictionaryRef blendDict );

	AIAPI AIErr (*SetBlendDictionary) ( AIParserBlendField blendField, AIDictionaryRef blendDict );

	AIAPI AIErr (*GetEvenOdd) ( AIParserPaintField paintField, AIBoolean* evenodd );
	AIAPI AIErr (*SetEvenOdd) ( AIParserPaintField paintField, AIBoolean evenodd );
	AIAPI AIErr (*NewPaintFieldFill) ( const AIFillStyle* fill, AIBoolean evenOdd, const AIArtStylePaintData* paintData,
									   AIParserPaintField* paintField );
	AIAPI AIErr (*NewPaintFieldStroke) ( const AIStrokeStyle* stroke, const AIArtStylePaintData* paintData,
										 AIParserPaintField* paintField );

	AIAPI AIErr (*DisposePaintField) ( AIParserPaintField paintField );

	AIAPI AIErr (*NewParserLiveEffect) ( AILiveEffectHandle liveEffectHandle, AILiveEffectParameters params,
										 AIParserLiveEffect* effect );

	AIAPI AIErr (*DisposeParserLiveEffect) ( AIParserLiveEffect effect );

	AIAPI AIErr (*GetCurrentArtStyle) ( AIArtStyleHandle* style );

	AIAPI AIErr (*EditPaintEffectParameters) ( AIArtStyleHandle artStyle, AIParserPaintField paintField );

	AIAPI AIBoolean (*IsNormalOpaquePaintBlend) ( AIParserPaintField paintField );

	AIAPI AIBoolean (*IsNormalOpaqueBlend) ( AIParserBlendField blendField );

	AIAPI AIBoolean (*IsDefaultPaintBlend) ( AIParserPaintField paintField );

	AIAPI AIErr (*SetDefaultPaintBlend) ( AIParserPaintField paintField );

	AIAPI AIBoolean (*IsDefaultBlend) ( AIParserBlendField blendField );

	AIAPI AIErr (*SetDefaultBlend) ( AIParserBlendField blendField, AIBoolean knockoutOff );

	AIAPI AIBoolean (*IsStyleSimple) ( AIStyleParser parser );

	AIAPI AIErr (*GetLiveEffectNameAndVersion) ( AIParserLiveEffect effect, const char** name, ai::int32* major, ai::int32* minor );

	AIAPI AIErr (*GetPaintLiveEffectNameAndVersion) ( AIParserPaintField paintField, const char** name, ai::int32* major, ai::int32* minor );

	AIAPI AIBoolean (*CompareStyles) ( AIStyleParser parserStyle1, AIStyleParser parserStyle2);

	AIAPI AIErr (*GetEffectVisible) ( AIParserLiveEffect effect, AIBoolean *visible);
		
	AIAPI AIErr (*SetEffectVisible) ( AIArtStyleHandle artStyle, AIParserLiveEffect effect, AIBoolean visible );

	AIAPI AIErr (*GetPaintFieldVisible) ( AIParserPaintField paintField, AIBoolean *visible);
	
	AIAPI AIErr (*SetPaintFieldVisible) ( AIArtStyleHandle artStyle, AIParserPaintField paintField, AIBoolean visible );

	AIAPI AIErr (*GetBlendFieldVisible) ( AIParserBlendField blendField, AIBoolean *visible);
	
	AIAPI AIErr (*SetBlendFieldVisible) ( AIArtStyleHandle artStyle, AIParserBlendField blendField, AIBoolean visible );

	AIAPI AIErr (*GetPaintBlendVisible) ( AIParserPaintField paintField, AIBoolean *visible);
	
	AIAPI AIErr (*SetPaintBlendVisible) ( AIArtStyleHandle artStyle, AIParserPaintField paintField, AIBoolean visible );

	AIAPI AIErr (*IntersectStyleWithParser) ( AIStyleParser parser, AIArtStyleHandle artStyle );

	AIAPI AIErr (*FindEquivalentPaintField) ( AIStyleParser parser, AIParserPaintField paintField, ai::int32 startIndex, ai::int32* index );

	AIAPI AIErr (*GetFocusEffect) ( AIStyleParser parser, AIParserLiveEffect* effectField );

	AIAPI AIErr (*SetFocusEffect) ( AIArtStyleHandle artStyle, AIStyleParser parser, AIParserLiveEffect effectField );

	AIAPI AIErr (*SetParserFocusEffect) ( AIStyleParser parser, AIParserLiveEffect effectField );

	AIAPI AIErr (*EditEffectParametersInSelection) ( AIParserLiveEffect effectField );

	AIAPI AIErr (*FindEquivalentEffect) ( AIStyleParser parser, AIParserPaintField paintField, AIParserLiveEffect effectField, AIBoolean preEffect, ai::int32 startIndex, ai::int32* index );

	AIAPI AIBoolean (*StyleContainsAttributes) ( AIArtStyleHandle artStyle, AIStyleParser attributes, AIBoolean includeTransparency );

} AI140ArtStyleParserSuite;


#include "AIHeaderEnd.h"


#endif
