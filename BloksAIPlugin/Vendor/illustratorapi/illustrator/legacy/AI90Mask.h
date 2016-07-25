#ifndef __AI90Mask__
#define __AI90Mask__

/*
 *        Name:	AI90Mask.h
 *   $Revision: 2 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 9.0 Mask Suite.
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

#include "AIMask.h"


#include "AIHeaderBegin.h"

/*******************************************************************************
 **
 **	Suite name and version
 **
 **/

#define kAI90BlendStyleSuite			"AI Blend Style Suite"
#define kAIBlendStyleSuiteVersion1		AIAPI_VERSION(1)
#define kAI90BlendStyleVersion			kAIBlendStyleSuiteVersion1

#define kAI90MaskSuite					"AI Mask Suite"
#define kAIMaskSuiteVersion1			AIAPI_VERSION(2)
#define kAI90MaskVersion				kAIMaskSuiteVersion1



/*******************************************************************************
 **
 **	Types
 **
 **/


/*******************************************************************************
 **
 **	Suite
 **
 **/


/* The blend style suite allows manipulation of the compositing attributes
	of object styles. */
typedef struct {
	
	/* The following methods are a short hand for getting the object's style
		and then modifying the opacity applied by the style to the object as
		a whole. */
	AIAPI AIBlendingMode (*GetBlendingMode) (AIArtHandle art);
	AIAPI AIErr (*SetBlendingMode) (AIArtHandle art, AIBlendingMode mode);
	
	AIAPI AIReal (*GetOpacity) (AIArtHandle art);
	AIAPI AIErr (*SetOpacity) (AIArtHandle art, AIReal opacity);
	
	AIAPI AIBoolean (*GetIsolated) (AIArtHandle art);
	AIAPI AIErr (*SetIsolated) (AIArtHandle art, AIBoolean isolated);
	
	AIAPI AIKnockout (*GetKnockout) (AIArtHandle art);
	AIAPI AIKnockout (*GetInheritedKnockout) (AIArtHandle art); // always explicitly on or off.
	AIAPI AIErr (*SetKnockout) (AIArtHandle art, AIKnockout knockout);
	
	AIAPI AIBoolean (*GetAlphaIsShape) (AIArtHandle art);
	AIAPI AIErr (*SetAlphaIsShape) (AIArtHandle art, AIBoolean alphaIsShape);
	
	/* Copy the compositing attributes applied globally by the style applied
		to the source object to the destination object.*/
	AIAPI AIErr (*Copy) (const AIArtHandle source, AIArtHandle destination);

	/* Manipulate the attributes applied to the object via a dictionary. See
		the definitions above for the names of the appropriate keys. These
		methods are a short hand for first getting the object's style and
		then using the Get/SetStyleAttrs methods. */
	AIAPI AIErr (*GetArtAttrs) (AIArtHandle art, AIDictionaryRef attrs);
	AIAPI AIErr (*SetArtAttrs) (AIArtHandle art, AIDictionaryRef attrs);

	/* Manipulate the attributes applied by the style via a dictionary. See
		the definitions above for the names of the appropriate keys. */
	AIAPI AIErr (*GetStyleAttrs) (AIArtStyleHandle style, AIDictionaryRef attrs);
	AIAPI AIErr (*SetStyleAttrs) (AIArtStyleHandle style, AIDictionaryRef attrs,
								  AIArtStyleHandle* newStyle);

	/* Manipulate the attributes applied by a specific filter element of an
		active style via a dictionary. See the definitions above for the names
		of the appropriate keys. * /
	AIAPI AIErr (*GetFilterAttrs) (AIStyleFilterExecHandle filter, AIDictionaryRef style);
	AIAPI AIErr (*SetFilterAttrs) (AIStyleFilterExecHandle filter, AIDictionaryRef attrs);*/
	
	/* Get and set the transparency attributes for the current selection in the document */
	AIAPI AIErr (*GetCurrentTransparency) (AIDictionaryRef styleAttrs,
										   AIDictionaryRef fillAttrs,
										   AIDictionaryRef strokeAttrs);
	AIAPI AIErr (*SetCurrentTransparency) (AIDictionaryRef styleAttrs,
										   AIDictionaryRef fillAttrs,
										   AIDictionaryRef strokeAttrs);
	
	AIAPI AIErr (*GetFocalFillAttrs) (AIArtStyleHandle artStyle, AIDictionaryRef attrs);
	AIAPI AIErr (*GetFocalStrokeAttrs) (AIArtStyleHandle artStyle, AIDictionaryRef attrs);
	AIAPI AIErr (*SetFocalFillAttrs) (AIArtStyleHandle artStyle, AIDictionaryRef attrs,
											 AIArtStyleHandle* newStyle);
	AIAPI AIErr (*SetFocalStrokeAttrs) (AIArtStyleHandle artStyle, AIDictionaryRef attrs,
											   AIArtStyleHandle* newStyle );

} AI90BlendStyleSuite;


typedef struct {

	/* Masks are reference counted. Call Release once you are done with
		a mask to free its memory. */
	AIAPI ASInt32 (*AddRef) (AIMaskRef mask);
	AIAPI ASInt32 (*Release) (AIMaskRef mask);

	/* GetMask obtains the mask associated with an object if any. */
	AIAPI AIErr (*GetMask) (AIArtHandle object, AIMaskRef* mask);

	/* Create a mask for an object if it doesn't already have one. The
		art of the newly created mask is an empty group object. */
	AIAPI AIErr (*CreateMask) (AIArtHandle object);

	/* Delete the mask associated with an object. */
	AIAPI AIErr (*DeleteMask) (AIArtHandle object);

	/* The link state controls whether the mask is linked to the object.
		When the mask is linked certain actions on the object automatically
		apply to the mask. For example, rotating the object will also
		rotate the mask. */
	AIAPI AIBoolean (*GetLinked) (AIMaskRef mask);
	AIAPI AIErr (*SetLinked) (AIMaskRef mask, AIBoolean linked);

	/* The disabled state controls whether the mask is ignored for rendering
		purposes. */
	AIAPI AIBoolean (*GetDisabled) (AIMaskRef mask);
	AIAPI AIErr (*SetDisabled) (AIMaskRef mask, AIBoolean disabled);

	/* The inverted state controls whether the opacity of the mask is
		inverted before being applied. */
	AIAPI AIBoolean (*GetInverted) (AIMaskRef mask);
	AIAPI AIErr (*SetInverted) (AIMaskRef mask, AIBoolean inverted);

	/* Copy the mask and the link status. */
	AIAPI AIErr (*Copy) (const AIArtHandle source, AIArtHandle destination);

	/* GetArt returns the handle to the mask art which will be NULL if there
		is none. */
	AIAPI AIArtHandle (*GetArt) (AIMaskRef mask);

	/* Methods to query and manipulate whether the mask art is being edited. */
	AIAPI AIBoolean (*IsEditingArt) (AIMaskRef mask);
	AIAPI AIErr (*SetEditingArt) (AIMaskRef mask, AIBoolean isedit);

	/* If "mask" is a group object which is the mask art for some other object
		then on return "masked" will be the masked object. If not then
		"masked" will be nil on return. */
	AIAPI AIErr (*GetMaskedArt) (AIArtHandle mask, AIArtHandle* masked);

} AI90MaskSuite;


#include "AIHeaderEnd.h"


#endif
