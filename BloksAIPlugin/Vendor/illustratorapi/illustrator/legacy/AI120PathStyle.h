#ifndef __AI120PathStyle__
#define __AI120PathStyle__

/*
 *        Name:	AI120PathStyle.h
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator Path Style Suite for AI 12
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

#include "AIPathStyle.h"

#ifndef __AI70Color__
#include "AI70Color.h"
#endif

#include "AIHeaderBegin.h"



/*******************************************************************************
 **
 **	Suite name and version
 **
 **/

#define kAI120PathStyleSuite			kAIPathStyleSuite
#define kAIPathStyleSuiteVersion8		AIAPI_VERSION(8)
#define kAI120PathStyleSuiteVersion		kAIPathStyleSuiteVersion8
#define kAI120PathStyleVersion			kAI120PathStyleSuiteVersion

/*******************************************************************************
 **
 **	Suite
 **
 **/

/** A path style describes the paint information for an object, including stroke
	and fill. Use the Path Style Suite to access or set path style information for
	paths.
*/
typedef struct {

	/** Retrieves the path style used to fill and/or stroke the object. The object
		must be of type kPathArt, kMeshArt, or kRasterArt. All other types return
		kBadParameterErr. */
	AIAPI AIErr (*GetPathStyle) ( AIArtHandle path, AIPathStyle *style );
	/** Sets the path style used to fill and/or stroke the object. The object
		must be of type kPathArt, kMeshArt, or kRasterArt. All other types return
		kBadParameterErr. */
	AIAPI AIErr (*SetPathStyle) ( AIArtHandle path, AIPathStyle *style );
	
	
	/** Get the common attributes of the current selected objects. Note that this
		API returns a partial style. */
	AIAPI AIErr (*GetCurrentPathStyle) ( AIPathStyle *style, AIPathStyleMap* stylemap );
	
	/** Apply the path style to any currently selected and paint-targetted objects.
		If a targetted object has an active style, the path style will be merged
		in to the focal fill and stroke filters. Any effects and non-focal fills
		and strokes will be unmodified. Use SetCurrentPathStyleForceSimple instead
		if you want to blow away any active styles. (The reason we didn't just add
		another parameter was so as not to have to bump the suite version number.) */ 
	AIAPI AIErr (*SetCurrentPathStyle) ( AIPathStyle *style, AIPathStyleMap* stylemap );

	/** Use this function to import the styles contained in the specified file. The
		styles are imported into a new document whose handle is returned. The styles
		can then be accessed through their respective APIs. For example the art
		style can be obtained through the AIArtStyleSuite and the swatches can be
		obtained through the AISwatchListSuite. */
	AIAPI AIErr (*ImportStyles) ( const ai::FilePath &source, AIDocumentHandle *newdoc );

	/** Do not use this function unless you desperately need to import mixed color space
		styles.  AI artwork does not allow mixed color space as of version 12, so using
		this function may cause serious damage on your artwork.  The intention of function
		is allowing mixed color space in Swatch Libraries.  AIPathStyleSuite::ImportStyles()
		does not work for this purpose because it always forces converting mixed color styles
		to a single color space. */
	AIAPI AIErr (*ImportStylesMixedColorSpace) ( const ai::FilePath &source, AIDocumentHandle *newdoc );

	/** Apply the AIColor to the object.  This does what is generally wanted when you've
		got an AIColor and you've got an object, and you want the object painted with the
		color. It handles setting the gradient vector to the default, enumerates groups,
		does the right thing on compound paths, etc. (If, for example, you have an object
		that's stroked with a dashed line and you pass in a new color with the onStroke
		parameter true, the old dash pattern will be retained. If the object didn't have
		a stroke before, the current paint style is looked at. If the current paint style
		also doesn't have a stroke, a sensible default is used.)

		The art object can be any type except kUnknownArt, kPlacedArt, or kMysteryPathArt.

		Since the routine enumerates container objects, for efficiency care should be taken
		that you do not call SetObjectAIColor on both a container and its children.
	*/
	AIAPI AIErr (*SetObjectAIColor) ( AIArtHandle art, AIColor *color, AIBoolean onStroke );

	/** Simple routine to convert from AIColor to AI70Color. */
	AIAPI AIErr	(*AIColorToAI70Color) ( AIColor *from, AI70Color *to);
	/** Simple routine to convert from AI70Color to AIColor. */
	AIAPI AIErr	(*AI70ColorToAIColor) ( AI70Color *from, AIColor *to);

	/** Determines whether the path style makes use of the supplied color in its fill
		or stroke and returns an indicator of how it is used. A style map may optionally
		be supplied for a partial style. If matchTint is false the tint percentage for
		spot and global process colors is not considered. If lookForIndirectUsage is
		true and the path style is a pattern then its definition is searched for a
		match. */
	AIAPI AIErr (*PathStyleUsesAIColor) ( AIPathStyle *pathStyle,
											AIPathStyleMap *psMap,
											AIColor *color,
											AIBoolean matchTint,
											AIBoolean lookForIndirectUsage,
											AIColorUsedHow *usage );

	/**	A routine which takes an AIColor and applies it to an AIPathStyle, doing what
		is generally wanted when people ask "why is it such a pain to simply set the
		color of an object?"  

		The path style map parameter is optional.

		If the newColor is a gradient or pattern, only the global object handle is
		relevant - the vector and transform fields are ignored. When the old pathStyle
		is already of the same kind, the existing vector and transform are used; if
		it is not, then default values are used. If newColor is a spot color, though,
		the tint is used. This is because this API is mainly intended for the use of
		the Swatches palette. Swatches contain tint info for spot colors, but they
		do not record gradient vector (even relative vector) or pattern transform data.

		If matchColor is non-null, then the onStroke parameter is ignored, and the
		newColor is applied to the fill and/or the stroke, whichever of them has the
		same color as matchColor. The matching is exact, including color space. This
		will never assign paint to an unpainted stroke or fill unless the matchColor
		is kNoneColor.

		If matchColor is null, then the newColor is applied to the stroke if onStroke
		is true, or to the fill if onStroke is false. (To apply to both, you must
		call this twice.)

		When it can't gather things from the pathStyle (which is assumed to be the "old"
		color of the object in question), it first looks at the current paint style and
		if that's not helpful, uses some reasonable (to me) defaults.  Search for the
		text "DEFAULT" below to find those if you want to muck with them. Defaults
		are only necessary when changing from one kind of color to another (e.g.,
		from a solid to a pattern or gradient) or when assigning color to a fill
		or stroke that was previously unpainted.

		The destination arthandle is used for the case where it needs to figure out the
		gradient vector based on the object's bounds. In the case where the object is
		part of a compound path, the bounds are calculated from the entire compound
		group.

		If whatChanged is non-null, returns in *whatChanged an AIColorUsedHow value
		indicating what part of the pathStyle (fill and/or stroke) was changed. (It is
		not necessary to do a SetPathStyle on the object if the old path style is the
		same as the new one.)
	*/
	AIAPI AIErr (*ApplyAIColorToPathStyle) ( AIPathStyle *pathStyle,
											AIPathStyleMap	*psMap,	// can be null
											AIColor			*newColor,
											AIColor			*matchColor,
											AIBoolean		onStroke,
											AIBoolean		useOldTint,
											AIArtHandle		destination,
											AIColorUsedHow	*whatChanged );

	/** Examine the art object, which can be any type, for usage of the targetColor,
		and return a vector of AIColorUsedHow values in *usage.

		If lookForIndirectUsage is true, it returns whether the art object would
		cause the color to be considered "in use" on the swatch palette. This
		includes usage inside patterns, gradients, and graph designs.

		If lookForIndirectUsage is false, the scan will not look inside of patterns,
		gradients, or graph designs. It will still look inside the graph style change
		records of graph objects.
	*/
	AIAPI AIErr (*ObjectUsesAIColor) ( AIArtHandle art,
										AIColor *targetColor,
										AIBoolean matchTint,
										AIBoolean lookForIndirectUsage,
										AIColorUsedHow *usage );

	/** For any direct usage of the oldColor in the art object, do a SetObjectAIColor to the
		newColor. "Direct" usage means the color of a stroke or fill, including inside graph
		path style change records. It does not cover colors used *inside* gradients, patterns,
		or graph designs that are attached to the object. (Indirect usages inside patterns
		and gradients are to be replaced by defining a new pattern or gradient, then calling
		ReplaceObjectAIColor with the oldColor and newColor being the pattern or gradient
		that was redefined. Indirect usage inside graph designs are similar, except that
		one doesn't call ReplaceObjectAIColor because a graph design isn't a color.)
		
		New for AI9:  if art is nil, replaces all usages in the current document

		If useOldTint is true, and both oldColor and newColor are custom colors, then
		the tint from the oldColor is used, otherwise the tint from the newColor is used.

		Sets *madeReplacement to true if it found oldColor and made a replacement, and
		to false if it didn't.

		The art object can any type except kPlacedArt, including those which are reported
		as kMysteryPathArt (paths inside text paths and graphs), and those which are
		reported as kUnknownArt, such as graphs and layer masks. (Since kPlacedArt is a
		reference to an external file, colors cannot be replaced inside of it.)
	*/
	AIAPI AIErr (*ReplaceObjectAIColor) ( AIArtHandle art,
											AIColor *oldColor, AIColor *newColor,
											AIBoolean useOldTint,
											AIBoolean *madeReplacement /* can be NULL */ );

	/** Get the default path style that tools should use when creating new objects other
		than text objects. */
	AIAPI AIErr (*GetInitialPathStyle) ( AIPathStyle *style );
	/** Set the default path style that tools should use when creating new objects other
		than text objects. */
	AIAPI AIErr (*SetInitialPathStyle) ( AIPathStyle *style );
	/** Get the default path style that tools should use when creating text objects. */
	AIAPI AIErr (*GetInitialTextStyle) ( AIPathStyle *style );
	/** Set the default path style that tools should use when creating text objects. */
	AIAPI AIErr (*SetInitialTextStyle) ( AIPathStyle *style );
	
	/** Take an AIColor structure and make sure that everything in it is appropriate for the
		current artwork, creating replacements if necessary.  For example, if you get a
		pattern from drag&drop, the pattern may not be in the current artwork.  (Usually it
		will be in the clipboard artwork).  This would replace it with an equivalent pattern
		that is in the current artwork. */
	AIAPI AIErr (*RetargetForCurrentDoc) ( AIColor *color) ;

	/** Like SetCurrentPathStyle, except that when a selected object has an active style,
		it will merge the input style values only with the paint attributes, and give
		the object that simple style. Both of the input pointers can be nil to replace
		all selected active styles with the simple style corresponding to their focal
		fill and/or stroke filters.
	*/
	AIAPI AIErr (*SetCurrentPathStyleForceSimple) ( AIPathStyle *style, AIPathStyleMap* stylemap );

	/** Like SetPathStyle, except that when a selected object has an active style,
		it will merge the input style values only with the paint attributes, and give
		the object that simple style. The input style can be nil to replace an active
		style with the simple style corresponding to its focal fill and/or stroke filters.
	*/
	AIAPI AIErr (*SetPathStyleForceSimple) ( AIArtHandle path, AIPathStyle *style );
	
	/** Interpolate the path style.  If percent is 0, styleOut is style0; if percent
		is 1, styleOut is style1. (Despite the misleading param name, percent is
		not a percentage but a value from 0 to 1.) See also the AIPathInterpolateSuite. */
	AIAPI AIErr (*InterpolatePathStyle) ( AIPathStyle *style0, AIPathStyle *style1,
		AIPathStyle *styleOut, AIReal percent);

	/** Interpolate just the AIColor. If color kinds are incompatible (e.g., two patterns),
		colorOut is always returned as color0. See also the AIPathInterpolateSuite. */ 
	AIAPI AIErr (*InterpolateAIColor) ( AIColor *color0, AIColor *color1, AIColor *colorOut,
										AIReal fraction );

	// New for AI12: 

	/** Sets the syncInitialPathStyle state

		When syncInitialPathStyle is TRUE, the initial path style is 
		synchronized with the current path style, and the UI in the swatches palette,
		color palette, and toolbox report the current path style. This synchronization
		happens when the selection changes and when GetCurrentPathStyle/SetCurrentPathStyle
		or GetInitialPathStyle/SetInitialPathStyle are called. syncInitialPathStyle is
		true the majority of the time.
		
		When syncInitialPathStyle is FALSE, the initial path style and the current path style
		become independant. In this mode GetCurrentPathStyle/SetCurrentPathStyle does not 
		affect the initial path style and GetInitialPathStyle/SetInitialPathStyle does not affect
		the current path style and the current selection. The UI in the swatches palette,
		color palette, and toolbox also report the initial path style rather than the current
		path style.

		Why this is useful:
		Sometimes a tool may want to maintain a "tool path style" that is not modified when
		the selection changes. This	allows the user to have a selection, choose
		a specific tool and color, and not have the color apply to the current
		selection. Such behavior is useful for the paintbucket tool, for example. To get
		this behavior the tool should set the syncState to true 
		and use GetInitialPathStyle/SetInitialPathStyle in place of
		GetCurrentPathStyle/SetCurrentPathStyle while the tool is selected. */
	AIAPI AIErr (*SetSyncInitialPathStyle) ( AIBoolean syncInitialPathStyle );
	/** Gets the syncInitialPathStyle state */
	AIAPI AIBoolean (*GetSyncInitialPathStyle)();

} AI120PathStyleSuite;


#include "AIHeaderEnd.h"

#endif
