#ifndef __AI110RealBezier__
#define __AI110RealBezier__

/*
 *        Name:	AIRealBezier.h
 *     Purpose:	Adobe Illustrator bezier suite.
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

#include "AIRealBezier.h"

#include "AIHeaderBegin.h"

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI110RealBezierSuite			kAIRealBezierSuite
#define kAIRealBezierSuiteVersion1		AIAPI_VERSION(1)
#define kAI110RealBezierVersion			kAIRealBezierSuiteVersion1


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** Utilities for working with cubic beziers */
typedef struct {

	/** Set a bezier from its four control points. */
	AIAPI void		(*Set)			(AIRealBezier* b, AIRealPoint* p0, AIRealPoint* p1,
									AIRealPoint* p2, AIRealPoint* p3);
	/** Translate the bezier by the vector. */
	AIAPI void		(*Offset)		(AIRealBezier* b, AIReal dh, AIReal dv);
	/** Apply the transformation matrix to the bezier. */
	AIAPI void		(*Transform)	(AIRealBezier* b, AIRealMatrix* m);
	/** Determine the point on the bezier corresponding to the parameter t. */
	AIAPI void		(*Evaluate)		(AIRealBezier* b, AIReal t, AIRealPoint* p);
	/** Determine the tangent to the bezier corresponding to the parameter t. */
	AIAPI void		(*Tangent)		(AIRealBezier* b, AIReal t, AIRealPoint* v);
	/** Determine the normal to the bezier corresponding to the parameter t. */
	AIAPI void		(*Normal)		(AIRealBezier* b, AIReal t, AIRealPoint* v);
	/** Split b at the parameter t returning the two halves as b1 and b2. */
	AIAPI void		(*Divide)		(AIRealBezier* b, AIReal t, AIRealBezier* b1,
									AIRealBezier* b2);
	/** Test whether the bezier intersects the supplied rectangle. */
	AIAPI AIBoolean	(*IntersectsRect)(AIRealBezier* b, AIRealRect* r, AIReal scale);

	// New for AI8.0.

	/** Calculate the length of the bezier. The flatness parameter controls the accuracy
		with which the curve is approximated. */
	AIAPI AIReal	(*Length)			(AIRealBezier* b, AIReal flatness);
	/** Equivalent to calling Evaluate() and Tangent() with half the work. */
	AIAPI void		(*PointAndTangent)	(AIRealBezier* b, AIReal t, AIRealPoint* p, AIRealPoint *v);

	/** Adjust the bezier such that it passes through the point p at the parameter value
		t. See #AIAdjustThroughPointResult for return values. */
	AIAPI unsigned short (*AdjustThroughPoint) (AIRealBezier* b, AIRealPoint* p, AIReal t);

} AI110RealBezierSuite;


#include "AIHeaderEnd.h"


#endif
