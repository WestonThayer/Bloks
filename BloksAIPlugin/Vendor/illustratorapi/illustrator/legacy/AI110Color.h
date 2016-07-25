#ifndef __AI110Color__
#define __AI110Color__

/*
 *        Name:	AI110Color.h
 *   $Revision: 17 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 6.0 Color Suite.
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

#include "AIColor.h"

#include "AIHeaderBegin.h"

/** @file AIColor.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

/** Custom colors define named colors. The appearance of the named color is
	defined by a color of one of these types. */
typedef enum {
	/** Solid ink, expressed in four process colors */
	kAI110CustomFourColor = 0,
	/** RGB colors */
	kAI110CustomThreeColor
} AI110CustomColorTag;


/*******************************************************************************
 **
 **	Types
 **
 **/

/** The union of all possible process colors that can be associated with
	a custom color. */
typedef union {
	AIFourColorStyle	f;
	AIThreeColorStyle	rgb;
	AIGrayColorStyle	gray;
} AI110CustomColorUnion;

/** Custom colors define named colors. These colors may be actual inks or simply
	names for process colors depending on whether the custom color is a spot
	or global process color. In either case the custom color has an associated
	process color. The type of process color is identified by this enumeration. */
typedef struct {
	AI110CustomColorTag		kind;
	AI110CustomColorUnion	c;
	AICustomColorFlags		flag;
	unsigned char			name[32];
} AI110CustomColor;



#include "AIHeaderEnd.h"

#endif
