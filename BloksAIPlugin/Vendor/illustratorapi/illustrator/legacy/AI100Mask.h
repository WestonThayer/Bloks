#ifndef __AI100Mask__
#define __AI100Mask__

/*
 *        Name:	AI100Mask.h
 *   $Revision: 2 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 10.0 Mask Suite.
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

#ifndef __AIMask__
#include "AIMask.h"
#endif

#include "AIHeaderBegin.h"

/*******************************************************************************
 **
 **	Suite name and version
 **
 **/

#define kAI100BlendStyleSuite			"AI Blend Style Suite"
#define kAIBlendStyleSuiteVersion2		AIAPI_VERSION(2)
#define kAI100BlendStyleVersion			kAIBlendStyleSuiteVersion2


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

	/* Return whether the object (or group, or layer) 
		contains any artwork with non-Normal blending
		that is not isolated at the level of the object. */
	AIAPI AIBoolean (*ContainsNonIsolatedBlending) (AIArtHandle object);
} AI100BlendStyleSuite;



#include "AIHeaderEnd.h"


#endif
