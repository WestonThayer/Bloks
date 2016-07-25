#ifndef __AI150BeautifulStrokes__
#define __AI150BeautifulStrokes__

/*
*        Date:	Started 2009
*     Purpose:	Adobe Illustrator Beautiful Strokes suite. This suite lets
*				clients control effects that can be applied to strokes such as
*				art and pattern brushes, arrowheads, and dash adjustments.
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 2009 Adobe Systems Incorporated.
* All rights reserved.
*
* NOTICE:  Adobe permits you to use, modify, and distribute this file
* in accordance with the terms of the Adobe license agreement
* accompanying it. If you have received this file from a source other
* than Adobe, then your use, modification, or distribution of it
* requires the prior written permission of Adobe.
*
*/

#include "AIBeautifulStrokes.h"
#include "AIHeaderBegin.h"

/*******************************************************************************
**
** Constants
**
**/

#define kAIBeautifulStrokesSuiteVersion1	AIAPI_VERSION(1)
#define kAI150BeautifulStrokesSuiteVersion	kAIBeautifulStrokesSuiteVersion1

/*******************************************************************************
**
**	Suite
**
**/

/**	@ingroup Suites
	This suite allows you to control advanced features for stroking paths. Setting are
	kept in a BeautifulStrokes params dictionary, which is contained in an \c #AILiveEffectsParameters
	dictionary, such as one returned by \c #AIPathStyle::GetCurrentPathStyle().  <br>
	One way to use this suite is to create a BeautifulStrokes params dictionary,
	add the stroke settings to the dictionary, then use that dictionary to apply
	the settings to source art. This generates new art in a destination group.
	For example:

	@code
	void Fn(AIArtHandle srcPath, AIArtHandle dstGroup)
	{
		AIDictionaryRef params = 0;
		sAIBeautifulStrokes->CreateParamsDict(NULL, params);
		sAIBeautifulStrokes->SetDashAdjustment(params, true);
		sAIBeautifulStrokes->GenerateArt(params, srcPath, NULL, TRUE, dstGroup, NULL);
		sAIDictionary->Release(params);
	}
	@endcode

	Counted object note: Suite functions that return counted object types such as
	\c #AIDictionarySuite::AIDictionaryRef and \c #AIArraySuite::AIArrayRef increment
	the reference count and the caller must release unneeded references to avoid memory
	leaks, as shown in the examples. Documentation for individual parameters mentions those
	that are reference counted and need to be released. See also \c #AICountedObjectSuite
	and the \c ai::Ref C++ class.

	The example above uses the \c #AIDictionarySuite::Release() directly.
	The following example uses the \c ai::Ref C++ class to manage the counted
	object. (Note that \c #AICountedObjectSuite::Release() is equivalent to
	\c #AIDictionarySuite::Release()):

	@code
	void Fn_Ref(AILiveEffectParameters effectParams)
	{
		ai::Ref<AIDictionaryRef> params;
		sAIBeautifulStrokes->CreateParamsDict(NULL, *(params << ai::Replace));
		sAIBeautifulStrokes->SetDashAdjustment(params, true);
		sAIBeautifulStrokes->GenerateArt(params, srcPath, NULL, TRUE, dstGroup, NULL);
	}
	@endcode

*/

struct AI150BeautifulStrokesSuite
{

	// General parameter management and stroke generation

	/**	Applies settings in a BeautifulStrokes parameters dictionary to the focal stroke on source art
		to generate new stroked art in the output group.

		@param effectParams		An effect parameters dictionary that contains a BeautifulStrokes params
								dictionary in which BeautifulStrokes settings are defined. This can also
								be a BeautifulStrokes params dictionary.
		@param inArt			The art (path) to which the parameters are to be applied.
		@param sourceArt		[optional] The non-styled art (path) possibly containing width anchors that can be
								used to adjust the width profile placement. (See \c #AIBeautifulStrokesSuite::GetPathAdjustedWidthDistances().)
								This parameter is ignored if inArt is not styled art (see \c #AIArtSuite::IsArtStyledArt()),
								since non-styled art will carry its own anchors. But art dictionaries are stripped
								from the input art to live effects. Thus, if \c inArt is the input art to a live effect
								execution for a stroke filter, and the art style being executed was attached to a path,
								then passing \c sourceArt as the non-styled path art object to which that art style was
								attached will allow access to the width anchors. (If there are no vector pre-effects
								before the stroke filter, then \c inArt will generally be a duplicate of \c sourceArt,
								but if there are vector pre-effects, then it may be substantially different.)
								Passing this parameter as null when inArt is styled art will cause any width profile
								in the effectParams to be applied without width anchor adjustment.
		@param outputOnTop		True to place the output art into the output group on top, false to place
								it inside the output group on the bottom.
		@param outGroup			The destination group for the generated output art.
		@param outArt			[optional] A pointer to an AIArtHandle in which to return the AIArtHandle for the generated output art.
	*/
	AIAPI AIErr (*GenerateArt)(ConstAILiveEffectParameters effectParams, AIArtHandle inArt, AIArtHandle sourceArt,
							   AIBoolean outputOnTop, AIArtHandle outGroup, AIArtHandle *outArt);

	/**	Creates a new BeautifulStrokes params dictionary. You must release the dictionary when no longer needed using
		\c #AIDictionarySuite::Release().

		@param effectParams		[optional] A set of LiveEffect parameters. If supplied, the new BeautifulStrokes
								params dictionary is added to this dictionary, or, if a BeautifulStrokes dictionary
								already exists, \c params is set to this existing dictionary.
		@param params			A reference to a new or the existing BeautifulStrokes params dictionary.
								The reference count on this dictionary is incremented on return and
								must be released when no longer needed.

	*/
	AIAPI AIErr (*CreateParamsDict)(AILiveEffectParameters effectParams, AIDictionaryRef &params);

	/**	Retrieves a BeautifulStrokes parameters dictionary from a set of LiveEffect parameters.

		@param effectParams		A set of LiveEffect parameters for an art object.
		@param params			A reference to the BeautifulStrokes params dictionary or
								NULL if one does not exist. The reference count on this
								dictionary is incremented on return and must be released
								when no longer needed.

		@return					No error is returned if the dictionary does not exist.
	*/
	AIAPI AIErr (*GetParamsDict)(ConstAILiveEffectParameters effectParams, AIDictionaryRef &params);

	/**	Reports whether two parameters dictionaries are equivalent.

		@param params1			The first dictionary.
		@param params2			The second dictionary.
		@return					True if equivalent.
	*/
	AIAPI AIBoolean (*Equiv)(ConstAIDictionaryRef params1, ConstAIDictionaryRef params2);

	/**	Accumulates common parameters in a dictionary to be used later with \c #ApplyParams().
		Call repeatedly with different parameter sets to collect the combined BeautifulStrokes
		attributes of multiple objects (or multiple art styles). You can use this to collect
		common attributes of objects that are not necessarily selected, or to ignore some of
		the selected objects, such as finding the combined BeautifulStrokes attributes of
		all the objects on a layer, whether they are selected or not.

		@param effectParams		A set of LiveEffect parameters containing a Beautiful Strokes params dictionary.
		@param accumulator		Common parameters being accumulated.
	*/
	AIAPI AIErr (*AccumulateParams)(ConstAILiveEffectParameters effectParams, AIDictionaryRef accumulator);

	/**	Applies a set of parameters from one dictionary to another.	For keys that exist in both dictionaries,
		the value from the source overwrites the value in the destination.

		@param params	The source dictionary containing a set of parameters to be applied.
						Typically obtained from \c #AIPathStyle::GetCurrentPathStyle(), from an art object or art style.
						If an accumulated dictionary is passed as the source, values that vary (were mixed in the selection)
						do not change value in the target dictionary. This is consistent with the behavior of
						\c #AIPathStyle::SetCurrentPathStyle(). See also \c #AccumulateParams().
		@param target	The target dictionary.
	*/
	AIAPI AIErr (*ApplyParams)(ConstAIDictionaryRef params, AIDictionaryRef target);

	/**	Reports whether a dictionary contains meaningful Beautiful Strokes parameters.
		(Note that this function returns a Boolean value, not an error code.)
		Call on an accumulator to check whether it contains any BeautifulStrokes parameters;
		if not, it can be freed or ignored.  See \c #AccumulateParams().
		Both a used accumulator and a new dictionary contain some bookkeeping entries, so you cannot just
		check for the dictionary being empty of all keys. A new dictionary just created by
		\c #CreateParamsDict() returns false to this call. <br>

		This does not recurse into sub-dictionaries. To test for nested dictionaries,
		call \c #GetParamsDict(), and if it is non-null check the contained dictionary.

		@param paramsDict	Dictionary to be examined.
		@return				True if the dictionary contains Beautiful Strokes parameters.
	*/
	AIAPI AIBoolean (*ContainsParams)(ConstAIDictionaryRef paramsDict);

	/**	Retrieves the BeautifulStrokes params dictionary, if any, associated with the focal stroke of an art object. Optionally
		retrieves the stroke style and other information about the stroke attributes.

		@param art			The art object.
		@param paramDict	[out] A reference in which to return the BeautifulStrokes params dictionary, or null if none.
							The reference count on this dictionary is incremented on return and must be released when
							no longer needed.
		@param strokeStyle	[out][optional] A buffer in which to return the focal stroke style from the paint attributes.
		@param hasBrush		[out][optional] A buffer in which to return true if the focal stroke carries a brush effect.
		@param scaleFactor	[out][optional] A buffer in which to return the combined scale factor that incorporates:
							the object scale factor reported by \c #AIArtStyleSuite::GetArtStyleScaleFactor(),
							the width of the art design on art brushes or the side tile on pattern brushes,
							and the scale factor from the brush options for brushes. <br>
							Multiplying these widths by this factor gives the width that the stroke edges
							preview at, assuming that any brush art fills the brush tile boundaries.<br>
							(Does not include the stroke weight or the width returned by \c #GetWidthAtDistance(), and so on.)
		@param canAccept	[out][optional] A buffer in which to return true if the art object has a style that can accept
							BeautifulStrokes parameters.
							(For CS5, it has a stroke, and the focal stroke is not a Calligraphic or Scatter brush, and is
							not inside/outside aligned.)
	*/
	AIAPI AIErr (*GetArtStrokeParams)(AIArtHandle art, AIDictionaryRef &paramDict,
									  AIStrokeStyle *strokeStyle, AIBoolean *hasBrush,
									  AIReal *scaleFactor, AIBoolean *canAccept);

	/**	Interpolates beautiful stroke parameters between two appearances.

		@param effectParams1	[optional] The effects parameters dictionary of a stroke filter,
								which may (or may not) contain a Beautiful Strokes params dictionary.
		@param effectParams2	[optional] The effects parameters dictionary of a stroke filter
								which may (or may not) contain a Beautiful Strokes params dictionary.
		@param effectParamsOut	The effects parameters dictionary of a stroke filter that represents the results
								of interpolating between effectParams1 and effectParams2.
		@param dist				A number in the range [0-1], where 0 is interpreted as matching effectParams1,
								and 1 is interpreted as matching effectParams2. (Negative values are interpreted
								as if they were 0, and values greater than 1 as if they were 1.)

		If either effectParams1 or effectParams2 contains a Beautiful Strokes parameter dictionary, then those parameters
		will be interpolated, and the results placed in effectParamsOut (which should not be null if either input parameter
		is null.)
	*/
	AIAPI AIErr (*InterpolateParams)(ConstAILiveEffectParameters effectParams1, ConstAILiveEffectParameters effectParams2,
									 AILiveEffectParameters effectParamsOut, AIReal dist);

	// General brush settings

	/**	Sets the option in a Beautiful Strokes dictionary to flip art across path to reverse vertical orientation.

		@param params		The dictionary.
		@param flipAcross	True to set the option, false to clear it.
	*/
	AIAPI AIErr (*SetFlipAcross)(AIDictionaryRef params, AIBoolean flipAcross);

	/**	Retrieves the option from a Beautiful Strokes dictionary to flip art across path to reverse vertical orientation.
		Note that this function returns a Boolean value, not an error code.

		@param params		The dictionary.
		@return				True if the option is set, false if it is clear.
	*/
	AIAPI AIBoolean (*GetFlipAcross)(ConstAIDictionaryRef params);

	/**	Sets the option in a Beautiful Strokes dictionary to flip art along path to reverse lateral orientation.

		@param params		The dictionary.
		@param flipAlong	True to set the option, false to clear it.
	*/
	AIAPI AIErr (*SetFlipAlong)(AIDictionaryRef params, AIBoolean flipAlong);

	/**	Retrieves the option from a Beautiful Strokes dictionary to flip art along path to reverse lateral orientation.
		Note that this function returns a Boolean value, not an error code.

		@param params		The dictionary.
		@return				True if the option is set, false if it is clear.
	*/
	AIAPI AIBoolean (*GetFlipAlong)(ConstAIDictionaryRef params);

	/**	Sets the scale (width) of art applied to path in a Beautiful Strokes dictionary.

		@param params	The dictionary.
		@param scale	Single scale for art not using tablet data.
		@param mnScale	[optional] Minimum scale for art using tablet data.
		@param mxScale	[optional] Maximum scale for art using tablet data.
	*/
	AIAPI AIErr (*SetScale)(AIDictionaryRef params, AIReal scale, const AIReal *mnScale, const AIReal *mxScale);

	/**	Retrieves the scale (width) of art applied to path from a Beautiful Strokes dictionary.

		@param params	The dictionary.
		@param scale	[out] A reference in which to return the single scale for art not using tablet data.
		@param mnScale	[optional] [out] A buffer in which to return the minimum scale for art using tablet data.
		@param mxScale	[optional] [out] A buffer in which to return the maximum scale for art using tablet data.
	*/
	AIAPI AIErr (*GetScale)(ConstAIDictionaryRef params, AIReal &scale, AIReal *mnScale, AIReal *mxScale);

	/**	Set fold adjustment on or off. This adjusts the brush folding across corners or bends.
	*/
	AIAPI AIErr (*SetFoldAdjustment)(AIDictionaryRef params, AIBoolean adjust);

	/**	Retrieves the fold adjustment status from a Beautiful Strokes dictionary.
		This adjusts the folding across corners or bends.
		Note that this function returns a Boolean value, not an error code.

		@param params	The dictionary.
		@param mixed	[optional] [out] A buffer in which to return true if the dictionary represents an accumulation
						returned from \c #AIPathStyleSuite::GetCurrentPathStyle(), and the selection is mixed.
						By convention, mixed values return false.
		@return			True if the option is set, false if it is clear.
	*/
	AIAPI AIBoolean (*GetFoldAdjustment)(ConstAIDictionaryRef params, AIBoolean *mixed);

	// Art Brushes

	/**	Sets the pattern to be applied along path in a Beautiful Strokes dictionary.

		@param params	The dictionary.
		@param art		The brush pattern.
	*/
	AIAPI AIErr (*SetArtPaint)(AIDictionaryRef params, AIPatternHandle art);

	/**	Retrieves the pattern to be applied along path from a Beautiful Strokes dictionary.
		Note that this function returns an object, not an error code.

		@param params	The dictionary.
		@return			The brush pattern.
	*/
	AIAPI AIPatternHandle (*GetArtPaint)(ConstAIDictionaryRef params);

	/**	Sets the stretching option in a Beautiful Strokes dictionary.

		@param params	The dictionary.
		@param stretch	True to stretch tiles non-uniformly along the path, false to scale
						up uniformly for the path length.
	*/
	AIAPI AIErr (*SetStretch)(AIDictionaryRef params, AIBoolean stretch);

	/**	Retrieves the stretching option from a Beautiful Strokes dictionary.
		Note that this function returns a Boolean value, not an error code.

		@param params	The dictionary.
		@return			True if the option is set (stretch tiles non-uniformly along the path),
						false if it is clear (scale up uniformly for the path length).
	*/
	AIAPI AIBoolean (*GetStretch)(ConstAIDictionaryRef params);

	/**	Sets the lengths of non-stretching start and end segments for a segmented brush	in a Beautiful Strokes dictionary.
		Lengths are expressed as absolute values in document points. If both values are zero, the brush is a non-segmented brush.

		@param params				The dictionary.
		@param startSegmentLength	Length of start segment.
		@param endSegmentLength		Length of end segment.
	*/
	AIAPI AIErr (*SetStartEndSegmentLength)(AIDictionaryRef params, AIReal startSegmentLength, AIReal endSegmentLength);

	/**	Retrieves the lengths of non-stretching start and end segments for a segmented brush from a Beautiful Strokes dictionary.
		Lengths are expressed as absolute values in document points.

		@param params				The dictionary.
		@param startSegmentLength	[out] A reference in which to return the start-segment length.
		@param endSegmentLength		[out] A reference in which to return the end-segment length.
	*/
	AIAPI AIErr (*GetStartEndSegmentLength)(ConstAIDictionaryRef params, AIReal &startSegmentLength, AIReal &endSegmentLength);

	// Pattern Brushes

	/**	Sets options for repeating pattern tiles along a path in a Beautiful Strokes dictionary.

		@param params				The dictionary.
		@param	beginArt			Brush pattern tile art to be applied to the beginning of the path. May be NULL.
		@param	endArt				Brush pattern tile art to be applied to the end of the path. May be NULL.
		@param	sideArt				Brush pattern tile art to be applied to the main part of the path.  May be NULL.
		@param	insideCornerArt		Brush pattern tile art to be applied to inside corners of the path.  May be NULL.
		@param	outsideCornerArt	Brush pattern tile art to be applied to outside corners of the path.  May be NULL.
		@param	adjustment			Method to use to apply art along path; see \c #RepeatedArtAdjustment().
		@param	spacing				Relative spacing between tiles; for example, 0.5 sets spacing to half
									the width of the tile. Relevant only when adjustment method is \c #kAddSpace.
	*/
	AIAPI AIErr (*SetArtPatternPaint)(AIDictionaryRef params, AIPatternHandle beginArt, AIPatternHandle endArt,
									  AIPatternHandle sideArt,
									  AIPatternHandle insideCornerArt, AIPatternHandle outsideCornerArt,
									  RepeatedArtAdjustment adjustment, AIReal spacing);

	/**	Retrieves options for repeating pattern tiles along a path from a Beautiful Strokes dictionary.

		@param params			The dictionary.
		@param beginArt			[out] A reference in which to return the brush pattern tile art to be
								applied to the beginning of the path. May be NULL.
		@param endArt			[out] A reference in which to return the brush pattern tile art to be
								applied to the end of the path. May be NULL.
		@param sideArt			[out] A reference in which to return the brush pattern tile art to be
								applied to the main part of the path.  May be NULL.
		@param insideCornerArt	[out] A reference in which to return the brush pattern tile art
								to be applied to inside corners of the path.  May be NULL.
		@param outsideCornerArt	[out] A reference in which to return the brush pattern tile art
								to be applied to outside corners of the path.  May be NULL.
		@param adjustment		[out] A reference in which to return the method to use to apply art along path;
								see \c #RepeatedArtAdjustment().
		@param spacing			[out] A reference in which to return the relative spacing between tiles.
								For example, 0.5 sets spacing to half the width of the tile.
								Relevant only when adjustment method is \c #kAddSpace.
	*/
	AIAPI AIErr (*GetArtPatternPaint)(ConstAIDictionaryRef params, AIPatternHandle &beginArt, AIPatternHandle &endArt,
									  AIPatternHandle &sideArt,
									  AIPatternHandle &insideCornerArt, AIPatternHandle &outsideCornerArt,
									  RepeatedArtAdjustment &adjustment, AIReal &spacing);

	// Dashing

	/**	Sets or clears the dash adjustment option in a Beautiful Strokes dictionary.
		When on, adjusts dashes so a certain fraction of the dash length always appears
		at the ends, corners, and intersections of dashed lines.
		(Note that dash/gap intervals are obtained from the art.)

		@param params	The dictionary.
		@param adjust	True to set the option, false to clear it.
	*/
	AIAPI AIErr (*SetDashAdjustment)(AIDictionaryRef params, AIBoolean adjust);

	/**	Retrieves the dash adjustment status from a Beautiful Strokes dictionary.
		See \c #SetDashAdjustment().
		(Note that this function returns a Boolean value, not an error code.)

		@param params	The dictionary.
		@param mixed	[optional] [out] A buffer in which to return true if the dictionary represents an accumulation
						returned from \c #AIPathStyleSuite::GetCurrentPathStyle(), and the selection is mixed.
						By convention, mixed values return false.
		@return			True if the option is set, false if it is clear.
	*/
	AIAPI AIBoolean (*GetDashAdjustment)(ConstAIDictionaryRef params, AIBoolean *mixed);

	// Arrowheads

	/**	Sets arrowhead-related stroke options in a Beautiful Strokes dictionary.
		The arrowhead symbols can be in a library rather than the current document. If so, they are retargeted to the
		document that the params dictionary is attached to, and placed in the "hidden symbols" of that document;
		that is, they do not appear in the Symbols panel. The symbols are parsed to determine the alignment
		parameters and the default scale.

		Any unpainted closed rectangle in the back of the symbol definition is ignored and stripped from
		the art that is used to determine the "tip" of the arrow and placed on the path. These unpainted
		rectangles are assumed to be only for the purpose of making the symbol thumbnails a uniform size.

		Arrowhead art inside the symbol is assumed to be positioned the way it would be when applied as an
		end arrow to a horizontal open path that started at the left and ended at the right.
		If applied as a start arrow, it is reflected horizontally before it is applied.

		If there is a stroked open straight line in the back of the symbol definition (either above or below
		the bounding rectangle if there is one), then the right endpoint of that line is used to specify the
		truncation point. If it additionally has an internal anchor point, the furthest right such anchor point
		is used to specify the attachment point, otherwise the attachment point is the same as the truncation point.

		The tip is treated as the point along the right edge of the bounding box (after removing the bounding tile,
		if any) which is at the same height as the positioning line. The stroke weight of the positioning line
		is used to determine the default scale of the arrowhead. For example, if the positioning stroke is 2 pts, then
		the arrowhead is scaled 50% when it is applied to a path with a 1 pt stroke, and scaled 150% when it
		is applied to a path with a 3 pt stroke. The begin-scale or end-scale factors are applied additionally.

		If there is no positioning line, the default is to use a 100% default scale; that is, to treat the symbol
		as if it were scaled appropriately for a 1 pt line, and to put both the attachment and truncation points
		in the center of the symbol.

		@param params			The dictionary.
		@param beginSymbol		A pointer to the symbol to apply as the arrowhead at the beginning of the path.
								To not change the existing settings, pass null. To remove the arrowhead,
								pass a pointer to null.
		@param endSymbol		The symbol to apply as the arrowhead at the end of the path, null if none
								To not change the existing settings, pass null. To remove the arrowhead,
								pass a pointer to null.
		@param beginScale		The factor by which to scale the begin arrow by, as a percentage relative
								to the default scale. To not change the existing settings, pass \c #kAIRealUnknown.
		@param endScale			The factor by which to scale the end arrow by, as a percentage relative
								to the default scale. To not change the existing settings, pass \c #kAIRealUnknown.
		@param alignment		The rule for positioning the arrows at the ends of the path.
								To not change the existing settings, pass \c #kUnknownArrowAlignment.
	*/
	AIAPI AIErr (*SetArrowheadOptions)(AIDictionaryRef params, AIPatternHandle *beginSymbol, AIPatternHandle *endSymbol,
									   AIReal beginScale, AIReal endScale, ArrowTipAlignment alignment);

	/**	Retrieves arrowhead-related stroke options from a Beautiful Strokes dictionary.
		All pointer arguments are optional and may be null if those options are not being queried.

		@param params			The dictionary to be searched. May be an accumulation of multiple paths, if
								returned from \c #AIPathStyleSuite::GetCurrentPathStyle().
		@param beginSymbol		[out] A buffer in which to return the symbol used as the arrowhead at the beginning of the path, null if none.
		@param endSymbol		[out] A buffer in which to return the symbol used as the arrowhead at the end of the path, null if none.
		@param beginScale		[out] A buffer in which to return the factor to uniformly scale the begin arrow by, as a percentage relative to the default scale.
								Returns \c #kAIRealUnknown if the params dict represents an accumulation with mixed values.
		@param endScale			[out] A buffer in which to return the factor to scale the end arrow by, as a percentage relative to the default scale
								Returns \c #kAIRealUnknown if the params dict represents an accumulation with mixed values.
		@param alignment		[out] A buffer in which to return the rule for positioning the arrows at the ends of the path. Must be the same for both ends.
								Returns \c #kUnknownArrowAlignment if the params dict represents an accumulation
								and the selection is mixed (including if some paths have no arrowheads).
		@param mixedBeginArrows	[out] A buffer in which to return true if there are different choices for the begin-symbol in a mixed selection
								(including if some paths have no begin arrow and some do.)
		@param mixedEndArrows	[out] A buffer in which to return true if there are different choices for the end-symbol in a mixed selection
								(including if some paths have no begin arrow and some do.)
	*/
	AIAPI AIErr (*GetArrowheadOptions)(ConstAIDictionaryRef params, AIPatternHandle *beginSymbol, AIPatternHandle *endSymbol,
									   AIReal *beginScale, AIReal *endScale, ArrowTipAlignment *alignment,
									   AIBoolean *mixedBeginArrows, AIBoolean *mixedEndArrows);

	// Variable Widths

	/**	Sets the source of stroke width in a Beautiful Strokes dictionary.

		@param params	The dictionary.
		@param source	Source of width information for stroke. If \c #kTabletData, set related values
						with \c #SetWidthTabletDataSource() and \c and #SetScale(), particularly minimum and maximum. <br>
						If \c #kUserProfile, call \c #SetCenteredWidthProfile() to set centered width values or
						\c #SetUncenteredWidthProfile() to set independent left and right width values.
	*/
	AIAPI AIErr (*SetWidthSource)(AIDictionaryRef params, StrokeWidthSource source);

	/**	Retrieves the source of stroke width from a Beautiful Strokes dictionary.
		(Note that this function returns a constant value, not an error code.)

		@param params	The dictionary.
		@return			The width source constant.
	*/
	AIAPI StrokeWidthSource (*GetWidthSource)(ConstAIDictionaryRef params);

	/**	Sets the type of tablet data to use for stroke width in the art passed to \c #GenerateArt(),
		in a Beautiful Strokes dictionary.

		@param params	The dictionary.
		@param dataType	The type of tablet data.
						@see \c #AITabletDataType
	*/
	AIAPI AIErr (*SetWidthTabletDataSource)(AIDictionaryRef params, AITabletDataType dataType);

	/**	Retrieves the tablet-data type option from a Beautiful Strokes dictionary.

		@param params	The dictionary.
		@param dataType	The type of tablet data to use for stroke width in the art passed to \c #GenerateArt().
						@see \c #AITabletDataType
	*/
	AIAPI AIErr (*GetWidthTabletDataSource)(ConstAIDictionaryRef params, AITabletDataType &dataType);

	/**	Sets centered width profile for output art in a Beautiful Strokes dictionary. Pass NULL for both arrays to clear the profile.
		A style cannot carry both an uncentered and centered width profile, so if there is an existing
		centered width profile, this function removes it.

		Other than length, the array values are not examined for validity at the time they are set.
		Instead, they are examined when used, and any invalid entries are ignored.
		A width profile in which all the array entries are used to form the stroke contour
		has the following properties:
			<ul><li>The first distance is 0 </li>
			<li>The last distance is 1</li>
			<li>Every distance value should be no less than the previous distance, and no more than the next one</li>
			<li>There should be no more than two consecutive distance values at the same distance </li></ul>
		When interpreting the width profile:
			<ul><li>If the first distance value is not zero, the function acts as if there was an additional value
			at the beginning of both arrays, with the distance being zero and the width being whatever
			the width is in the first entry in the widths array. </li>
			<li>If any distance value is more than 1, or less than the preceding distance value, or equal
			to both the preceding distance value and the following distance value, the function ignores
			the array entries at that index</li>
			<li>If the last distance value is not 1, the function acts as if there were an additional pair of
			entries with the distance equal to 1, and the width equal to the width at the last valid
			distance entry </li>
		    <li>Negative values are interpreted as if they were 0. Values greater than 1 are allowed, but cause
		    the stroke to be wider at those places than the width shown in the Stroke panel, so should be avoided.

			Note that this differs from the interpretation of widths in the functions such	as \c #SetCenteredWidthAtDistance()
			that take a path object and query or modify the width at specific offsets; these incorporate the stroke weight scaling.
			This is because the functions that manage entire width arrays may be dealing with profiles that are shared across multiple
			paths of different weights or belong to unattached preset dictionaries.</li> </ul>

		@param params	The dictionary.
		@param tVals	An array of \c AIReal values ranging from [0-1] representing fractional distances
						along the path.
		@param widths	An array of \c AIReal values the same size as \c tVals representing the fractional stroke width
						at the corresponding offset in the \c tVals array. Values are fractions of the stroke weight
						as shown in the Stroke panel, in the range [0-1].
		@return The error \c #kBadParameterErr if the arrays are of different lengths, or if one is null and the other is not.
	*/
	AIAPI AIErr (*SetCenteredWidthProfile)(AIDictionaryRef params, AIArrayRef tVals, AIArrayRef widths);

	/**	Retrieves the centered width profile for output art from a Beautiful Strokes dictionary.

		@param params		The dictionary.
		@param distances	A reference in which to return an array of \c AIReal values ranging from [0-1] representing fractional distances
							along the path.
		@param widths		A reference in which to return an array of \c AIReal values the same size as \c tVals representing the fractional stroke width
							at the corresponding offset in the \c tVals array.
	*/
	AIAPI AIErr (*GetCenteredWidthProfile)(ConstAIDictionaryRef params, AIArrayRef &distances, AIArrayRef &widths);

	/**	Sets an uncentered width profile for output art in a Beautiful Strokes dictionary, with independent
		left and right width values. Left and right are interpreted by following the path
		from the start point to the end point.
		A path cannot carry both an uncentered and centered width profile, so if there is an existing
		centered width profile, this function removes it.

		@param params		The dictionary.
		@param tVals		An array of \c AIReal values ranging from [0-1] representing fractional distances
							along the path.
		@param leftWidths	An array of \c AIReal the same size as \c tVals representing the width of the left side
							of the stroke at corresponding distances in \c tVals.
		@param rightWidths	An array of \c AIReal the same size as \c tVals representing the width of the right side
							of the stroke at corresponding distances in \c tVals.
	*/
	AIAPI AIErr (*SetUncenteredWidthProfile)(AIDictionaryRef params, AIArrayRef tVals, AIArrayRef leftWidths, AIArrayRef rightWidths);

	/**	Retrieves the uncentered width profile for output art from a Beautiful Strokes dictionary.

		@param params		The dictionary.
		@param tVals		A reference in which to return an array of \c AIReal values ranging from [0-1] representing fractional distances
							along the path.
							The reference count on this array is incremented on return and must be released when no longer needed.
		@param leftWidths	A reference in which to return an array of \c AIReal the same size as \c tVals representing the width of the left side
							of the stroke at corresponding distances in \c tVals.
							The reference count on this array is incremented on return and must be released when no longer needed.
		@param rightWidths	A reference in which to return an array of \c AIReal the same size as \c tVals representing the width of the right side
							of the stroke at corresponding distances in \c tVals.
							The reference count on this array is incremented on return and must be released when no longer needed.
	*/
	AIAPI AIErr (*GetUncenteredWidthProfile)(ConstAIDictionaryRef params, AIArrayRef &tVals, AIArrayRef &leftWidths, AIArrayRef &rightWidths);

	/**	INTENDED FOR FUTURE ENHANCEMENTS - All non-default options are currently ignored.
		Can only be called after setting the width profile with \c #SetCenteredWidthProfile() or \c #SetUncenteredWidthProfile().
		If not present (the usual case), all width markers use default options, which are dependent upon the context. All arrays can be null.
		The defaults are for markers that are concurrent with corner anchor points of the path to be treated as
		tethered corner width markers, and for all other markers to be untethered smooth markers, with the
		default smoothness values.

		To save space, there is a single array of marker options for both centered and uncentered width profiles,
		with different flag values to distinguish when the options are different for the left and right sides
		of the stroke (for example, if it is smooth on the left side but cornered on the right.)
		If an incoming smoothness array exists but the outgoing smoothness array does not exist on that side
		of the path, then the outgoing smoothness is inherited from the incoming smoothness.
		Similarly, if the left smoothness array(s) exist but the right smoothness arrays do not, then
		the right smoothness is inherited from the left smoothness.

		You must only call this function AFTER either \c #SetCenteredWidthProfile() or \c #SetUncenteredWidthProfile();
		it returns /c #kBadParameterErr if any of the arrays are non-null and either there is no width profile,
		or the existing width profile has a different number of markers than the size of the detail arrays.
		No validation is done on the contents of the arrays, other than their lengths.

		@param params					The dictionary.
		@param markerOptions			An array of integers parallel to the t values, interpreted as a bit vector
										of WidthMarkerFlagValues
		@param incomingLeftSmoothness	An array of \c AIReal numbers ranging from [0-1] parallel to the t values,
										ranging from minimally smooth at 0 to maximally smooth at 1.
		@param outgoingLeftSmoothness	An array of \c AIReal numbers ranging from [0-1] parallel to the t values,
										ranging from minimally smooth at 0 to maximally smooth at 1.
		@param incomingRightSmoothness	An array of \c AIReal numbers ranging from [0-1] parallel to the t values,
										ranging from minimally smooth at 0 to maximally smooth at 1.
		@param outgoingRightSmoothness	An array of \c AIReal numbers ranging from [0-1] parallel to the t values,
										ranging from minimally smooth at 0 to maximally smooth at 1.
		@return							The error \c #kBadParameterErr if any of the arrays are non-null
										and either there is no width profile, or the existing width profile
										has a different number of markers than the size of the detail arrays.
	*/
	AIAPI AIErr (*SetWidthProfileDetails)(AIDictionaryRef params, AIArrayRef markerOptions,
										  AIArrayRef incomingLeftSmoothness, AIArrayRef outgoingLeftSmoothness,
										  AIArrayRef incomingRightSmoothness, AIArrayRef outgoingRightSmoothness);

	/**	Retrieves the options for the width profile markers from a Beautiful Strokes dictionary.

		@param params					The dictionary.
		@param markerOptions			A reference in which to return an array of integers parallel to the t values, interpreted as a bit vector of \c #WidthMarkerFlagValues.
										The reference count on this array is incremented on return and must be released when no longer needed.
		@param incomingLeftSmoothness	A reference in which to return an array of \c AIReal numbers parallel to the t values.
										The reference count on this array is incremented on return and must be released when no longer needed.
		@param outgoingLeftSmoothness	A reference in which to return an array of \c AIReal numbers parallel to the t values.
										The reference count on this array is incremented on return and must be released when no longer needed.
		@param incomingRightSmoothness	A reference in which to return an array of \c AIReal numbers parallel to the t values.
										The reference count on this array is incremented on return and must be released when no longer needed.
		@param outgoingRightSmoothness	A reference in which to return an array of \c AIReal numbers parallel to the t values.
										The reference count on this array is incremented on return and must be released when no longer needed.
	*/
	AIAPI AIErr (*GetWidthProfileDetails)(ConstAIDictionaryRef params, AIArrayRef &markerOptions,
										  AIArrayRef &incomingLeftSmoothness, AIArrayRef &outgoingLeftSmoothness,
										  AIArrayRef &incomingRightSmoothness, AIArrayRef &outgoingRightSmoothness);

	/**	If a path has variable widths (either centered or uncentered), retrieves a vector of the values
		from the distance array, after adjustment to shift any anchored width points to the relative
		distance along that path of the path positions they are anchored to.
		<ul><li>If the path has no variable widths, the returned vector is empty.</li>
		<li>If the path has variable widths but no width profile anchors, the returned vector contains
		the same distance values that are in the distance array returned
		by \c #GetCenteredWidthProfile() or \c #GetUncenteredWidthProfile().</li></ul>

		@param path					The path.
		@param adjustedDistances	A reference in which to return the result vector. The reference
									count on this array is incremented on return and must be released
									when no longer needed.
	*/
	AIAPI AIErr (*GetPathAdjustedWidthDistances)(AIArtHandle path, AIArrayRef &adjustedDistances);

	/**	Retrieves the left, right, and combined widths of the focal stroke at a fraction of the distance along a path,
		and reports the source of the widths.
		The widths are analogous to the stroke weights as returned by the \c #AIArtStyle::GetPaintAttributes().
		As such, they include the stroke weight scaling, but do not include the impact of pattern or art brush
		scale options or pattern or art brush tile sizes.

		@param path				[in] The path to be examined for width data.
		@param lengthFraction	[in/out] Upon input, the fraction of the path length at which the width is being queried.
								Upon output, if the width source is \c #kCenteredProfileMark or \c #kUncenteredProfileMark, the
								possibly snapped position of that mark. To find whether snapping has occurred,
								cache the original length fraction and compare it to the returned value.
		@param tolerance		[in] If positive and the path has a user-specified variable width profile,
								and the input length fraction is within this tolerance of one of the t values in the
								width array, then the length fraction is snapped to that t value. If zero
								or negative, a tolerance of .001 is used.
		@param totalWidth		[out][optional] A buffer in which to return the total width at the given position,
								as obtained from the width source.
		@param leftWidth		[out][optional] A buffer in which to return the stroke width on the left side of the path
								at the given position, as obtained from the width source.
		@param rightWidth		[out][optional] A buffer in which to return the stroke width on the right side of the path
								at the given position, as obtained from the width source.
		@param widthSource		[out][optional] A buffer in which to return the width-source constant. It will be one of kConstantWidth, kTabletData,
								kCenteredProfileMark, kUncenteredProfileMark, kCenteredProfileInterpolation, kUncenteredProfileInterpolation.
		@param markerIndex		[out][optional] A buffer in which to return the marker index. If width source is from a centered
								or uncentered profile, the index into the parallel t and width arrays of the marker.
								For \c #kCenteredProfileMark and \c #kUncenteredProfileMark,
								it is the index of the marker at that location; for \c #kCenteredProfileInterpolation and
								\c #kUncenteredProfileInterpolation, it is the index of the preceding marker.
		@param markerDetails	[in/out][optional] On input, the only meaningful flag values are \c #kIncomingWidthMarker and
								\c #kOutgoingWidthMarker. These specify which of the two markers should be returned in
								the event that there are two markers at exactly the input length fraction. (If snapping
								occurs, then the flags are ignored; the incoming marker is returned when
								it snaps upward, and the outgoing when it snaps downward.) If null
								or if neither or both of those flags are on, and there are two markers
								at exactly the input length fraction, then the larger of the two is returned.
								On output, if  width source is \c #kCenteredProfileMark or \c #kUncenteredProfileMark, can
								contain one of \c #kIncomingWidthMarker or \c #kOutgoingWidthMarker, and/or \c #kCornerWidthMarker.
	*/
	AIAPI AIErr (*GetWidthsAtDistance)(AIArtHandle path, AIReal &lengthFraction, AIReal tolerance,
									   AIReal *totalWidth, AIReal *leftWidth, AIReal *rightWidth,
									   StrokeWidthSource *widthSource, short *markerIndex, WidthMarkerFlags *markerDetails);

	/**	Sets the total width of the focal stroke at a given fraction of the distance along the path. (If lengthFraction is within
		0.001 of an existing t value in the width profile, modifies the existing width at that t value rather than
		inserting a new one.)
		<ul><li>If there is already a centered width profile, inserts the indicated value into it.</li>
		<li>If there is already an uncentered profile, this is equivalent to setting the left and right widths to half the input width.</li>
		<li>If there is not yet any user specified width profile, creates a centered width profile from the current stroke source
		and then modifies it and sets the stroke-width source to \c #kUserProfile. </li></ul>

		@param path				The path.
		@param lengthFraction	A fraction of the distance along the path	at which to set the width.  If within 0.001 of an existing t value
								in the width profile, modifies the existing width at that t value rather than inserting a new one.
		@param width			The new width.
		@param options			A logical OR of bit flags that determine how to perform the operation.
	*/
	AIAPI AIErr (*SetCenteredWidthAtDistance)(AIArtHandle path, AIReal lengthFraction, AIReal width, WidthMarkerFlags options);

	/**	Sets the left and right widths of the focal stroke at a given fraction of the distance along the given path. (If lengthFraction
		is within 0.001 of an existing t value in the width profile, modifies the existing width at that t value
		rather than inserting a new one.)
		<ul><li>If there is already an uncentered width profile, it inserts the indicated values into it.</li>
		<li>If left and right widths are equal and there is already a centered width profile, inserts their sum into it.</li>
		<li>If left and right widths are unequal and there is not yet an uncentered width profile, or if they are equal
		and there is not yet any width profile, it creates one from the current stroke source and then modifies it
		and sets the stroke-width source to \c #kUserProfile. </li></ul>

		@param path				The path.
		@param lengthFraction	A fraction of the distance along the path	at which to set the width.  If within 0.001 of an existing t value
								in the width profile, modifies the existing width at that t value rather than inserting a new one.
		@param leftWidth		The new left width.
		@param rightWidth		The new right width.
		@param options			A logical OR of bit flags that determine how to perform the operation.
	*/
	AIAPI AIErr (*SetUncenteredWidthsAtDistance)(AIArtHandle path, AIReal lengthFraction,
												 AIReal leftWidth, AIReal rightWidth, WidthMarkerFlags options);

	/**	Moves the width marker at the given index to a new t value. If the given marker is incoming-only or
		outgoing-only due to two markers being at the same t value, both are moved together.
		Only the content of the tValue array changes, so this works for either centered or non-centered widths.

			@param path			The path.
			@param markerIndex	The 0-based index position of the marker to move.
			@param newTValue	[in, out] Fraction of length along whole path to which the marker should be moved.
								In the range [0-1].
			@param options		A logical OR of bit flags that determine how to perform the operation:
				<ul> <li> If \c #kCopyMarker is on, the marker is duplicated and the new copy moved, while the old
				one remains at the prior location. There must always be a marker at 0 and one at 1,
				so any movement of the first or last marker is implicitly a duplication even if this flag is off. </li>
				<li>If \c #kSpreadWidthChanges is on, the other markers on the side that this marker is moving
				away from are spread out proportionally to cover the larger distance, and the other markers
				on the side that this marker is moving towards are compressed proportionally to fit in the
				smaller distance. The scope of the spreading is limited by the selection state and corner
				status of the adjacent anchor points.</li>
				<li>If \c #kSpreadWidthChanges is off and \c #kLimitAtNeighbors is on, and there is another width marker
				between the current t value at the given index and the new t value, then the marker stops
				when it hits the adjacent marker. No error code is returned in this case, but \c newTValue
				is updated to the actual destination. To determine whether it stopped, cache the original
				value and compare with the returned value.
				(Note that this causes the two markers at the same location to become an incoming-only
				outgoing only pair where the width may jump discontinuously.)</li>
				<li>If \c #kSpreadWidthChanges and \c #kLimitAtNeighbors are both off, then the moved marker is allowed
				to jump past other markers as if they were not there.</li>
				</ul>
			@return				The error \c #kBadParameterErr if the path does not have a user width profile or
				if the new t value is not in the range [0-1].
	*/
	AIAPI AIErr (*SlideWidthMarkerToNewT)(AIArtHandle path, short markerIndex, AIReal &newTValue, WidthMarkerFlags options);

	/**	Deletes the width point at the given index position from the given path. The first and last width points cannot be deleted.

			@param path			The path.
			@param markerIndex	The index position of the point to delete.
	*/
	AIAPI AIErr (*DeleteWidthPoint)(AIArtHandle path, short markerIndex);

	/**	Adds, removes, or reindexes width profile anchors as needed before editing a path.
		An editing tool or command calls this before modifying the geometry of a path
		or applying a different art style.

		Modifies anchors at a subset of the same places that cause \c #kSelectorAINotifyEdits
		to be sent to plug-in groups ancestral to the edited path. It is not necessary to send this message
		if the path is being transformed in its entirety in a way that does not change the relative lengths
		of path segments.

		If width anchors already exist at the relevant anchor points, and the numbers of anchor points are
		not changing, does nothing.

		@param path				The path to be edited.
		@param editDescription	The type of edit to be done.
	*/
	AIAPI AIErr (*AdjustWidthAnchorsBeforePathEdit)(AIArtHandle path, const PathEditDescription &editDescription);

	/**	Tests whether a cursor point on a path is within a given tolerance of the region covered by the stroke, and if
		so, reports additional details about what part of the stroke was hit; see  \c #StrokeHitResults.
		For brush strokes, the entire region within the brush design's tile box is considered to be stroked.

		@param path			The path.
		@param cursor		The cursor point.
		@param tolerance	The tolerance value.
		@param hitResults	A buffer in which to return the result.
	*/
	AIAPI AIErr (*StrokeHitTest)(AIArtHandle path, const AIRealPoint &cursor, AIReal tolerance, StrokeHitResults *hitResults);

};

#include "AIHeaderEnd.h"
#endif
