#ifndef __AI110Path__
#define __AI110Path__

/*
 *        Name:	AI110Path.h
 *   $Revision: 13 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 11.0 Path Object Suite.
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

#include "AIPath.h"

#include "AI70Color.h"

#include "AIHeaderBegin.h"

/** @file AI110Path.h */


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI110PathSuite				kAIPathSuite
#define kAIPathSuiteVersion5		AIAPI_VERSION(5)
#define kAI110PathSuiteVersion		kAIPathSuiteVersion5
#define kAI110PathVersion			kAI110PathSuiteVersion


/*******************************************************************************
 **
 **	Types
 **
 **/

// These typedefs are needed only for the AIPathStyleToAI70PathStyle and AI70PathStyleToAIPathStyle
// functions in this suite.
// They are AIFixed versions of the types defined in AIPathStyle.h, but since we no longer export the
// AI70PathStyle suite, the typedef has been moved here to be with its only reference.

typedef struct {
	AI70Color color; 				/* Fill color */
	AIBoolean overprint;			/* Overprint */
} AI70FillStyle;

typedef struct {
	short length;				/* 0 if solid */
	AIFixed offset;				/* Dash offset */
	AIFixed array[kMaxDashComponents];	/* Dash array */
} AI70DashStyle;

typedef struct {
	AI70Color color;			/* Stroke color */
	AIBoolean overprint;		/* Overprint - not meaningful if ColorTag is pattern */
	AIFixed width;				/* Line width */
	AI70DashStyle dash;			/* Stroke dash */
	AILineCap cap;				/* Line cap */
	AILineJoin join;			/* Line join */
	AIFixed miterLimit;			/* Line miter limit */
} AI70StrokeStyle;

typedef struct {
	AIBoolean fillPaint;		/* Whether or not to fill the path */
	AIBoolean strokePaint;		/* Whether or not to stroke the path */
	AI70FillStyle fill;			/* Fill style, if fillPaint is true */
	AI70StrokeStyle stroke;		/* Stroke style, if strokePaint is true */
	AIBoolean clip;				/* Whether or not to use this as a clipping path */
	AIBoolean evenodd;			/* Whether or not to use the even-odd rule to determine path insideness */	
	AIFixed resolution;			/* Path's resolution */
	unsigned char note[256];
} AI70PathStyle;

typedef struct AI110PathStyle {
	AIBoolean fillPaint;		/** Whether or not to fill the path. */
	AIBoolean strokePaint;		/** Whether or not to stroke the path */
	struct AIFillStyle fill;	/** Fill style, if fillPaint is true */
	struct AIStrokeStyle stroke;	/** Stroke style, if strokePaint is true */
	AIBoolean clip;				/** Whether or not to use this as a clipping path */
	AIBoolean lockClip;			/** Whether or not to lock the clipping path */
	AIBoolean evenodd;			/** Whether or not to use the even-odd rule to determine path insideness */
	AIReal resolution;			/** Path's resolution */
	unsigned char note[256];
} AI110PathStyle;



/*******************************************************************************
 **
 **	Suite
 **
 **/


/**
	The shape of art of type kPathArt is defined by one or more path segments. It
	has two other attributes, whether the path is closed and whether it is a guide.
	In addition, it has paint attibutes associated with it in a path style (see the
	AIPathStyleSuite).

	Every segment of a path corresponds to an anchor point (anchor points are
	the path handles that are visible when the path is selected). The segment
	count is the number of anchor points on the path, including the two at each
	end. A segment is defined by the AIPathSegment structure.

	The in and out points of a segment define the tangent of the curve at a point
	Note that the in point for initial and final segments of an open path are not
	used.

	A segment can be a corner point or a smooth point. If the segment is a
	corner (corner == true), the in and out points can be anywhere. To make a
	straight line, place the in and out points of each end on their p points.

	Segment numbers begin at zero. Illustrator limits the number of segments in
	a path to 8191. A path may consist of a single anchor point.

	A path can be open or closed. If a path is open, it is defined only by its
	segments. If it is closed, a 'phantom' segment is added by Illustrator
	between the first and last anchor points. It uses the out tangent of the last
	segment and the in segment of the first.

	Some paths double as guides. In all other respects they are paths, having
	segments, corner points and close attributes.
 */
struct AI110PathSuite {

	/** Every anchor point on a path corresponds to a path segment (anchor points
		are the path handles that are visible when the path is selected). The segment
		count is the number of anchor points on the path, including the two at each
		end. A path may consist of a single anchor point. */
	AIAPI AIErr (*GetPathSegmentCount) ( AIArtHandle path, short *count );
	/** Sets the number of segments for the path. This may be used to either increase
		or decrease the count of segments. If the count is increased any new segments
		are initialized to default values. Callers should not depend on these default
		values.
	
		Note: SetPathSegmentCount() and SetPathSegments() will return #kTooManySegmentsErr
		when you try to exceed the maximum number of path segments,

		Note: When AIArtSuite::NewArt() creates a path, it initially allocates space
		for 32 segments. When creating many small paths, this can get waste quite
		a bit of memory. SetPathSegmentCount() will free the memory of unused path
		segments immediately.
	*/
	AIAPI AIErr (*SetPathSegmentCount) ( AIArtHandle path, short count );
	/** Use this to 'read' a range of segments out of a path.

		The segNumber and count arguments specify the range of segments to get
		(the first segment and the number of segments). Segment numbers begin at
		zero.

		The segment argument points to an array of AIPathSegment structures
		allocated by the plug-in to receive these segments. It must be at least as big
		as count.
	*/
	AIAPI AIErr (*GetPathSegments) ( AIArtHandle path, short segNumber, short count, AIPathSegment segments[] );
	/** Use this to 'write' a range of segments into a path. */
	AIAPI AIErr (*SetPathSegments) ( AIArtHandle path, short segNumber, short count, const AIPathSegment segments[] );
	/** This function inserts count segments after segNumber. */
	AIAPI AIErr (*InsertPathSegments) ( AIArtHandle path, short segNumber, short count, const AIPathSegment segments[] );
	/** This function deletes count segments starting at segNumber. If you delete
		segments from a closed path, the path remains closed. */
	AIAPI AIErr (*DeletePathSegments) ( AIArtHandle path, short segNumber, short count );

	/** Returns whether the path is closed. */
	AIAPI AIErr (*GetPathClosed) ( AIArtHandle path, AIBoolean *closed );
	/** Sets whether the path is closed. */
	AIAPI AIErr (*SetPathClosed) ( AIArtHandle path, AIBoolean closed );
	/** Returns whether the path is a guide */
	AIAPI AIErr (*GetPathGuide) ( AIArtHandle path, AIBoolean *isGuide );
	/** Sets whether the path is a guide */
	AIAPI AIErr (*SetPathGuide) ( AIArtHandle path, AIBoolean isGuide );

	/** Returns an indication of the selection state for the indicated segment. The
		possible values are given by #AIPathSegementSelectionState. */
	AIAPI AIErr (*GetPathSegmentSelected)( AIArtHandle path, short segNumber, short *selected );
	/** Sets the selection state for the indicated segment. The possible values are
		given by #AIPathSegementSelectionState. Note that modifying the selection
		state of one segment may affect adjacent segments. For example, if the out
		direction of one segment is selected then the in direction of the following
		segment will be selected. */
	AIAPI AIErr (*SetPathSegmentSelected)( AIArtHandle path, short segNumber, short selected );

	/** Reverses the order of segments in the path. Use this as a quick way to change
		the winding order of a path. The winding order is only significant if the path
		is a subpath of a compound path. It controls the insideness of the compound path.*/
	AIAPI AIErr (*ReversePathSegments) ( AIArtHandle path );
	/** The area is returned as area and is in square points. The paths winding
		order is determined by the sign of area. If the area is negative, the path is
		wound counter-clockwise. Self-intersecting paths may contain sub-areas that
		cancel each other out. It’s possible for a path to return zero for its area,
		even though it’s got lots of area. */
	AIAPI AIErr (*GetPathArea) ( AIArtHandle path, AIReal *area );

	// New for AI8.0:

	/** Get the length of the perimeter of the path measured in points. The flatness
		parameter controls the degree of accuracy to the true mathematical length. */
	AIAPI AIErr (*GetPathLength) ( AIArtHandle path, AIReal *length, AIReal flatness );
	/** Returns the bezier from "segNumber" anchor to the next.

		If segNumber is the last anchor point of an open path, it will wrap around to
		the beginning. If it is the last anchor point of a closed path, then all four
		points will be equal (i.e., the outgoing control point will be ignored), so
		that visible bounding rect, length, and other functions will treat it properly.
	*/
	AIAPI AIErr (*GetPathBezier) ( AIArtHandle path, short segNumber, AIRealBezier *bezier );
	/** Determines if GetPathLength() != 0 but much more efficient. */
	AIAPI AIErr (*PathHasLength) ( AIArtHandle path, AIBoolean *hasLength );
	
	/** Determines whether the path is a clipping path. The input object may be a
		path or a compound path. To be a clipping object a path must have at least
		two segments. To make a path into a clipping path use AIArtSuite::SetArtUserAttr() */
	AIAPI AIErr (*GetPathIsClip) ( AIArtHandle path, AIBoolean *isClip );

	/** A utility to convert an Illustrator 8 and later path style to an Illustrator
		7.0 path style. The former uses floating point while the latter uses fixed
		point for numbers.
		Since the AI70PathStyle suite is not exported, this conversion is no longer useful. */
	AIAPI AIErr (*AIPathStyleToAI70PathStyle)( AI110PathStyle *from, AI70PathStyle *to );
	/** A utility to convert an Illustrator 7.0 path style to an Illustrator 8 and
		later path style. The latter uses floating point while the former uses fixed
		point for numbers.
		Since the AI70PathStyle suite is not exported, this conversion is no longer useful. */
	AIAPI AIErr (*AI70PathStyleToAIPathStyle)( AI70PathStyle *from, AI110PathStyle *to );

	// New for AI 11

	/** Determines whether all segments of the path are selected. In this case the
		path is considered to be fully selected. */
	AIAPI AIErr (*GetPathAllSegmentsSelected) ( AIArtHandle path, AIBoolean *selected );
	
};


#include "AIHeaderEnd.h"


#endif
