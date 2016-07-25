#ifndef _AI_CROP_AREA_H_
#define _AI_CROP_AREA_H_

/*
 *       Name: AICropArea.h
 *  $Revision: 1 $
 *     Author: Dimcho Balev
 *       Date: June, 2006
 *    Purpose: Adobe Illustrator Crop Area Suite
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2006-2007 Adobe Systems Incorporated.
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

#include "ASTypes.h"
#include "AIPlugin.h"

#include "AIHeaderBegin.h"

#define kAICropAreaSuite			"AI Crop Area Suite"
#define kAICropAreaSuiteVersion2		AIAPI_VERSION(2)

/* Latest version */
#define kAICropAreaSuiteVersion		kAICropAreaSuiteVersion2
#define kAICropAreaVersion			kAICropAreaSuiteVersion


/** @file AICropArea.h */

/*******************************************************************************
**
**	Constants
**
**/
#define kAIMAX_CROPAREA_LIMIT				100
#define kAIExceededMaxCropAreaLimitErr		'EMxL'
#define kAICantDeleteLastCropAreaErr		'CDLC'

/** Properties of a crop area. See \c #kAICropAreaSuite */
struct AICropArea
{
	/** The size of the crop area in points in document coordinate system */
	AIRealRect	m_CropAreaRect;
	/** Pixel aspect ratio, used in ruler visualization if the units are pixels */
	AIReal		m_fPAR;
	/** Show center mark */
	AIBoolean	m_bShowCenter;
	/** Show cross hairs */
	AIBoolean	m_bShowCrossHairs;
	/** Show title and action safe areas (for video) */
	AIBoolean	m_bShowSafeAreas;
	
	AICropArea()
	{
		m_fPAR = 1.0f;
		m_bShowCenter = false;
		m_bShowCrossHairs = false;
		m_bShowSafeAreas = false;
	}
};
/** This structure defines a crop area in a document. See \c #kAICropAreaSuite */
typedef AICropArea *AICropAreaPtr;

enum Source{
	kSetActive,
	kUpdate,
	kUndoRedo
};

typedef struct
{
	Source msgSrc;
} AIArtboardMessage;

/*******************************************************************************
 **
 **	Suite
 **
 **/


/** @ingroup Suites
	This suite allows you to activate, access, and modify crop areas in Illustrator documents.
	Illustrator maintains a list of crop areas in a document, and these functions allow
	you to iterate through the list. The active crop area is the one returned by
	\c #AIDocumentSuite::GetDocumentCropBox(), which is displayed with crop marks,
	and which is used when saving or exporting to a file.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAICropAreaSuite and \c #kAICropAreaSuiteVersion.
*/

typedef struct 
{

	/** Retrieves the index position of the active crop area in the document's list.
			@note In some cases this function can mark the document as changed and in need of saving.
			@param index [out] A buffer in which to return the 0-based index, or
				-1 if there are no crop areas in the current document.
		*/
	AIAPI AIErr (* GetActive ) (ASInt32 *index);

	/** Makes a specific crop area active, and makes it current in the iteration order.
		See \c #Next(), and \c #Previous().
			@param index The 0-based index position of the crop area in the document list.
		*/
	AIAPI AIErr (* SetActive ) (ASInt32 index);

	/** Retrieves the properties of a crop area	 Use with \c #GetCount() and \c #Update()
		to modify crop areas without changing which crop area is active in the document.
			@param index The 0-based index position of the crop area in the document list.
			@param properties [out]	A buffer in which to return	the crop-area properties.
		*/
	AIAPI AIErr (* Get ) (ASInt32 index, AICropAreaPtr *properties);

	/** Finds the next crop area in the list after the currently active area, makes it
		active, and retrieves its properties.
		The list is circular; that is, the next one after the last crop area
		is the first one in the list.
			@param properties [out]	A buffer in which to return	the crop-area properties, or
				\c NULL if there are no crop areas in the current document.
		*/
	AIAPI AIErr (* Next ) (AICropAreaPtr *properties);

	/** Finds the previous crop area in the list before the currently active area, makes it
		active, and retrieves its properties.
		The list is circular; that is, the previous one before the first crop area
		is the last one in the list.
			@param properties [out]	A buffer in which to return	the crop-area properties, or
				\c NULL if there are no crop areas in the current document.
		*/
	AIAPI AIErr (* Previous ) (AICropAreaPtr *properties);

	/** Retrieves the number of crop areas defined in the current document.
			@param count [out] A buffer in which to return the number of crop areas.
		*/
	AIAPI AIErr (* GetCount ) (ASInt32 *count);

	/** Deletes a crop area from the document list, makes the next one in the list active,
		and retrieves the properties of the newly active area.
		Last crop area can not be deleted, throws error kAICantDeleteLastCropAreaErr in such case.
			@param index The 0-based index position of the crop area to delete.
			@param properties [out]	 A buffer in which to return the crop-area properties of the
				newly active area, or \c NULL if there are no remaining crop areas in the current document.
		*/
	AIAPI AIErr (* Delete ) (int index, AICropAreaPtr *properties);

	/** Not Implemented returns kNotImplementedErr*/
	AIAPI AIErr (* DeleteAll ) ();

	/** Adds new crop area to the document and returns its index position in the crop-area list.
	    Maximum limit MAX_CROPAREA_LIMIT,throws error kAIExceededMaxCropAreaLimitErr after this limit.
			@param properties The new crop area.
			@param index [out] A buffer in which to return the 0-based index position of the new crop area.
		*/
	AIAPI AIErr (* AddNew ) (AICropAreaPtr properties, ASInt32 *index);

	/** Updates the properties of a crop area. Use with \c #GetCount() and \c #Get()
		to modify crop areas without changing which crop area is active in the document.
			@param index The 0-based index position of the crop area in the document list.
			@param properties The new crop-area definition.
		*/
	AIAPI AIErr (* Update ) (ASInt32 index, AICropAreaPtr properties);

} AICropAreaSuite;

#include "AIHeaderEnd.h"

#endif // _AI_CROP_AREA_H_
