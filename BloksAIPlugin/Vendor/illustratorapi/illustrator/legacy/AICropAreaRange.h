/*************************************************************************
*
*ADOBE SYSTEMS INCORPORATED
* Copyright 2007 Adobe Systems Incorporated
* All Rights Reserved.
*
*NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the 
*terms of the Adobe license agreement accompanying it.  If you have received this file from a 
*source other than Adobe, then your use, modification, or distribution of it requires the prior 
*written permission of Adobe.
*
**************************************************************************/

#ifndef _AI_CROP_AREA_RANGE_H_
#define _AI_CROP_AREA_RANGE_H_

/*******************************************************************************
**
**	Imports
**
**/
#include "ASTypes.h"
#include "AIPlugin.h"
#include "AIArtboardRange.h"

#include "AIHeaderBegin.h"

#define kAICropAreaRangeSuite			"AI Crop Area Range Suite"
#define kAICropAreaRangeSuiteVersion1		AIAPI_VERSION(1)

/* Latest version */
#define kAICropAreaRangeSuiteVersion		kAICropAreaRangeSuiteVersion1
#define kAICropAreaRangeVersion			kAICropAreaRangeSuiteVersion


/** @file AICropAreaRange.h */
/** @ingroup Suites
This legacy suite allows you to validate and iterate over a crop area range string for Illustrator documents.

DEPRECATED: Don't use this suite in new code. Replacement is AIArtboardRangeSuite.

\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
\c #kAICropAreaRangeSuite and \c #kAICropAreaRangeSuiteVersion.
*/

typedef AIArtboardRangeHandle AICropAreaRangeHandle;
typedef AIArtboardRangeIterator AICropAreaRangeIterator;

typedef AIArtboardRangeSuite AICropAreaRangeSuite;

#include "AIHeaderEnd.h"

#endif // _AI_CROP_AREA_RANGE_H_