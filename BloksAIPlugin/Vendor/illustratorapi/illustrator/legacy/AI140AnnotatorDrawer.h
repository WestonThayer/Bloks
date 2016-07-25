#ifndef __AI140AnnotatorDrawer__
#define __AI140AnnotatorDrawer__

/*
 *        Name:	AI140AnnotatorDrawer.h
 *      Author: Started by Chris Quartetti
 *        Date: 2007
 *     Purpose:	Adobe Illustrator Annotator Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2007-2008 Adobe Systems Incorporated.
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

#include "AIAnnotatorDrawer.h"

#include "AIHeaderBegin.h"

// This Windows macro obscures an API
#undef DrawText

/** @file AI140AnnotatorDrawer.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIAnnotatorDrawerSuiteVersion1		AIAPI_VERSION(1)
#define kAI140AnnotatorDrawerSuiteVersion		kAIAnnotatorDrawerSuiteVersion1
#define kAI140AnnotatorDrawerSuite			kAIOldAnnotatorDrawerSuite
//This suite #defd as "AI Annotator Suite", in the latest version we have changed it to "AI Annotator Drawer
// suite", but cant change it here to maintain backward compatibility.
#define kAIOldAnnotatorDrawerSuite			"AI Annotator Suite"



/**	@ingroup Suites
	The annotator drawer suite allows plug-ins to draw annotations into the
	document window that are not a part of the artwork. Coordinates are in
	document view space.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAI40AnnotatorDrawerSuite and \c #kAI140AnnotatorDrawerSuiteVersion.
 */

struct AI140AnnotatorDrawerSuite
{
	/// @name Color
	//@{
	/// Set drawing color
	AIAPI void (*SetColor)(AIAnnotatorDrawer *drawer, const AIRGBColor &color);

	/// Get drawing color
	AIAPI void (*GetColor)(AIAnnotatorDrawer *drawer, AIRGBColor &color);
	//@}

	/// @name Lines and shapes
	/// Note: Line width is one point by default.
	//@{
	/** Set line width. */
	AIAPI void (*SetLineWidth)(AIAnnotatorDrawer *drawer, const AIReal newWidth);
	/** Get line width. */
	AIAPI AIReal (*GetLineWidth)(AIAnnotatorDrawer *drawer);

	/** Set dashed line drawing on or off. If \a dashed is true, all lines will
		be drawn dashed until set back to false. */
	AIAPI void (*SetLineDashed)(AIAnnotatorDrawer *drawer, AIBoolean dashed);
	/** Get state of dashed line drawing. */
	AIAPI AIBoolean (*GetLineDashed)(AIAnnotatorDrawer *drawer);

	/** Draw a line between \a start and \a end points. */
	AIAPI AIErr (*DrawLine)(AIAnnotatorDrawer *drawer, const AIPoint &start, const AIPoint &end);
	/** Draw a rectangle, optionally filling it with the current color. */
	AIAPI AIErr (*DrawRect)(AIAnnotatorDrawer *drawer, const AIRect &rect, AIBoolean fill);

	/** Draw a polygon by connecting the points. */
	AIAPI AIErr (*DrawPolygon)(AIAnnotatorDrawer *drawer, const AIPoint points[], ai::uint32 numPoints, AIBoolean fill);

	/** Draw an ellipse bounded by the rectangle. */
	AIAPI AIErr (*DrawEllipse)(AIAnnotatorDrawer *drawer, const AIRect &rect, AIBoolean fill);

	/** Draw cubic Bezier curves starting at \a start and threading through the points in the \a pointSets array.
		@param start[in]		The starting anchor point for the curve
		@param pointSets[in]	An array of sets of points describing the Bezier. The points in the
			inner array, p0, p1, and p2, have the following meaning:<br>
				p0	exit control point for the previous anchor<br>
				p1	entry control point for anchor<br>
				p2	anchor point<br>
			These are in the same order as for the PostScript CurveTo command.
		@param numPointSets[in]	Number of sets of points in the \a pointSets array.
		*/
	AIAPI AIErr (*DrawBezier)(AIAnnotatorDrawer *drawer, const AIPoint &start, const AIPoint pointSets[][3], ai::uint32 numPointSets, AIBoolean fill);
	//@}

	/// @name Text and Fonts
	//@{
	/** Draw \a text putting the bottom left at \a bottomLeft. */
	AIAPI AIErr (*DrawText)(AIAnnotatorDrawer *drawer, const ai::UnicodeString &text, const AIPoint &bottomLeft);

	/** Draw text aligned in the rectangle \rect with the given vertical and
		horizontal alignment. NB: Text will not wrap. */
	AIAPI AIErr (*DrawTextAligned)(AIAnnotatorDrawer *drawer, const ai::UnicodeString &text, const AIHorizAlignment horizAlign, const AIVertAlignment vertAlign, const AIRect &rect);

	/**	Find the bounds of text drawn in current font at current size. Specify \a location to
		get the bounds document view coordinates, otherwise bounds will start at 0,0.
		@param text[in]		Text to be drawn
		@param location[in]	Optional parameter to simulate drawing text in document view coordinates.
		@param bounds[out]	Coordinates of text boundary. If \a location is not specified, top left will be 0,0.	
		*/
	AIAPI AIErr (*GetTextBounds)(AIAnnotatorDrawer *drawer, const ai::UnicodeString &text, AIPoint *location, AIRect &bounds);

	/** Set font size. */
	AIAPI void (*SetFontSize)(AIAnnotatorDrawer *drawer, const AIReal size);

	/** Get font size. */
	AIAPI AIReal (*GetFontSize)(AIAnnotatorDrawer *drawer);

	/** Set the typeface and size with a AIAnnotatorFont enumeration. */
	AIAPI AIErr (*SetFontPreset)(AIAnnotatorDrawer *drawer, AIAnnotatorFont font);

	/** Set the font using an \a AIFontKey. */
	AIAPI AIErr (*SetFontByFontKey)(AIAnnotatorDrawer *drawer, AIFontKey font);

	/** Set the font by name. The API first attempts to interpret \a name as a
		PostScript name, then if not found, as a platform encoded name. */
	AIAPI AIErr (*SetFontByName)(AIAnnotatorDrawer *drawer, const ai::UnicodeString &name);

	/** Get the \a AIFontKey for the current font. */
	AIAPI AIFontKey (*GetFontKey)(AIAnnotatorDrawer *drawer);

	/** Get the name of the current font. */
	AIAPI void (*GetFontName)(AIAnnotatorDrawer *drawer, ai::UnicodeString &name);
	//@}

	/// @name Clipping
	//@{

	/**	Start sequence to define a clipping path. Anything drawn before calling \a DefineClipEnd
		will be unioned into the clipping path, after which all drawing will be clipped
		until calling \a ClearClip. Shapes drawn for clipping should generally be filled.
		*/
	AIAPI void (*DefineClipStart)(AIAnnotatorDrawer *drawer);

	/**	End sequence defining clipping path. Subsequent drawing will be clipped to the paths
		previously drawn until calling \a ClearClip.
		*/
	AIAPI void (*DefineClipEnd)(AIAnnotatorDrawer *drawer);

	/** Remove clipping path defined with \a DefineClipStart/DefineClipEnd. */
	AIAPI void (*ClearClip)(AIAnnotatorDrawer *drawer);
	//@}

	/// @name Miscellaneous
	//@{
	/** Set highlight blending mode (off by default). This provides extra visibility
		like XOR drawing but it cannot be used to erase previous marks drawn in highlight mode.
		*/
	AIAPI AIErr (*SetHighlightMode)(AIAnnotatorDrawer *drawer, AIBoolean highlightOn);

	/** Get highlight blending mode setting. Return value of true indicates highlight mode is on. */
	AIAPI AIBoolean (*GetHighlightMode)(AIAnnotatorDrawer *drawer);

	/**  Draw the icon putting the top left at the point \a topLeft. */
	AIAPI AIErr (*DrawIcon)(AIAnnotatorDrawer *drawer, ADMIconRef inIcon,  const AIPoint &topLeft);

	/** Draw the icon centered in the given rectangle. */
	AIAPI AIErr (*DrawIconCentered)(AIAnnotatorDrawer *drawer, ADMIconRef inIcon, const AIRect &rect);

	/** Get an AGM port suitable for use with AGMSuite. */
	AIAPI AIAGMPort* (*GetAGMPort)(AIAnnotatorDrawer *drawer);

	/** Release AGM port and set pointer to NULL. */
	AIAPI void (*ReleaseAGMPort)(AIAGMPort *&admAGMPort);
	//@}
};


#include "AIHeaderEnd.h"


#endif
