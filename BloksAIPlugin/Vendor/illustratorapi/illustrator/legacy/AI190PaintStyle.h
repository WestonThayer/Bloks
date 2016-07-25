#ifndef __AI190PaintStyle__
#define __AI190PaintStyle__

/*
 *        Name:	AI190PaintStyle.h
 *      Author:	Dave Lazarony
 *        Date:	6/17/96
 *     Purpose:	AI Paint Style Suite.
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

#ifndef __ASTypes__
#include "ASTypes.h"
#endif

#ifndef __AIColor__
#include "AIColor.h"
#endif

#ifndef __AIPathStyle__
#include "AIPathStyle.h"
#endif

#ifndef __AISwatchList__
#include "AISwatchList.h"
#endif

#include "AIPaintStyle.h"
#include "AIHeaderBegin.h"
/** @file AI190PaintStyle.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI190PaintStyleSuite			kAIPaintStyleSuite
#define kAIPaintStyleSuiteVersion9	AIAPI_VERSION(9)

/* Latest version */
#define kAI190PaintStyleSuiteVersion	kAIPaintStyleSuiteVersion9
#define kAI190PaintStyleVersion		kAI190PaintStyleSuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provides functions to examine and operate on the Color and Gradient
	palettes, which display and modify the paint style of the current selection,
	and the Color Editor, which allows a user to choose and edit colors.

 	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIPaintStyleSuite and \c #kAIPaintStyleSuiteVersion.
 */
typedef struct
{
	/** Causes the Color palette to show the stroke color (not fill).
		(Note that this function does not return an error code.)
		*/
	void ASAPI (*SetStrokeActive)();

	/** Reports whether the Color palette shows the stroke color (not fill).
		(Note that this function returns a boolean value, not an error code.)
			@return True if stroke is active.
		*/
	ASBoolean ASAPI (*IsStrokeActive)();

	/** Causes the Color palette to show the fill color (not stroke).
		(Note that this function does not return an error code.)
		*/
	void ASAPI (*SetFillActive)();

	/** Reports whether the Color palette shows the fill color (not stroke).
		(Note that this function returns a boolean value, not an error code.)
			@return True if fill is active.
		*/
	ASBoolean ASAPI (*IsFillActive)();

	/** Sets the fill and stroke states of the current selection to those
		of the default style (usually white for fill and solid
		1-point black for stroke).
		(Note that this function does not return an error code.)
		*/
	void ASAPI (*SetDefaultFillStroke)();

	/** Retrieves the index position of the selected stop the current gradient.
		(Note that this function returns a numeric value, not an error code.)
			@return The 0-based position index, or -1 if a gradient stop is not
				currently being edited.
		*/
	int ASAPI (*GetActiveGradientStopIndex)();

	/** Retrieves the gradient currently shown in the Gradient palette.
			@param color [out] A buffer in which to return the gradient.
		*/
	ASErr ASAPI (*GetCurrentGradient)(AIColor *color);

	/** Retrieves the fill, stroke, or currently active gradient stop
		color currently shown in the Color palette.
			@param color [out] A buffer in which to return the color.
		*/
	ASErr ASAPI (*GetCurrentColor)(AIColor *color);

	/** Invokes the Gradient palette. */
	ASErr ASAPI (*ShowGradientDialog)();

	/** Invokes the Color palette. */
	ASErr ASAPI (*ShowColorDialog)();

	/** If caching is not active, applies a color to the selection, or to the
		active gradient stop.

		If caching is active--that is, between a call to \c #BeginActiveColor()
		and a call to \c #EndActiveColor() --applies the color to proxies (such as the
		color previews in the Tools palette) rather than to the selection or gradient stop.
		(The eyedropper tool uses this during mouse-drag.)
			@param color The new color.
			@param useGradientStop True to replace the color in the
				currently active gradient stop only, false to replace the color
				in the entire selection.
		*/
	ASErr ASAPI (*SetActiveColor)(AIColor *color, ASBoolean useGradientStop);

	/** Starts caching for color application to proxies.
		@see \c #SetActiveColor(), \c #SetAIColor() */
	ASErr ASAPI (*BeginActiveColor)();

	/** Finishes caching for color application to proxies.
		@see \c #SetActiveColor(), \c #SetAIColor() */
	ASErr ASAPI (*EndActiveColor)();

	/** Reports whether the current color in the Color palette is for a stroke or fill.
		(Note that this function returns a boolean value, not an error code.)
			@return True if the color is for a stroke, false if it is for a fill.
		*/
	ASBoolean ASAPI (*IsCurrentColorStroke)();

	/** If caching is not active, applies a stroke or fill color to the current selection,
		using a partial color specification.

		If caching is active--that is, between a call to \c #BeginActiveColor()
 		and a call to \c #EndActiveColor() --applies the color to proxies (such as the
		color previews in the Tools palette) rather than to the selection.
			@param color The color structure containing new color component values.
			@param colorMap A color map that specifies which members of the color structure
				contain valid values.
			@param isStroke True to set the current stroke color, false to set the fill color.
		*/
	ASErr ASAPI (*SetAIColor)(AIColor *color, AIColorMap *colorMap, ASBoolean isStroke);

	/**	Shows a gradient in the Gradient palette.
			@param color The gradient.
		*/
	ASErr ASAPI (*SetCurrentGradient)(AIColor *color);

	/**	Shows a color in the Color palette.
			@param color The color.
		*/
	ASErr ASAPI (*SetCurrentColor)(AIColor *color);

	/** Shows the Color palette if it is hidden, hides the Color palette if it is shown.
		*/
	ASErr ASAPI (*ToggleColorDialog)();

	/** Exchanges the fill and stroke colors for the current selection.
		(Note that this function does not return an error code.)
		*/
	void ASAPI (*SwapFillStroke)();

	/** Invokes the color-chooser dialog and reports the chosen color.
		(Note that this function returns a boolean value, not an error code.)
		@param currentColor specifies the initial color the picker will display.
		When the function returns currentColor will become the color the user picked.
			@return True if the user clicked OK, false of the user clicked Cancel. */
	ASBoolean ASAPI (*DisplayColorPicker)(AIColor *currentColor);

	/** Invokes the Color Picker dialog with options and reports the chosen color.
		(Note that this function returns a boolean value, not an error code.)
			@param currentColor [in/out] On input, the initial color to display.
				On output, the color the user selected.
			@param options Options for initial display. The Color Picker opens in
				the swatch-list view if the initial color exactly matches the color
				in a swatch from the \c #AIColorPickerOptions::swatchList.
			@return True if the user clicked OK in the Color Picker, false if the user clicked Cancel.
		*/
	ASBoolean ASAPI (*DisplayColorPickerWithOptions)(AIColor *currentColor, const AIColorPickerOptions &options );

	/** Changes the stroke alignment on an art.
			@param art [in] The art handle whose stroke alignment is to be changed..
				On output, the color the user selected.
			@param strokeAlignment [in] The requirement alignment type. For possible values please see enum \c #AIStrokeAlignmentType.
			@return kNoErr if successful, error code otherwise.
		*/
	AIErr ASAPI (*SetStrokeAlignment)(AIArtHandle art, ai::uint32 strokeAlignment);

} AI190PaintStyleSuite;



#include "AIHeaderEnd.h"

#endif
