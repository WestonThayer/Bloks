#ifndef __AI110ForeignObject__
#define __AI110ForeignObject__

/*
 *        Name:	AI110ForeignObject.h
 *     Purpose:
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2002-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

/*******************************************************************************/
// Imports

#ifndef __AIForeignObject__
#include "AIForeignObject.h"
#endif


#include "AIHeaderBegin.h"

/** @file AI110ForeignObject.h */

/*******************************************************************************/
//	Constants

#define kAI110ForeignObjectSuite		kAIForeignObjectSuite
#define kAIForeignObjectSuiteVersion1	AIAPI_VERSION(1)
#define kAI110ForeignObjectSuiteVersion	kAIForeignObjectSuiteVersion1


/*******************************************************************************/
// Suite


/**
	This suite exposes an API for the foreign object. The foreign object is a
	wrapper around imaging constructs supported by PDF and the Adobe Imaging Model
	but not natively in Illustrtor.

	Foreign objects behave like placed objects in that they can be positioned on
	the page, saved, displayed on the screen, and printed.  But they do not respond
	to other Illustrator editing commands. A foreign object may use global resources
	that are used by other artwork elements. For example it may use fonts or spot
	colors.
	
	Illustrator requires that all spot colors used in a document be installed into
	the swatch list. Each spot color must have a unique definition and spot colors
	used by foreign objects are locked against having their definition edited. The
	installation and locking of spot colors needs to be done once the foreign
	object has been created and is known to be a permanent result of an operation
	on the document	as opposed to a temporary object created during an operation.
	For this reason installation of spot colors is done when an editing operation
	is committed. When spot colors are installed their definitions may conflict
	with existing spot colors. If this is the case the user is prompted to resolve
	the conflict.

	See also the AIFOConversionSuite for APIs that expand foreign objects
	to native Illustrator artwork.
*/
typedef struct AI110ForeignObjectSuite {

	/** Create a new Foreign object. See AIArtSuite::NewArt() for the meanings
		of the paintOrder and prep parameters.  */
	AIAPI AIErr (*New) (short paintOrder, AIArtHandle prep, AIArtHandle *newArt);

	/** Test whether a given object is a foreign object */
	AIAPI AIBoolean (*Is) (AIArtHandle art);

	/** Get the bounds of the foreign object (before application of the matrix) */
	AIAPI AIErr (*GetBounds) ( AIArtHandle art, AIRealRect *bounds );

	/** Set the bounds of the foreign object (before application of the matrix) */
	AIAPI AIErr (*SetBounds) ( AIArtHandle art, AIRealRect *bounds );

	/** Get the transformation matrix of the foreign object. */
	AIAPI AIErr (*GetMatrix) (AIArtHandle art, AIRealMatrix *matrix);

	/** Set the transformation matrix of the foreign object. */
	AIAPI AIErr (*SetMatrix) (AIArtHandle art, AIRealMatrix *matrix);
	
	/** Get the foreign object's display port. The display port is an AGM port.
		After creating a foreign object a client will typically obtain the
		display port and draw into it. The drawing commands are recorded by
		the display port and are played back whenever the foreign object is
		rendered. One way to draw into the display port is to set it as the
		portV6 member of the AIDrawArtData structure and use the
		AIDrawArtSuite::DrawArt() API. Clients who have access to the AGM
		interface can also draw directly into the the display list or play it's
		contents to another AGM port. */
	AIAPI AIErr (*GetDisplayPort)(AIArtHandle art, AIDisplayPortHandle *port);

	/** No-op. */
	AIAPI AIErr (*InstallResources)(AIArtHandle art);
	
	/** This API is intended for use by the AIFOConversionSuite implementation
		of the #kAIFOConversionSuppressAttributes flag. It duplicates the input
		object stripping off any attributes that affect the rendering of the
		contents of the object other than the matrix. */
	AIAPI AIErr (*DuplicateForConversion)(AIArtHandle art, short paintOrder, AIArtHandle prep, AIArtHandle* newArt);

} AI110ForeignObjectSuite;


#include "AIHeaderEnd.h"


#endif
