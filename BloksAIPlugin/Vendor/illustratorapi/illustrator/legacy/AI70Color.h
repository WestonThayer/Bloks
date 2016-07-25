#ifndef __AI70Color__
#define __AI70Color__

/*
 *        Name:	AI70Color.h
 *   $Revision: 1 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 7.0 Color Types.
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

#ifndef __AIColor__
#include "AIColor.h"
#endif

#ifndef __AITypes__
#include "AITypes.h"
#endif

#ifndef __AIFixedMath__
#include "AIFixedMath.h"
#endif


#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 **	Types
 **
 **/

typedef struct {
	AIFixed gray;
} AI70GrayColorStyle;

typedef struct {
	AIFixed cyan, magenta, yellow, black;
} AI70FourColorStyle;

typedef struct {
	AIFixed red, green, blue;
} AI70ThreeColorStyle;


typedef union {
	AI70FourColorStyle	f;
	AI70ThreeColorStyle	rgb;
} AI70CustomColorUnion;

typedef struct {
	AICustomColorTag	kind;
	AI70CustomColorUnion	c;
	unsigned char		name[32];
} AI70CustomColor;

typedef struct {
	AICustomColorHandle color;
	AIFixed tint;
} AI70CustomColorStyle;


typedef struct {
	AIPatternHandle pattern;	 	/* reference to the AIPattern */
	AIFixed shiftDist;	/* distance to translate the [unscaled] prototype before filling */
	AIFixed shiftAngle;	/* angle to translate the [unscaled] prototype before filling */
	AIFixedPoint scale;	/* fraction to scale the prototype before filling */
	AIFixed rotate;		/* angle to rotate the prototype before filling */
	AIBoolean reflect;	/* whether or not the prototype is reflected before filling */
	AIFixed reflectAngle;	/* axis around which to reflect */
	AIFixed shearAngle;	/* angle to slant the shear by */
	AIFixed shearAxis;	/* axis to shear with respect to */
	AIFixedMatrix transform; /* additional transformation arising from manipulating the path */
} AI70PatternStyle;

typedef struct {
	AIGradientHandle gradient; 			/* reference to the AIGradient */
	AIFixedPoint gradientOrigin;			/* gradient vector origin */
	AIFixed gradientAngle;				/* gradient vector angle */
	AIFixed gradientLength;				/* gradient vector length */
	AIFixedMatrix matrix;					/* transformation applied by xform tools */
	AIFixed hiliteAngle;					/* gradient hilite vector angle */
	AIFixed hiliteLength;					/* length of hiliteVector measured as a fraction
										of the length of the gradient vector (gradientLength) */
} AI70GradientStyle;

typedef union { 
	AI70GrayColorStyle g;
	AI70FourColorStyle f;
	AI70ThreeColorStyle rgb;
	AI70CustomColorStyle c;
	AI70PatternStyle p;
	AI70GradientStyle b;
} AI70ColorUnion;

typedef struct {
	AIColorTag kind;			/* Used to determine the color variant */
	AI70ColorUnion c;
} AI70Color;


typedef struct {
	AIFixed midPoint; 				/* midpoint skew value in percent */
	AIFixed rampPoint;				/* location of color in the blend in percent */
	AI70Color color;
} AI70GradientStop;


#include "AIHeaderEnd.h"


#endif
