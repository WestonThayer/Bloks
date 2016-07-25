#ifndef __AI140DrawArt__
#define __AI140DrawArt__

/*
 *        Name:	AIDrawArt.h
 *   $Revision: $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Draw Art Suite.
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

#ifndef __AIArt__
#include "AIArt.h"
#endif

#ifndef __AIColor__
#include "AIColor.h"
#endif

#ifndef __AIColorConversion__
#include "AIColorConversion.h"
#endif

#ifndef __AIRaster__
#include "AIRaster.h"
#endif

#include "AIDrawArt.h"

#include "ADMAGMTypes.h"

#include "AIHeaderBegin.h"

/** @file AIDrawArt.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIDrawArtSuite				"AI Draw Art Suite"
#define kAIDrawArtSuiteVersion8		AIAPI_VERSION(8)
#define kAI140DrawArtSuiteVersion	kAIDrawArtSuiteVersion8
#define kAI140DrawArtVersion		kAI140DrawArtSuiteVersion


/*******************************************************************************
 **
 **	Types
 **
 **/

/** Drawing data, defines an art object to be drawn, the object it is
	to be drawn into and parameters affecting how it is to be
	drawn. See \c #AIDrawArtSuite::DrawArt(), \c #AIDrawArtSuite::BeginDrawArt() */
typedef struct AI140DrawArtData {
	/** The version of \c #AIDrawArtSuite in use, a \c #kAIDrawArtVersion value. */
	short version;
	/** Flags that modify drawing behavior, a logical OR of
		\c #AIDrawArtFlagBitPos values. */
	AIDrawArtFlags flags;
	/** The type of port that is the destination for the draw operation. */
	AIDrawArtOutputType type;
	/** The point in the source artwork coordinates that is mapped to (0,0) in
	 	the destination port.*/
	AIRealPoint origin;
	/** The transformation matrix to be applied after placement
		at the origin. */
	AIRealMatrix matrix;
	/** The art object to be drawn. */
	AIArtHandle art;
	/** The destination clipping bounds. */
	AIRealRect destClipRect;
	/** When true, \c destClipRect is erased before the art is drawn. */
 	AIBoolean eraseDestClipRect;
	/** The art object that was being drawn when the operation was
		interrupted. See \c #kAIDrawArtPreviewInterrupt and \c #kAIDrawArtPreviewContinue. */
	AIArtHandle interruptedArt;
	 /** The greeking threshold. If the point size of text,
	 	after transformation to the coordinate system of the
		destination port, is smaller than this value, the text
		is greeked. Use -1 to indicate no greeking. */
	AIReal greekThreshold;
	/** Not used */
	AIExtendedRGBColorRec selectionColor;
	/** The port that is the destination for the draw operation.*/
	AIDrawArtOutputUnion output;
} AI140DrawArtData;


/*******************************************************************************
 **
 **	Suite
 **
 **/

/**	@ingroup Suites
	Legacy Version
	These functions draw Illustrator artwork to an \e output \e port
	(drawing surface). The port can be a screen window, or it can be
	an offscreen drawing surface used to rasterize artwork.

	The many drawing options are controlled by values in an \c #AIDrawArtData
	structure and related option structures \c #AIColorConvertOptions and
	\c #AIDrawArtFlags.

	When drawing to a port whose color space does  not match the
	document color space, bracket a sequence of calls
	to \c #DrawArt() with calls to.\c #BeginDrawArt() and \c #EndDrawArt().
	Examples are drawing a CMYK document to an RGB window,
	or an RGB document to a window with a different profile.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIDrawArtSuite and \c #kAIDrawArtSuiteVersion8.
 */
typedef struct {

	/** Draws artwork as specified
			@param data A pointer to the structure that specifies an art object
				to be drawn, the object it is to be drawn into, and
				parameters affecting how it is to be drawn.
			@param options An \c #AIColorConvertOptions object that sets
				the appropriate black preservation value--that is, whether
				a CMYK to RGB/Gray color transformation maps CMYK 0,0,0,1
				to the darkest black:
					\li By default, the operation uses the standard conversion,
						which never uses black preservation.
					\li For export, the operation uses the black-preservation setting
						that is currently configured in the print and export preferences.
					\li For preview, the operation uses the black-preservation setting
						that is currently configured in the screen-display preferences.
	*/
	AIAPI AIErr (*DrawArt)( AI140DrawArtData *data, const AIColorConvertOptions& options );

	/** Establishes a temporary drawing surface whose color space matches the
		document space. Must be paired with a call to \c #EndDrawArt() at the end
		of a sequence of calls \c #DrawArt().
			@param data A pointer to the structure that specifies an art object
				to be drawn, the object it is to be drawn into, and
				parameters affecting how it is to be drawn. Can be \c NULL.
			@param options An \c #AIColorConvertOptions object; see \c #DrawArt().
			@param flags A set of options that modify drawing behavior, a logical
				OR of \c #AIDrawArtFlagBitPos values.
				@note If you set the \c #kAIDrawArtOPP flag to draw to an OPP port,
					the "begin" call temporarily changes the target port in the \c data
					structure. The call to \c #EndDrawArt() restores the
					original port. In this case, the set of spot colors needed for the
					OPP port are determined from the art object specified in \c data, or
					from the entire document if no art object is specified.

		*/
	AIAPI AIErr (*BeginDrawArt)( AI140DrawArtData * data, const AIColorConvertOptions& options, AIDrawArtFlags flags );

	/** Copies the contents of the temporary drawing surface to the final destination.
			@param data A pointer to the drawing data structure that was passed to
				the corresponding call to \c #BeginDrawArt().
			@param options The \c #AIColorConvertOptions object that was passed to
				the corresponding call to \c #BeginDrawArt().
		*/
	AIAPI AIErr (*EndDrawArt)( AI140DrawArtData *data, const AIColorConvertOptions& options );

	/** Draws a color swatch. Color swatches are always assumed to be drawn for the
		purpose of screen display.
			@param data A pointer to the structure that specifies an art object
				to be drawn, the object it is to be drawn into, and
				parameters affecting how it is to be drawn.
		*/
	AIAPI AIErr (*DrawColorSwatch)( AIDrawColorData *data );

	/** Draws the highlighting annotations for an art object. Call only in the response
		to an annotator's Draw Annotations message.
			@param art The art object.
			@param color The highlight color.
			@param lineWidth The stroke width.
	*/
	AIAPI AIErr (*DrawHilite)( AIArtHandle art, AIRGBColor* color, float lineWidth );

	/** Draws a thumbnail of an art object to the AGM port. Thumbnails are always assumed
		to be drawn for the purpose of screen display. No transformations are applied, and
		the image is drawn to fit into the destination rectangle.
			@param art The art object, of type \c #kRasterArt or \c #kPlacedArt.
			@param port A pointer to the AGM port.
			@param dstrect The destination rectangle, a bounding box for the thumbnail image.
		*/
	AIAPI AIErr (*DrawThumbnail) ( AIArtHandle art, void* port, AIRealRect* dstrect );

} AI140DrawArtSuite;


#include "AIHeaderEnd.h"


#endif
