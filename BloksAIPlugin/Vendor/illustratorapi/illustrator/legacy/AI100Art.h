#ifndef __AI100Art__
#define __AI100Art__

/*
 *        Name:	AI100Art.h
 *     Purpose:	Adobe Illustrator 10.0 Artwork Object Suite.
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

#include "AIArt.h"

#include "AIHeaderBegin.h"

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI100ArtSuite			kAIArtSuite
#define kAIArtSuiteVersion9		AIAPI_VERSION(9)
#define kAI100ArtSuiteVersion	kAIArtSuiteVersion9


/*******************************************************************************
 **
 **	Suite
 **
 **/


/* Illustrator 10.0 Art suite */
typedef struct _AI100ArtSuite {

	AIAPI AIErr (*NewArt) ( short type, short paintOrder, AIArtHandle prep, AIArtHandle *newArt );
	AIAPI AIErr (*DisposeArt) ( AIArtHandle art );
	AIAPI AIErr (*ReorderArt) ( AIArtHandle thisArt, short paintOrder, AIArtHandle prep );
	AIAPI AIErr (*DuplicateArt) ( AIArtHandle thisArt, short paintOrder, AIArtHandle prep, AIArtHandle *newArt );

	AIAPI AIErr (*GetFirstArtOfLayer) ( AILayerHandle layer, AIArtHandle *art );
	AIAPI AIErr (*GetLayerOfArt) ( AIArtHandle art, AILayerHandle *layer );
	AIAPI AIErr (*GetArtType) ( AIArtHandle art, short *type );
	AIAPI AIErr (*GetArtUserAttr) ( AIArtHandle art, long whichAttr, long *attr );
	AIAPI AIErr (*SetArtUserAttr) ( AIArtHandle art, long whichAttr, long attr );
	AIAPI AIErr (*GetArtParent) ( AIArtHandle art, AIArtHandle *parent );
	AIAPI AIErr (*GetArtFirstChild) ( AIArtHandle art, AIArtHandle *child );
	AIAPI AIErr (*GetArtSibling) ( AIArtHandle art, AIArtHandle *sibling );
	AIAPI AIErr (*GetArtPriorSibling) ( AIArtHandle art, AIArtHandle *sibling );

	AIAPI AIErr (*GetArtBounds) ( AIArtHandle art, AIRealRect *bounds );
	AIAPI AIErr (*SetArtBounds) ( AIArtHandle art );

	AIAPI AIErr (*GetArtCenterPointVisible) ( AIArtHandle art, AIBoolean *visible );
	AIAPI AIErr (*SetArtCenterPointVisible) ( AIArtHandle art, AIBoolean visible );

	/* New with Illustrator 7.0 */
	AIAPI AIErr (*GetArtTransformBounds) ( AIArtHandle art, AIRealMatrix *transform, long flags, AIRealRect *bounds );
	AIAPI AIErr (*UpdateArtworkLink) ( AIArtHandle art, AIBoolean *updated );

	/* New in Illustrator 8.0 */
	AIAPI AIBoolean (*ValidArt) ( AIArtHandle art );
	AIAPI AIErr (*GetArtOrder) ( AIArtHandle art1, AIArtHandle art2, short *order );
	AIAPI AIErr (*SelectNamedArtOfLayer) ( AILayerHandle layer, char *name, AIBoolean matchWholeWord, AIBoolean caseSensitive );
	AIAPI AIErr (*GetArtRotatedBounds) ( AIArtHandle art, AIReal angle, long flags, AIRealRect *bounds );

	AIAPI AIBoolean (*ArtHasFill) ( AIArtHandle art );
	AIAPI AIBoolean (*ArtHasStroke) ( AIArtHandle art );
	AIAPI AIBoolean (*ArtsHaveEqualPaths) ( AIArtHandle art1, AIArtHandle art2 );
	AIAPI AIErr (*ArtCopyFillStyleIfEqualPaths) ( AIArtHandle dstArt, AIArtHandle srcArt );
	AIAPI AIErr (*ArtCopyStrokeStyleIfEqualPaths) ( AIArtHandle dstArt, AIArtHandle srcArt );

	/* New in Illustrator 9.0 */
	
		/* Any of these parameters may be NULL if not needed. */
	AIAPI AIErr (*GetInsertionPoint) ( AIArtHandle *art, short *paintorder, ASBoolean *editable );
	AIAPI AIErr (*SetInsertionPoint) ( AIArtHandle art );

	AIAPI AIErr (*GetKeyArt) ( AIArtHandle *art );	 
	AIAPI AIErr (*CancelKeyArt) (void);

	/* Returns the dictionary associated with the art object. The same dictionary
		is accessed by the AITag suite but that suite is only capable of
		setting and getting string values. Note that dictionaries are reference
		counted. You must call sAIDictionary->Release() when you're done with
		it. */
	AIAPI AIErr (*GetDictionary) ( AIArtHandle art, struct _AIDictionary** dictionary );
	AIAPI AIErr (*SetArtName) (AIArtHandle art, char const *name);

		/* If there is no user assigned name, a default descriptive name will be
		   returned. *isDefaultName will be set to reflect this. isDefaultName
		   may be null. */
	AIAPI AIErr (*GetArtName) (AIArtHandle art, char name[], int bufferSize, ASBoolean *isDefaultName);

		/* True if art is a group and it corresponds to a layer. */
	AIAPI AIErr (*IsArtLayerGroup) (AIArtHandle art, ASBoolean *isLayerGroup);
	AIAPI AIErr (*ReleaseToLayers) (const AIArtHandle art, ASBoolean build);
	
	/* More efficient than doing one art at a time */
	AIAPI AIErr (*ModifyTargetedArtSet) (AIArtHandle *list, long count, long action);

	/* Return true if art is part of the styled art of another object */
	AIAPI AIBoolean (*IsArtStyledArt) (AIArtHandle art);

	/* Return true if 'art' adds to clipping. Should only be called on
	   descendents of a clipGroup or a maskObject. A return of TRUE indicates
	   'art' is either an appropriate art object with the isClip flag on or a
	   non-clip group with a clipping descendent that isn't bounded by another
	   clipGroup. */
	AIAPI AIBoolean (*IsArtClipping) (AIArtHandle art);


	/* New in Illustrator 10.0 */

	/* Transfers attributes from the source art to the destination. This is intended
		to be used when the destination art is to replace the source art in the art
		tree. For example when an art object is converted from one type to another. */
	AIAPI AIErr (*TransferAttributes) (AIArtHandle srcart, AIArtHandle dstart, unsigned long which);

} AI100ArtSuite;

#include "AIHeaderEnd.h"


#endif
