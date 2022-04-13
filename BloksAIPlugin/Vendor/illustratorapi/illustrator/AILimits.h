/*************************************************************************
* ADOBE CONFIDENTIAL
* 
* Copyright 2017 Adobe
* All Rights Reserved.
* 
* NOTICE: Adobe permits you to use, modify, and distribute this file in
* accordance with the terms of the Adobe license agreement accompanying
* it. If you have received this file from a source other than Adobe,
* then your use, modification, or distribution of it requires the prior
* written permission of Adobe.
**************************************************************************/

#pragma once


#define kAILimitsSuite					"AI Limits Suite"
#define kAILimitsSuiteVersion			AIAPI_VERSION(2)  
#define kAILimitsVersion				kAILimitsSuiteVersion

#include <limits>

#include "AITypes.h"

namespace ai
{
	constexpr auto kInfinity = std::numeric_limits<AIReal>::infinity();

	// Use following constants for initializing "bounds" which will contain a union of bounds.
	// kNullUnionBoundsSoft has max limits considering axis +Y going in bottom
	// kNullUnionBoundsHard has max limits considering axis +Y going in top (+X going in left in both of above)
	//												{	LEFT,		TOP,		RIGHT,		  BOTTOM   };
	constexpr AIRealRect kNullUnionBoundsHard{ kInfinity , kInfinity  , -kInfinity , -kInfinity };
	constexpr AIRealRect kNullUnionBoundsSoft{ kInfinity , -kInfinity , -kInfinity ,  kInfinity };

}

#include "AIHeaderBegin.h"
/*******************************************************************************
**
**	Suite
**
**/

/**	@ingroup Suites
This suite provides utilities that allow you to get the Limits .

\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
\c #kAILimitsSuite and \c #kAILimitsSuiteVersion.

*/
enum class AIDecimalPrecisionType : ai::uint16
{
	kValue = 0,		// precision for general value inputs like color, opacity etc
	kDimension,		// precision for dimensions like length, height etc
	kType,		    // for values related to text
	kScale,			// for scaling factors
	kArtboardSize,	// for artboard dimensions
	kPercentage,	// for percentage values
	kColor,			// precision for color values
	kAngle,			// for angle values
    kResolution,     // for resolution values
	kStroke	//Precision for stroke dimension
};

struct AILimitsSuite
{
	/** Retrieves the size of the canvas. 
	(Note that this function returns a constant value, not an error code.)
	@return The canvas size (assuming square canvas)
	*/
	AIAPI ai::int32(*GetCanvasSize)();

	/**
	 * Returns the default large canvas scaling, compared to the regular canvas size.
		(Note that this function returns a constant value, not an error code.)
	 */
	AIAPI AIReal(*GetLargeCanvasScale)();

	AIAPI ai::int32(*GetDecimalPrecision)(AIDecimalPrecisionType type);
    AIAPI AIReal(*GetMinTransformDimensionValue)();
};

#include "AIHeaderEnd.h"







