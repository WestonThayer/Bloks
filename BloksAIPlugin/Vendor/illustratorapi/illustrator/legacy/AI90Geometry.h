#ifndef __AI90Geometry__
#define __AI90Geometry__

/*
 *        Name:	AI90Geometry.h
 *     Purpose:	Adobe Illustrator 9.0 Geometry Suite.
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

#define kAI90GeometrySuite			kAIGeometrySuite
#define kAIGeometryVersion2			AIAPI_VERSION(2)
#define kAI90GeometrySuiteVersion	kAIGeometryVersion2



/*******************************************************************************
 **
 **	Types
 **
 **/


typedef struct {

	AIGeometryBeginProc beginPath;
	AIGeometryEndProc endPath;
	AIGeometryBeginProc beginGroup;
	AIGeometryEndProc endGroup;
	AIGeometryBeginProc beginCompoundPath;
	AIGeometryEndProc endCompoundPath;
	AIGeometryBeginProc beginPlacedImage;
	AIGeometryEndProc endPlacedImage;
	AIGeometryBeginProc beginRaster;
	AIGeometryEndProc endRaster;
	AIGeometryBeginProc beginText;
	AIGeometryEndProc endText;
	AIGeometryBeginProc beginTextPath;
	AIGeometryEndProc endTextPath;
	AIGeometryBeginProc beginTextLine;
	AIGeometryEndProc endTextLine;
	AIGeometryBeginProc beginClipGroup;
	AIGeometryEndProc endClipGroup;
	AIGeometryBeginProc beginMask;
	AIGeometryEndProc endMask;
	AIGeometryBeginProc beginMesh;
	AIGeometryEndProc endMesh;

} AI90GeometryOrganizationProcs;


/*******************************************************************************
 **
 **	Suite
 **
 **/

typedef struct {

	ASAPI AIErr (*GeometryIterate) ( AIArtHandle art, 
									 AI90GeometryOrganizationProcs *organizationProcs, 
									 AIGeometryConstructionProcs *constructionProcs, 
									 AIGeometryPaintingProcs *paintingProcs, 
									 AIGeometryStateProcs *stateProcs, 
									 AIGeometryUserData userData );

} AI90GeometrySuite;


#include "AIHeaderEnd.h"


#endif
