#ifndef __AI192Geometry__
#define __AI192Geometry__

/*
 *        Name:	AI192Geometry.h
 *     Purpose:	Adobe Illustrator 19.2 Geometry Suite.
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

#include "AIGeometry.h"


#include "AIHeaderBegin.h"

/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAI192GeometrySuite			kAIGeometrySuite
#define kAIGeometryVersion5			AIAPI_VERSION(5)
#define kAI192GeometrySuiteVersion	kAIGeometryVersion5



/*******************************************************************************
 **
 **	Suite
 **
 **/

typedef struct {

	ASAPI AIErr(*GeometryIterate) (AIArtHandle art,
		AIGeometryOrganizationProcs *organizationProcs,
		AIGeometryConstructionProcs *constructionProcs,
		AIGeometryPaintingProcs *paintingProcs,
		AIGeometryStateProcs *stateProcs,
		AIGeometryUserData userData);

} AI192GeometrySuite;


#include "AIHeaderEnd.h"


#endif
