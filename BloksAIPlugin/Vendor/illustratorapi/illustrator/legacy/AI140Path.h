#ifndef __AI140Path__
#define __AI140Path__

/*
 *        Name:	AI140Path.h
 *        Date:
 *     Purpose:	backwards compatibility support for Path Object Suite from Adobe Illustrator 14.0
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2009 Adobe Systems Incorporated.
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

#include "AIPath.h"

#include "AIHeaderBegin.h"

/** @file AI140Path.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI140PathSuite				kAIPathSuite
#define kAIPathSuiteVersion8		AIAPI_VERSION(8)
#define kAI140PathSuiteVersion		kAIPathSuiteVersion8
#define kAI140PathVersion			kAI140PathSuiteVersion



/*******************************************************************************
 **
 **	Suite
 **
 **/


/** @ingroup Suites
	This suite provides functions that allow you to examine and manipulate
	\e paths, which are art objects of type \c #kPathArt.

	The shape of a path is defined by one or more path \e segments.
	Every segment of a path corresponds to an \e anchor \e point, which is
	the handle shown when the path is selected. The number of anchor points
	on a path, or \e segment \e count, includes the two at each end.
	A segment is defined by the \c #AIPathSegment structure. Segment
	index numbers begin at zero. A path can have a single anchor point.

	The \e in and \e out points of a segment define the tangent of the curve
	at a point \e p. The in point is not used for the initial and final segments
	of an open path. A segment can be a \e corner point or a \e smooth point.
	For a corner, the in and out points can be anywhere. To make a straight line,
	place the in and out points of each end on their p points.

	A path can be can be \e closed or \e open.
	If a path is open, it is defined only by its segments. If it is closed,
	Illustrator draws a segment between the first and last anchor points,
	which uses the out tangent of the last segment and the in tangent of the first.

	Some paths are also used as \e guides. In all other respects they are paths,
	with the same contents and attributes. Paint attributes are associated with
	a path through a \e path \e style. See the \c #AIPathStyleSuite.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIPathSuite and \c #kAIPathVersion.
*/
typedef struct {

	AIAPI AIErr (*GetPathSegmentCount) ( AIArtHandle path, short *count );

	AIAPI AIErr (*SetPathSegmentCount) ( AIArtHandle path, short count );

	AIAPI AIErr (*GetPathSegments) ( AIArtHandle path, short segNumber, short count, AIPathSegment *segment );

	AIAPI AIErr (*SetPathSegments) ( AIArtHandle path, short segNumber, short count, AIPathSegment *segment );

	AIAPI AIErr (*InsertPathSegments) ( AIArtHandle path, short segNumber, short count, AIPathSegment *segment );

	AIAPI AIErr (*DeletePathSegments) ( AIArtHandle path, short segNumber, short count );

	AIAPI AIErr (*GetPathClosed) ( AIArtHandle path, AIBoolean *closed );

	AIAPI AIErr (*SetPathClosed) ( AIArtHandle path, AIBoolean closed );

	AIAPI AIErr (*GetPathGuide) ( AIArtHandle path, AIBoolean *isGuide );

	AIAPI AIErr (*SetPathGuide) ( AIArtHandle path, AIBoolean isGuide );

	AIAPI AIErr (*GetPathSegmentSelected)( AIArtHandle path, short segNumber, short *selected );

	AIAPI AIErr (*SetPathSegmentSelected)( AIArtHandle path, short segNumber, short selected );

	AIAPI AIErr (*ReversePathSegments) ( AIArtHandle path );

	AIAPI AIErr (*GetPathArea) ( AIArtHandle path, AIReal *area );

	// New for AI8.0:

	AIAPI AIErr (*GetPathLength) ( AIArtHandle path, AIReal *length, AIReal flatness );

	AIAPI AIErr (*GetPathBezier) ( AIArtHandle path, short segNumber, AIRealBezier *bezier );

	AIAPI AIErr (*PathHasLength) ( AIArtHandle path, AIBoolean *hasLength );

	AIAPI AIErr (*GetPathIsClip) ( AIArtHandle path, AIBoolean *isClip );

	// New for AI 11

	AIAPI AIErr (*GetPathAllSegmentsSelected) ( AIArtHandle path, AIBoolean *selected );

	// New for AI 13

	AIAPI AIErr (*GetKeySegment) (AIArtHandle* path, short* segmentNumber);

	AIAPI AIErr (*CancelKeySegment) (void);

	AIAPI AIBoolean (*IsPath9SliceSplitter)(AIArtHandle path);

	// New for AI14

	AIAPI AIErr (*SetKeySegment)(AIArtHandle path, short segmentNumber);

} AI140PathSuite;

#include "AIHeaderEnd.h"

#endif		//__AI140Path__
