#ifndef __AISLICING__
#define __AISLICING__

/*
 *        Name:	AISlicing.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator 10 Slicing Suite.
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

#ifndef __SLICETYPES__
#include "AISliceTypes.h"
#endif

#ifndef __AIDataFilter__
#include "AIDataFilter.h"
#endif

#ifndef __AIEntry__
#include "AIEntry.h"
#endif

#ifndef __AIPlatformMemory__
#include "AIPlatformMemory.h"
#endif

#ifndef __AIHTMLCONVERSION__
#include "AIHTMLConversion.h"
#endif

#ifndef AIFLASHPREFS_H
#include "AIFlashPrefs.h"
#endif

#ifndef _AISVGACTION_H_
#include "AISVGAction.h"
#endif

#ifndef __AIDict__
#include "AIDictionary.h"
#endif

#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAISlicingSuite							"AI Slicing Suite"
#define kAISlicingSuiteVersion1					AIAPI_VERSION(1)
#define kAISlicingSuiteVersion					kAISlicingSuiteVersion1

#define kAIOptimizationSettingsSuite			"AI Optimization Settings Suite"
#define kAIOptimizationSettingsSuiteVersion1	AIAPI_VERSION(1)
#define kAIOptimizationSettingsSuiteVersion		kAIOptimizationSettingsSuiteVersion1


#define kAISlicingChangedNotifier	"AI Slicing Changed"
#define kAISliceCommandsMenuGroup 	"AI Slice Commands Menu Group"


/*******************************************************************************
 **
 **	Types
 **
 **/

enum ASOptimizedFileFormat
{
	asffGIF89a,				// "GIF"
	asffJPEG,				// "JPEG"
	asffPNG8,				// "PNG8"
	asffPNG24,				// "PNG24"
	asffAuto,				// "auto
	asffInvalidFormat,		// ""
	asffMixedFormat,		// "mixed"
	asffSWF,				// "SWF"
	asffSVG					// "SVG"
};

enum ASDitherAlgorithm
{
	asdaNone,				// "none"
	asdaDiffusion,			// "diffusion"
	asdaPattern,			// "pattern"
	asdaWhiteNoise,			// "whiteNoise
	asdaBlueNoise			// "noise"
};

enum ASReductionAlgorithm
{
	asraAdaptive,			// "adaptive"
	asraSelective,			// "selective"
	asraPerceptual,			// "perceptual"
	asraMacintoshSystem,	// "macintoshSystem"
	asraWindowsSystem,		// "windowsSystem"
	asraWeb,				// "web"
	asraImageReadyCustom,	// "custom"
	asraFileBased,			// "fileBased"
	asraNeuralNet,			// "neuralNet"
	asraFauxPerceptual		// "fauxPerceptual"
};



typedef struct
{
	ADMRGBColor rangeStart;
	ADMRGBColor rangeEnd;
	ADMRGBColor remapColor;
}
ASColorShiftEntry;


typedef struct
{
	ASBoolean transparency;
	ASBoolean includeCaption;
	ASBoolean interlaced;

	ASBoolean noMatteColor;
	ADMRGBColor matteColor;

	ASBoolean autoReduced;
	ASBoolean rolloverMasterPalette;

	ASInt32 webShiftedPercentage;

	ASInt32 numberOfColors;

	ASInt32 qualitySetting;
	ASDitherAlgorithm ditherAlgorithm;
	ASInt32 ditherPercentage;
	ASReductionAlgorithm reductionAlgorithm;

	ASHandle reductionAlgorithmFilename;	// see allocation comments in ASSliceSettings definition
} ASGIFSettings;


typedef struct
{
	ASBoolean transparency;	// obsolete and ignored
	ASBoolean noMatteColor;
	ADMRGBColor matteColor;
	ASBoolean optimized;
	ASInt32 qualitySetting;
	ASBoolean multiplePasses;	// progressive
	AIReal blurAmount;
	ASBoolean embedICCProfile;
} ASJPEGSettings;


typedef struct
{
	ASBoolean transparency;
	ASBoolean includeCaption;		//	unused
	ASBoolean interlaced;
	ASBoolean noMatteColor;
	ADMRGBColor matteColor;

	ASBoolean autoReduced;
	ASBoolean rolloverMasterPalette;
	ASInt32 webShiftedPercentage;
	ASInt32 numberOfColors;

	ASDitherAlgorithm ditherAlgorithm;
	ASInt32 ditherPercentage;
	ASReductionAlgorithm reductionAlgorithm;

	ASHandle reductionAlgorithmFilename;	// see allocation comments in ASSliceSettings definition
} ASPNG8Settings;


typedef struct
{
	ASBoolean transparency;
	ASBoolean includeCaption;		//	unused
	ASBoolean interlaced;
	ASBoolean noMatteColor;
	ADMRGBColor matteColor;
	ASBoolean filtered;
} ASPNG24Settings;


typedef struct
{
 	AISVGFontSubsetting fontSubsetting;
 	AISVGFileLocation fontLocation;
 	AISVGRasterLocation imageLocation;
	ASBoolean obsolete;
 	AISVGFileCompression compression;
 	AISVGCoordinatePrecision precision;
 	AISVGDocumentEncoding  encoding;
 	AISVGStyle style;
} ASSVGSettings;


typedef struct
{
 	FlashExportOption exportOption;
 	AIReal frameRate;
 	ASBoolean loop;
 	ASBoolean readOnly;
 	ASInt32 curveQuality;
	ASBoolean preserveAppearance;
} ASSWFSettings;


typedef union
{
	ASGIFSettings	gif;
	ASJPEGSettings	jpeg;
	ASPNG8Settings	png8;
	ASPNG24Settings	png24;
	ASSVGSettings	svg;
	ASSWFSettings	swf;
} ASOptimizationSettingsUnion;

typedef struct ASOptimizationSettings
{
	ASOptimizedFileFormat 		fileFormat;
	ASOptimizationSettingsUnion	s;
} ASOptimizationSettings;


typedef struct
{
	ASInt32 groupID;
	ai::ESliceType type;
	ASBoolean cellTextIsHTML;
	ai::ESliceHorzAlign horzAlign;
	ai::ESliceVertAlign vertAlign;
	ai::ESliceBGColorType bgColorType;
	ADMRGBColor bgColor;

	// For Set calls, the handle must be allocated by the caller.
	// For Get calls, if a handle is non-NULL it will be used as provided;
	//     if a handle is NULL, it will be allocated by the slicing suite.
	// In either case, handles must be released when no longer needed **by the caller**.
	ASHandle hName;
	ASHandle hURL;
	ASHandle hTarget;
	ASHandle hMessage;
	ASHandle hAltTag;
	ASHandle hCellText;
} ASSliceSettings;


typedef void* AISavedSliceListRef;


/*******************************************************************************
 **
 **	Suite
 **
 **/

typedef struct {

	// if an ID is passed in it will be used if possible, the ID actually used is returned
	// fromPlace should be true if the function is used from a file format to create slices
	// if used from a menu, tool, etc., fromPlace should be false
	AIAPI AIErr (*MakeSlice)(AIArtHandle art, ASInt32 *sliceID, ASBoolean fromPlace);

	// creates a no fill/no stroke rect designated as a slice and selects if desired
	// if an ID is passed in it will be used if possible, the ID actually used is returned
	// fromPlace should be true if the function is used from a file format to create slices
	// if used from a menu, tool, etc., fromPlace should be false
	AIAPI AIErr (*CreateSlice)(AIArtHandle placeAboveArt, ASInt32 *sliceID, AIBoolean selected, ASBoolean fromPlace);

	// deletes the slice art and its slicing information
	AIAPI AIErr (*DeleteSlice)(ASInt32 sliceID);

	// removes the slicing designation from the art, but does not delete the art
	AIAPI AIErr (*Unslice)(AIArtHandle art);

	// get the slice ID of an art object, returns kInvalidSliceID if not a slice
	AIAPI ASInt32 (*GetArtSliceID)(AIArtHandle art);

	// get the art of a slice ID, returns NULL if not a slice
	AIAPI AIArtHandle (*GetSliceArt)(ASInt32 sliceID);

	AIAPI ASInt32 (*GetUniqueSliceID)(void);
	AIAPI AIBoolean (*SliceExists)(ASInt32 sliceID);

	// Get the number of slices in the slice list
	AIAPI ASInt32 (*GetSliceCount)(void);

	// Get the slice ID of the nth slice
	AIAPI ASInt32 (*GetIndexedSliceID)(ASInt32 index);

	// Set works on no fill/no stroke slices objects but will not transform art otherwise
	// Get returns the bounds to be used for the slice including the border
	AIAPI AIErr (*SetSliceBounds)(ASInt32 sliceID, AIRealRect *boundsRect);
	AIAPI AIErr (*GetSliceBounds)(ASInt32 sliceID, AIRealRect *boundsRect);

	// The slice border is the appended to the art visual bounds to generate the slice bounds
	AIAPI AIErr (*SetSliceBorder)(ASInt32 sliceID, AIRealRect *borderRect);
	AIAPI AIErr (*GetSliceBorder)(ASInt32 sliceID, AIRealRect *borderRect);

	// Get/set the standard slice information
	AIAPI AIErr (*SetSliceSettings)(ASInt32 sliceID, ASSliceSettings *settings);
	AIAPI AIErr (*GetSliceSettings)(ASInt32 sliceID, ASSliceSettings *settings);

	// Get/set a single slice attribute
	AIAPI AIErr (*SetSliceSetting)(ASInt32 sliceID, const AIDictKey &key, AIEntryRef valueEntry);
	AIAPI AIErr (*GetSliceSetting)(ASInt32 sliceID, const AIDictKey &key, AIEntryRef *valueEntry);

	// Is the slice somehow convertible to text
	AIAPI AIBoolean (*SliceIsText)(ASInt32 sliceID);

	// Mark that it should be converted on output
	AIAPI AIErr (*SetSliceIsHTMLText)(ASInt32 sliceID, long HTMLTextOptions);

	// Is the slice to be converted on output
	AIAPI AIBoolean (*GetSliceIsHTMLText)(ASInt32 sliceID, long *HTMLTextOptions);

	// Convert the slice to text.  The call allocates and frees the handle, though
	// it may be resized using the AIPlatformMemorySuite.
	// Options are defined in the "AIHTMLConversion.h" file (and elsewhere?)
	AIAPI AIErr (*GetSliceAsHTMLText)(ASInt32 sliceID, long options, ASHandle *text);

	// See if the slice is on a given layer
	AIAPI AIBoolean (*SliceIsOnLayer)(ASInt32 sliceID, AILayerHandle layer);

	// Temporarily replaces the slice list with an empty slice list and the optimizations
	// list with just the settins of the given slice group ID.
	// Returns an opaque references to the current full lists, which must be restored.
	AIAPI AIErr (*ReplaceSliceList)(ASInt32 groupID, AISavedSliceListRef *oldSliceList);
	AIAPI AIErr (*RestoreSliceList)(AISavedSliceListRef oldSliceList);

	AIAPI AIBoolean (*SliceIsSelected)(ASInt32 sliceID);
	AIAPI AIErr (*GetSelectedSliceList)(ASInt32 **sliceIDList, ASInt32 *count);
	AIAPI AIErr (*ReleaseSelectedSliceList)(ASInt32 *sliceIDList);
	
} AI100SlicingSuite;


typedef struct
{
	AIAPI ASInt32 (*GetOptimizationSettingsCount)(void);

	AIAPI ASInt32 (*GetIndexedOptimizationSettingsID)(ASInt32 index);

	AIAPI void (*DeleteOptimizationSettings)(ASInt32 optimizationID);

	AIAPI ASInt32 (*GetUniqueOptimizationSettingsID)(void);
	AIAPI AIBoolean (*OptimizationSettingsExists)(ASInt32 optimizationID);

	// Get/set the optimization settings for a settings group
	AIAPI AIErr (*SetOptimizationSettings)(ASInt32 optimizationID, ASOptimizationSettings *settings);
	AIAPI AIErr (*GetOptimizationSettings)(ASInt32 optimizationID, ASOptimizationSettings *settings);

	AIAPI AIErr (*SetOptimizationSetting)(ASInt32 optimizationID, const AIDictKey&key, AIEntryRef valueEntry);
	AIAPI AIErr (*GetOptimizationSetting)(ASInt32 optimizationID, const AIDictKey&key, AIEntryRef *valueEntry);

	// These functions must be used by a file format plug-in to attach settings directly to a sliced art
	// object during a file place operation when the main optimization settings database is unavailable.
	// After the place command, optimization settings attached to an object will be inserted into
	// the main database.
	AIAPI AIErr (*SetSliceOptimizationID)(ASInt32 sliceID, ASInt32 optimizationID);
	AIAPI AIErr (*SetSliceOptimizationSettings)(ASInt32 sliceID, ASOptimizationSettings *settings);
	// You can use theis last function to suplement optimization information once it has been created
	// with the above function.
	AIAPI AIErr (*SetSliceOptimizationSetting)(ASInt32 sliceID, const AIDictKey&key, AIEntryRef valueEntry);


	//*** Important, for the GetColorTable-like functions, make a first call with the numColors/Entries initialized
	// but pass NULL for the ADMRGBColor/ASColorShiftEntry array.  This will return the number of entries in the
	// array.  Initialize it accordingly and call the funciton again with a point to the allocated memory.

	// the color table must ALWAYS be intialized to 256 ADMRGBColors
	AIAPI AIErr (*GetColorTable)(ASInt32 optimizationID, ASInt32* numColors, ADMRGBColor* colors, ASBoolean* exact);
	AIAPI AIErr (*SetColorTable)(ASInt32 optimizationID, ASInt32 numColors, ADMRGBColor* colors, ASBoolean exact);

	// the color table must ALWAYS be intialized to 256 ADMRGBColors
	AIAPI AIErr (*GetLockedColors)(ASInt32 optimizationID, ASInt32* numColors, ADMRGBColor* colors);
	AIAPI AIErr (*SetLockedColors)(ASInt32 optimizationID, ASInt32 numColors, ADMRGBColor* colors);
	AIAPI AIErr (*GetColorShiftEntries)(ASInt32 optimizationID, ASInt32* numEntries, ASColorShiftEntry *entries);
	AIAPI AIErr (*SetColorShiftEntries)(ASInt32 optimizationID, ASInt32 numEntries, ASColorShiftEntry *entries);

} AIOptimizationSettingsSuite;


#include "AIHeaderEnd.h"


#endif