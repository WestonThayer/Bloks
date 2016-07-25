#ifndef __AI180DocumentView__
#define __AI180DocumentView__

/*
 *     Name:	AI180DocumentView.h
 *     Purpose:	Adobe Illustrator Document View Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2008 Adobe Systems Incorporated.
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

#ifndef __AIDocument__
#include "AIDocument.h"
#endif

#include "AIDocumentView.h"

#include "AIHeaderBegin.h"

/** @file AI180DocumentView.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI180DocumentViewSuite				kAIDocumentViewSuite
#define kAI180DocumentViewSuiteVersion12	AIAPI_VERSION(12)

// latest version
#define kAI180DocumentViewSuiteVersion		kAI180DocumentViewSuiteVersion12
#define kAI180DocumentViewVersion			kAI180DocumentViewSuiteVersion

/*******************************************************************************
 **
 **	Suite
 **
 **/


/** @ingroup Suites
	Use these functions to get and set properties of a document view,
	including the bounds, center, zoom, and screen mode.

	To operate on the current view, you can usually pass \c NULL for
	the \c view parameter. To get a view reference for the current
	view, pass 0 to \c #AIDocumentViewSuite::GetNthDocumentView().

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIDocumentViewSuite and \c #kAIDocumentViewVersion.
*/
struct AI180DocumentViewSuite {

	/** Retrieves the bounds of a document view in artwork coordinates (that is,
		the portion of the artboard that is visible in the window).
			@param view The view reference, or \c NULL for the current view.
			@param bounds [out] A buffer in which to return the bounding box.
		*/
	AIAPI AIErr (*GetDocumentViewBounds) ( AIDocumentViewHandle view, AIRealRect *bounds );

	/** Retrieves the center of a document view in artwork coordinates (that is, the
		point of the artboard that maps to the center of the window).
			@param view The view reference, or \c NULL for the current view.
			@param center [out] A buffer in which to return the center point.
		*/
	AIAPI AIErr (*GetDocumentViewCenter) ( AIDocumentViewHandle view, AIRealPoint *center );

	/** Sets the point of the artboard that maps to the center of the window for a view.
			@param view The view reference, or \c NULL for the current view.
			@param center The new center point.
		*/
	AIAPI AIErr (*SetDocumentViewCenter) ( AIDocumentViewHandle view, const AIRealPoint *center );

	/** Retrieves the zoom factor for a view. This is the scale factor from artwork
		coordinates to window coordinates.
			@param view The view reference, or \c NULL for the current view.
			@param zoom [out] A buffer in which to return the zoom factor, a percentage
				value where 1 is 100% (actual size), 0.5 is 50% and 2 is 200%.
		*/
	AIAPI AIErr (*GetDocumentViewZoom) ( AIDocumentViewHandle view, AIReal *zoom );

	/** Sets the scale factor from artwork coordinates to window coordinates for a view.
		The scale factor is silently clamped to lie between the minimum and maximum values
		supported (currently between 1/32 and 64). After adjusting the zoom, the document view
		center remains unchanged.
				@param view The view reference, or \c NULL for the current view.
				@param zoom The new zoom factor, a percentage value where
					1 is 100% (actual size), 0.5 is 50% and 2 is 200%.
		*/
	AIAPI AIErr (*SetDocumentViewZoom) ( AIDocumentViewHandle view, AIReal zoom );

	/** Converts a point from artwork coordinates to view (window) coordinates. The resulting
		view coordinate is rounded to the nearest pixel.
			@param view The view reference, or \c NULL for the current view.
			@param artworkPoint The point to convert, in artwork coordinates.
			@param viewPoint [out] A buffer in which to return the converted point, in window coordinates.
			@see \c #FixedArtworkPointToViewPoint() (does not round)
		*/
	AIAPI AIErr (*ArtworkPointToViewPoint) ( AIDocumentViewHandle view, const AIRealPoint *artworkPoint, AIPoint *viewPoint );

	/** Converts a point from view coordinates to artwork coordinates.
			@param view The view reference, or \c NULL for the current view.
			@param viewPoint The point to convert, in window pixel coordinates.
			@param artworkPoint [out] A buffer in which to return the converted point, in artboard coordinates.
			@see \c #FixedViewPointToArtworkPoint() (takes floating-point coordinate values)
		 */
	AIAPI AIErr (*ViewPointToArtworkPoint) ( AIDocumentViewHandle view, const AIPoint *viewPoint, AIRealPoint *artworkPoint );

	/** Gets the number of open views for the current document. Use with
		\c #GetNthDocumentView() to iterate through views.
			@param count [out] A buffer in which to return the number of views.
		*/
	AIAPI AIErr (*CountDocumentViews)( ai::int32 *count );

	/** Retrieves a document view for the current document by position index. Use with
		\c #CountDocumentViews() to iterate through views.
			@param n The index, in the range <code>[1..numViews]</code>, or 0 to get the current view.
			@param view [out] A buffer in which to return the view reference.
		*/
	AIAPI AIErr (*GetNthDocumentView)( ai::int32 n, AIDocumentViewHandle *view );

	/** Converts a point from artwork coordinates to view (window) coordinates. Does \e not round
		the result.
			@param view The view reference, or \c NULL for the current view.
		 	@param artworkPoint The point to convert, in artwork coordinates.
		 	@param viewPoint [out] A buffer in which to return the converted point, in window coordinates.
			@see \c #ArtworkPointToViewPoint() (rounds result to nearest pixel)
		*/
	AIAPI AIErr (*FixedArtworkPointToViewPoint) ( AIDocumentViewHandle view, const AIRealPoint *artworkPoint, AIRealPoint *viewPoint );

	/** Converts a point from view coordinates to artwork coordinates.
			@param view The view reference, or \c NULL for the current view.
			@param viewPoint The point to convert, in window floating-point coordinates.
			@param artworkPoint [out] A buffer in which to return the converted point, in artboard coordinates.
			@see \c #ViewPointToArtworkPoint() (takes pixel coordinate values)
		*/
	AIAPI AIErr (*FixedViewPointToArtworkPoint) ( AIDocumentViewHandle view, const AIRealPoint *viewPoint, AIRealPoint *artworkPoint );

	/** Sets the screen mode of a view. In the UI, the screen mode is
		selected with icons at the bottom of the Tool palette.
			 @param view The view reference, or \c NULL for the current view.
			 @param mode The new screen mode.
		*/
	AIAPI AIErr (*SetScreenMode) ( AIDocumentViewHandle view, AIScreenMode mode );

	/** Retrieves the screen mode of a view. In the UI, the screen mode is
		shown by icons at the bottom of the Tool palette.
			 @param view The view reference, or \c NULL for the current view.
			 @param mode [out] A buffer in which to return the screen mode.
		*/
	AIAPI AIErr (*GetScreenMode) ( AIDocumentViewHandle view, AIScreenMode *mode );

	/** Retrieves the page tiling information that describes how the artwork is printed
		onto one or more pages.
			 @param pageTiling [out] A buffer in which to return the tiling information.
		*/
	AIAPI AIErr (*GetPageTiling) ( AIPageTiling *pageTiling );

	/** Reports whether there is a visible template layer.
			 @param view The view reference, or \c NULL for the current view.
			 @param visible [out] A buffer in which to return true if the template layer is shown.
		*/
	AIAPI AIErr (*GetTemplateVisible) ( AIDocumentViewHandle view, AIBoolean *visible );

	/** Scrolls a document window.
			 @param view The view reference, or \c NULL for the current view.
			 @param delta The vector by which to scroll, a horizontal and vertical
			 	distance in points.
		*/
	AIAPI AIErr (*DocumentViewScrollDelta)( AIDocumentViewHandle view, AIRealPoint *delta);

	/** Retrieves a rectangle that encloses (at least) the portions of the viewed
		document that have been changed and so need to be redrawn. This rectangle is reset to
		be empty each time the \c #kAIDocumentViewInvalidRectChangedNotifier is sent.
			@param view The view reference, or \c NULL for the current view.
			@param invalidRect [out] A buffer in which to return the invalid area, in artwork coordinates.
		*/
	AIAPI AIErr (*GetDocumentViewInvalidRect)( AIDocumentViewHandle view, AIRealRect *invalidRect );

	/** Sets the invalid rectangle for a view. This is the area that encloses
		(at least) the portions of the viewed document that have been changed
		and so need to be redrawn in the given view.
			@param view The view reference, or \c NULL for the current view.
			@param invalidRect The new area, in artwork coordinates.
			@see \c #GetDocumentViewInvalidRect(), \c #SetDocumentViewInvalidDocumentRect()
		*/
	AIAPI AIErr (*SetDocumentViewInvalidRect)( AIDocumentViewHandle view, const AIRealRect *invalidRect );

	/** Retrieves the display mode for a view.
			@param view	The view reference, or \c NULL for the current view.
			@param style [out] A buffer in which to return the style, a logical OR of these bit flags:<br>
				\c #kVsArtwork, \c #kVsPreview, \c #kVsRaster, \c #kVsOpaque, \c #kVsInk
		*/
	AIAPI AIErr (*GetDocumentViewStyle)( AIDocumentViewHandle view,  ai::int16 *style );

	/** Sets the invalid rectangle for all views of a viewed document. This is the area
		that encloses (at least) the portions of the viewed document that have been
		changed and so need to be redrawn in all views of that document.
			@param view The view reference, or \c NULL for the current view.
			@param invalidRect The new area, in artwork coordinates.
			@see \c #SetDocumentViewInvalidRect()
		*/
	AIAPI AIErr (*SetDocumentViewInvalidDocumentRect)( AIDocumentViewHandle view, const AIRealRect *invalidRect );

	/** Reports whether page tiling is shown for the current view. Each view has its own setting.
			@param show [out] A buffer in which to return true if page tiling is shown.
		*/
	AIAPI AIErr (*GetShowPageTiling) ( AIBoolean *show );

	/** Sets the page tiling mode for the current view. Each view has its own setting.
			@param show True to turn page tiling on, false to turn it off.
		*/
	AIAPI AIErr (*SetShowPageTiling) ( AIBoolean show );

	/** Retrieves grid options for a view.
			@param view The view reference, or \c NULL for the current view.
			@param show [out] A buffer in which to return true if the grid is visible.
			@param snap [out] A buffer in which to return true if the snap-to-grid is on.
		*/
	AIAPI AIErr (*GetGridOptions) ( AIDocumentViewHandle view, AIBoolean* show, AIBoolean* snap );

	/**  Sets grid options for a view
			@param view The view reference, or \c NULL for the current view.
	 		@param show True to make the grid visible, false to hide it.
			@param snap True to turn snap-to-grid on, false to turn it off.
		*/
	AIAPI AIErr (*SetGridOptions) ( AIDocumentViewHandle view, AIBoolean show, AIBoolean snap );

	/** Reports whether the transparency grid is shown in a view.
			@param view The view reference, or \c NULL for the current view.
			@param show [out] A buffer in which to return true if the transparency grid is visible.
		*/
	AIAPI AIErr (*GetShowTransparencyGrid) ( AIDocumentViewHandle view, AIBoolean* show );

	/** Sets whether the transparency grid is shown in the view.
			@param view The view reference, or \c NULL for the current view.
	 		@param show True to make the transparency grid visible, false to hide it.
		*/
	AIAPI AIErr (*SetShowTransparencyGrid) ( AIDocumentViewHandle view, AIBoolean show );

	/** Retrieves the document displayed in a view.
			@param view The view reference, or \c NULL for the current view.
			@param document [out] A buffer in which to return the document reference.
		*/
	AIAPI AIErr (*GetDocumentViewDocument) ( AIDocumentViewHandle view, AIDocumentHandle *document );

	/** Forces all document views to not be obscured by the Control palette.
		*/
	AIAPI AIErr (*ForceDocumentViewsOnScreen) ( void );

	/** Retrieves the visibility state of the guides.
			@param view The view reference, or \c NULL for the current view.
			@param show [out] A buffer in which to return true if the guides are visible.
		*/
	AIAPI AIErr (*GetShowGuides) ( AIDocumentViewHandle view, AIBoolean* show );

	/** Sets the visibility state of the guides.
			@param view The view reference, or \c NULL for the current view.
	 		@param show True to make the guides visible, false to hide them.
		*/
	AIAPI AIErr (*SetShowGuides) ( AIDocumentViewHandle view, AIBoolean show );

 	/** Retrieves the visibility state of the edges of the selection.
 			@param view The view reference, or \c NULL for the current view.
 			@param show True to make the edges visible, false to hide them.
 		*/
 	AIAPI AIErr (*GetShowEdges) ( AIDocumentViewHandle view, AIBoolean* show );

 	/** Sets the visibility state of the edges of the selection.
 			@param view The view reference, or \c NULL for the current view.
 			@param show True to make the edges visible, false to hide them.
 		*/
 	AIAPI AIErr (*SetShowEdges) ( AIDocumentViewHandle view, AIBoolean show );

	/** Captures the contents of the view window (excluding scrollbars, etc.) to
		a TIFF file. Artboards are centered in window before capture.
 			@param view			The view reference, or \c NULL for the current view.
			@param saveFilename	Full path and name of TIFF file to create.
			@param windowSize	Size to set window before capture. Will restore
								original window size before returning.	
		*/
	AIAPI AIErr (*SaveImage) ( AIDocumentViewHandle view, const ai::UnicodeString &saveFilename, 
		const AIPoint &windowSize );

	/** Determines the current state of video rulers if they are visible or not.
			@param view			The view reference, or \c NULL for the current view.
			@param visible		True if the artboard rulers are visible, false otherwise.
		*/
	AIAPI AIErr (*IsArtboardRulerVisible) ( const AIDocumentViewHandle view, AIBoolean *visible );

	/** Sets the video rulers visibility on or off.
			@param view			The view reference, or \c NULL for the current view.
			@param visible		True if artboard ruler visibility is to be turned on, false otherwise.
		*/
	AIAPI AIErr (*SetArtboardRulerVisible) ( const AIDocumentViewHandle view, const AIBoolean visible );
	
	/** Returns the number plates in the plate set for the view.  The plate set is only relevant for OPP
		view mode.
			@param view					The view reference, or \c NULL for the current view.
			@param count [out]			The number of plates.
		*/
	AIAPI AIErr (*CountOPPPlates) ( AIDocumentViewHandle view, ai::int32& count );

	/** Get an identifier for the nth plate in the view's plate set.
			@param view					The view reference, or \c NULL for the current view.
			@param plate [out]			The plate identifier.
		*/
	AIAPI AIErr (*GetNthOPPPlate) ( AIDocumentViewHandle view, ai::int32 n, ai::ColorSpace& plate );

	/** Get the visibility state for \c plate in the current view's plate state.  Visibility is only
		recognized for OPP view mode.
			@param view					The view reference, or \c NULL for the current view.
			@param plate				Identifier for the plate to get the state of.
			@param isOn [out]			The current visibility state of \c plate.
		*/
	AIAPI AIErr (*GetOPPPlateState) ( AIDocumentViewHandle view, const ai::ColorSpace& plate, AIBoolean& isOn );

	/** Set the visibility state for \c plate in the current view's plate state.  Visibility is only
		recognized for OPP view mode.  Invalid \c plate identifiers are ignored.
			@param view					The view reference, or \c NULL for the current view.
			@param plate				Identifier for the plate to get the state of.
			@param isOn					The new visibility state of \c plate.
		*/
	AIAPI AIErr (*SetOPPPlateState) ( AIDocumentViewHandle view, const ai::ColorSpace& plate, const AIBoolean isOn );

	/** Sets the display mode for a view.  Currently these flags are mostly mutually exclusive. \c #kVsInk
		only makes sense combined with \c #kVsPreview. \c #kVsArtwork, \c #kVsPreview, and \c #kVsRaster are 
		mutually exclusive.
			@param view	The view reference, or \c NULL for the current view.
			@param style A logical OR of these bit flags:<br>
				\c #kVsArtwork, \c #kVsPreview, \c #kVsRaster, \c #kVsOpaque, \c #kVsInk
			@param mask A logical OR of the same bit values as style indicating which 
				bits from style to change.
		*/
	AIAPI AIErr (*SetDocumentViewStyle)( AIDocumentViewHandle view,  ai::int16 style, ai::int16 mask );

	/** Determines whether the rulers are shown in Artboard co-ordinates.
	@param view			The view reference, or \c NULL for the current view.
	@param isYes		True if the rulers are shown in Artboard co-ordinates, false otherwise.
	*/
	AIAPI AIErr (*IsRulerInArtboardCoordinates)( const AIDocumentViewHandle view, ASBoolean *isYes );

	/** Sets the rulers to use Artboard co-ordinates.
	@param view			The view reference, or \c NULL for the current view.
	@param state		True if the rulers are shown in Artboard co-ordinates, false otherwise.
	*/
	AIAPI AIErr (*UseArtboardCoordinatesInRuler) ( const AIDocumentViewHandle view, const ASBoolean state );
};


#include "AIHeaderEnd.h"


#endif
