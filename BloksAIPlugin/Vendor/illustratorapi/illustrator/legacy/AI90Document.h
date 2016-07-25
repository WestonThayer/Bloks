#ifndef __AI90Document__
#define __AI90Document__

/*
 *        Name:	AI90Document.h
 *   $Revision: 25 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 9.0 Document Suite.
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

#include "AI120Document.h"

#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI90DocumentSuite				kAIDocumentSuite
#define kAIDocumentSuiteVersion6		AIAPI_VERSION(6)
#define kAI90DocumentSuiteVersion		kAIDocumentSuiteVersion6

/*******************************************************************************
 **
 **	Suite
 **
 **/


typedef struct {

	AIAPI AIErr (*GetDocumentPageOrigin) ( AIRealPoint *origin );
	AIAPI AIErr (*SetDocumentPageOrigin) ( AIRealPoint *origin );
	AIAPI AIErr (*SetDocumentRulerOrigin) ( AIRealPoint *origin );
	AIAPI AIErr (*GetDocumentRulerUnits) ( short *units );
	AIAPI AIErr (*SetDocumentRulerUnits) ( short units );
	AIAPI AIErr (*GetDocumentCropBoxGroupHandle) ( AIArtHandle *cropHandle );
	AIAPI AIErr (*GetDocumentCropBox) ( AIRealRect *cropBox );
	AIAPI AIErr (*SetDocumentCropBox) ( AIRealRect *cropBox );
	AIAPI AIErr (*GetDocumentCropStyle) ( AICropMarkStyle *cropStyle );
	AIAPI AIErr (*SetDocumentCropStyle) ( AICropMarkStyle cropStyle );
	AIAPI AIErr (*GetDocumentPrintRecord) ( AIDocumentPlatformPrintRecord *print );
	AIAPI AIErr (*SetDocumentPrintRecord) ( AIDocumentPlatformPrintRecord print );
	AIAPI AIErr (*GetDocumentSetup) ( AI120DocumentSetup *setup );
	AIAPI AIErr (*SetDocumentSetup) ( AI120DocumentSetup *setup );
	AIAPI AIErr (*GetDocumentModified) ( AIBoolean *modified );
	AIAPI AIErr (*SetDocumentModified) ( AIBoolean modified );
	AIAPI AIErr (*GetDocumentFileFormat) ( AIFileFormatHandle *fileFormat );
	AIAPI AIErr (*SetDocumentFileFormat) ( AIFileFormatHandle fileFormat );
	AIAPI AIErr (*GetDocumentFileFormatParameters) ( AIDocumentFileFormatParameters *parameters );
	AIAPI AIErr (*SetDocumentFileFormatParameters) ( AIDocumentFileFormatParameters parameters );

	AIAPI AIErr (*RedrawDocument) ( void );

	AIAPI AIErr (*GetDocument) ( AIDocumentHandle *document );
	

	AIAPI AIErr (*GetDocumentMiPrintRecord) ( AIDocumentMiPrintRecordPtr print );
	AIAPI AIErr (*SetDocumentMiPrintRecord) ( AIDocumentMiPrintRecordPtr print );

	AIAPI AIErr (*GetDocumentRulerOrigin) ( AIRealPoint *origin );
	
	AIAPI AIErr (*UpdateLinks) ( AIBoolean *updatedSomething );

	AIAPI AIErr (*GetDocumentZoomLimit) ( AIReal *min, AIReal *max );
	AIAPI AIErr (*GetDocumentMaxArtboardBounds)( AIRealRect *bounds );
	AIAPI AIErr (*DocumentExists) ( AIDocumentHandle document, AIBoolean *exists );

	/* Returns the recorded dictionary associated with the document. Note that dictionaries
		are reference counted. You must call sAIDictionary->Release() when you're
		done with it. */
	AIAPI AIErr (*GetDictionary) ( struct _AIDictionary** dictionary );
	AIAPI AIErr (*GetDocumentColorModel) ( short *colorModel);
	AIAPI AIErr (*SetDocumentColorModel) ( short colorModel);
	AIAPI AIErr (*GetDocumentProfiles) ( AIColorProfile *rgbProfile, AIColorProfile *cmykProfile, AIColorProfile *grayProfile );
	AIAPI AIErr (*SetDocumentProfiles) ( AIColorProfile rgbProfile, AIColorProfile cmykProfile, AIColorProfile grayProfile );
	AIAPI AIErr (*Copy)		();
	AIAPI AIErr (*Cut)		();
	AIAPI AIErr (*Paste)	();
	
	AIAPI AIErr (*SyncDocument) ( void );
	
	AIAPI AIErr (*GetDocumentTargeting) ( short *paintTarget, short *transparencyTarget, short *effectsTarget );
	AIAPI AIErr (*SetDocumentTargeting) ( short paintTarget, short transparencyTarget, short effectsTarget );

	/* Returns the dictionary associated with the document for which changes to the
		dictionary and its contents will not be recorded for undo/redo purposes. You
		must call sAIDictionary->Release() when you're done with it.*/
	AIAPI AIErr (*GetNonRecordedDictionary) ( struct _AIDictionary** dictionary );
	
	// Returns AI version of the current document.  If unknown, or not an AI file, returns 0.  
	// Version 2 is Illustrator 88.
	AIAPI int (*GetAIVersion) ();

	AIAPI AIErr (*DocumentHasTransparency) ( AIBoolean *hasTransparency, AIBoolean detectOverprint );
	AIAPI AIErr (*DocumentHasSpotColorArt) ( AIBoolean *hasSpotColorArt );

} AI90DocumentSuite;



#include "AIHeaderEnd.h"


#endif
