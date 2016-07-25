#ifndef __AI140HardSoft__
#define __AI140HardSoft__

/*
 *        Name:	AIHardSoft.h
 *   $Revision: 3 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Hard/Soft Suite.
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


#include "AIHeaderBegin.h"

/** @file AIHardSoft.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAIHardSoftSuite			"AI Hard Soft Suite"
#define kAIHardSoftSuiteVersion2	AIAPI_VERSION(2)


/*******************************************************************************
 **
 **	Types
 **
 **/


/*******************************************************************************
 **
 **	Suite
 **
 **/

/** @ingroup Suites
	This suite provides functions for converting between different coordinate
	systems used at different levels of Illustrator.

	The geometry of an object is described by coordinates that are relative to
	a pair of imaginary axes imposed on the artboard. Illustrator uses two ways of
	placing these axes, one for storing coordinate information internally and
	another for passing coordinate information across the SDK functions.

	\li In the internal coordinate system, the origin is the top left corner of the
	artboard--that is, of the white area that can be seen when zoomed out as far as
	possible. The X axis is horizontal, with the values increasing to the right.
	The Y axis is vertical, with values increasing downward. Values in this
	system are called \e hard, or \e artboard coordinates.

	\li In the public coordinate system, the origin is the \e ruler origin--that is,
	the point that corresponds to the 0 marks on the ruler when it is visible.
	By default, it is the bottom left corner of the page, but it can be changed by the
	user. The X axis is horizontal, with the values increasing to the right.
	The Y axis is vertical, with values increasing upward. Values in this system
	are called \e soft, or \e page coordinates.

	Most functions in the SDK use the public system of page coordinates, but
	some use the internal artboard coordinates. This suite provides functions
	for mapping between the coordinate systems.	For example, if you pass
	the origin point, [0,0], to \c #AIRealPointHarden(), the function returns the
	vector from the artboard origin (the top left of the canvas) to the page	origin
	(the bottom left of the visible page).

	@note These matrix conversion functions do not convert all
	components of translation matrices. To do this, you must understand
	the details of the two coordinate systems involved and use linear algebra.
	You must analyzed each case. For example, the matrix stored
	in an \c #AIPatternStyle maps coordinates from pattern space to internal
	artboard space, whereas the matrix for an image maps from image space to
	public page space.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIHardSoftSuite and \c #kAIHardSoftVersion.
*/
typedef struct {		// AI 8.0

	/** Converts a point in public page coordinates to a point in internal
		artboard coordinates.
			@param srcpoint A pointer to the point in public page coordinates.
			@param dstpoint	[out] A buffer in which to return the point in internal
				artboard coordinates.
	 */
	AIAPI AIErr (*AIRealPointHarden) ( AIRealPoint* srcpoint, AIRealPoint* dstpoint );

	/** Converts a point in internal artboard coordinates to a point in public
		page coordinates.
			@param srcpoint A pointer to the point in internal artboard coordinates.
			@param dstpoint	[out] A buffer in which to return the point in public
				page coordinates.
	 */
	AIAPI AIErr (*AIRealPointSoften) ( AIRealPoint* srcpoint, AIRealPoint* dstpoint );

	/** Applies \c #AIRealPointHarden() to the translation
		component of a matrix. This can be used to re-harden a returned
		matrix that has been incorrectly softened.
			@param matrix [in, out] The translation matrix, which is modified in place.
	*/
	AIAPI AIErr (*AIRealMatrixHarden) ( AIRealMatrix* matrix );

	/** Applies \c #AIRealPointSoften() to the translation
		component of a matrix. This can be used to pre-soften a matrix being passed
		into a function that will apply incorrect hardening.
			@param matrix [in, out] The translation matrix, which is
				modified in place.
		*/
	AIAPI AIErr (*AIRealMatrixSoften) ( AIRealMatrix* matrix );

	/** Applies \c #AIRealPointHarden() to the translation component
		of a matrix, then negates the \c b and \c c components.
			@param matrix [in, out] The translation matrix, which is
				modified in place.
	 */
	AIAPI AIErr (*AIRealMatrixRealHard) ( AIRealMatrix* matrix );

	/** Applies \c #AIRealPointSoften() to the translation component
		of a matrix, then negates the \c b and \c c components.
			@param matrix [in, out] The translation matrix, which is
				modified in place.
	*/
	AIAPI AIErr (*AIRealMatrixRealSoft) ( AIRealMatrix* matrix );

} AI140HardSoftSuite;


#include "AIHeaderEnd.h"


#endif
