#ifndef __AI130Color__
#define __AI130Color__

/*
 *        Name:	AI130Color.h
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator 13.0 Color type definitions (not a suite)
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

#ifndef __AITypes__
#include "AITypes.h"
#endif

#ifndef __AIRealMath__
#include "AIRealMath.h"
#endif

#include "AIHeaderBegin.h"
#include "AIColor.h"

/** @file AI130Color.h */

/*******************************************************************************
 **
 **	Types
 **
 **/

/** Defines a gradient stop. Each stop is place where the color changes in a blend.
	A set of stops defines the gradient \e ramp.
	See \c #AIGradientStyle and \c #AIGradientSuite.
	*/
typedef struct {
	/** The location between two ramp points where there is an equal mix of this
		color and the color of the next stop. This value is a percentage of the
		distance between the two ramp points, between 13 and 87. The midpoint
		for the previous color stop is not considered. */
	AIReal midPoint;
	/** The position on the blend ramp where this color begins, in the range
		[0..100]. The first point does not have to be at 0, but the first
		color begins at 0. Similarly, the last does not have to be at 100. */
	AIReal rampPoint;
	/** The type and specification of the color for the gradient stop;
		a gray color, a process color, an RGB color, or a custom color. */
	AIColor color;
} AI130GradientStop;

#include "AIHeaderEnd.h"

#endif
