#ifndef __AI120ArtStyleParser__
#define __AI120ArtStyleParser__

/*
 *        Name:	AI120ArtStyleParser.h
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

#define kAI120ArtStyleParserSuite			kAIArtStyleParserSuite
#define kAIArtStyleParserSuiteVersion3		AIAPI_VERSION(3)
#define kAI120ArtStyleParserSuiteVersion	kAIArtStyleParserSuiteVersion3


/*******************************************************************************
 **
 **	Suite
 **
 **/

/* Illustrator 12.0 Art Style Parser Suite */
typedef struct {

	AIAPI AIErr (*NewParser) ( AIStyleParser* parser );
	AIAPI AIErr (*DisposeParser) ( AIStyleParser parser );

	AIAPI AIErr (*ParseStyle) ( AIStyleParser parser, AIArtStyleHandle artStyle );

	AIAPI AIErr (*MergeStyleIntoParser) ( AIStyleParser parser, AIArtStyleHandle artStyle );

	AIAPI AIBoolean (*IsStyleParseable) ( AIStyleParser parser );

	AIAPI ASInt32 (*CountPreEffects) ( AIStyleParser parser );
	AIAPI ASInt32 (*CountPostEffects) ( AIStyleParser parser );
	AIAPI ASInt32 (*CountPaintFields) ( AIStyleParser parser );
	AIAPI ASInt32 (*CountEffectsOfPaintField) ( AIParserPaintField paintField );

	AIAPI AIErr (*GetNthPreEffect) ( AIStyleParser parser, ASInt32 n, AIParserLiveEffect* effect );
	AIAPI AIErr (*GetNthPostEffect) ( AIStyleParser parser, ASInt32 n, AIParserLiveEffect* effect );
	AIAPI AIErr (*GetNthPaintField) ( AIStyleParser parser, ASInt32 n, AIParserPaintField* paintField );
	AIAPI AIErr (*GetNthEffectOfPaintField) ( AIParserPaintField paintField, ASInt32 n,
											  AIParserLiveEffect* effect );

	AIAPI AIErr (*GetStyleBlendField) ( AIStyleParser parser, AIParserBlendField* blendField );

	AIAPI AIErr (*InsertNthPreEffect) ( AIStyleParser parser, ASInt32 n, AIParserLiveEffect effect );
	AIAPI AIErr (*InsertNthPostEffect) ( AIStyleParser parser, ASInt32 n, AIParserLiveEffect effect );
	AIAPI AIErr (*InsertNthPaintField) ( AIStyleParser parser, ASInt32 n, AIParserPaintField paintField );
	AIAPI AIErr (*InsertNthEffectOfPaintField) ( AIStyleParser parser, AIParserPaintField paintField, ASInt32 n,
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

	AIAPI ASInt32 (*GetGroupContentsPosition) ( AIStyleParser parser );
	AIAPI AIErr (*MoveGroupContentsPosition) ( AIStyleParser parser, ASInt32 position );

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
	AIAPI ASInt32 (*GetColorPosn) ( AIParserPaintField paintField );
	AIAPI AIErr (*SetColorPosn) ( AIParserPaintField paintField, ASInt32 colorPosn );
	AIAPI AIErr (*ClonePaintField) ( AIParserPaintField paintField, AIParserPaintField* clonedPaintField );
	AIAPI AIErr (*GetPaintLiveEffectInfo) ( AIParserPaintField paintField, AILiveEffectHandle* liveEffectHandle,
											AILiveEffectParameters* params );
	AIAPI AIErr (*SetPaintLiveEffectInfo) ( AIParserPaintField paintField, AILiveEffectHandle liveEffectHandle,
											AILiveEffectParameters params );

	AIAPI AIErr (*GetBlendDictionary) ( AIParserBlendField blendField, AIDictionaryRef blendDict );
	AIAPI AIErr (*SetBlendDictionary) ( AIParserBlendField blendField, AIDictionaryRef blendDict );

	// NEW FOR AI10

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

} AI120ArtStyleParserSuite;


#include "AIHeaderEnd.h"


#endif
