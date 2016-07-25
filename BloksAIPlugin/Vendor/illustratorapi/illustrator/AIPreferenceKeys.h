#ifndef __AIPreferenceKeys__
#define __AIPreferenceKeys__

/*
 *        Name:	AIPreferenceKeys.h
 *     Purpose:	To define shared preference keys, defaults, and other
 *              relevant information.
 *       Notes: When sharing preferences between plugins and the main app,
 *              either a) use a null prefix, or b) access the preferences from
 *              the main app via the AIPreference suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2001-2014 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

/** Preference prefix: Use low-resolution proxy for linked EPS files  */
#define kUseLowResProxyPrefix nullptr
/** Preference suffix: Use low-resolution proxy for linked EPS files  */
#define kUseLowResProxySuffix ((const char *)"useLowResProxy")
/** Preference default: Use low-resolution proxy for linked EPS files  */
const bool kUseLowResProxyDefault= false;


/** Preference prefix: Display Bitmaps as Anti-Aliased images in Pixel Preview  */
#define kDisplayBitmapsAsAntiAliasedPixelPreviewPrefix nullptr
/** Preference suffix: Display Bitmaps as Anti-Aliased images in Pixel Preview  */
#define kDisplayBitmapsAsAntiAliasedPixelPreviewSuffix ((const char *)"DisplayBitmapsAsAntiAliasedPixelPreview")
/** Preference default: Display Bitmaps as Anti-Aliased images in Pixel Preview  */
const bool kDisplayBitmapsAsAntiAliasedPixelPreviewDefault= false;



/** Preference prefix: EPS rasterization resolution for linked EPS/DCS files */
#define kEPSResolutionPrefix nullptr
/** Preference suffix: EPS rasterization resolution for linked EPS/DCS files */
#define kEPSResolutionSuffix	((const char *)"EPSResolution")
/** Preference default: EPS rasterization resolution for linked EPS/DCS files */
const ai::int32 kEPSResolutionDefault = 300;

/** Preference prefix: Update linked file options */
#define kFileClipboardPrefix ((const char *)"FileClipboard")
/** Preference suffix: Update linked file options */
#define kLinkOptionsSuffix ((const char *)"linkoptions")
/** Preference options: Update linked file options */
enum UpdateLinkOptions {AUTO, MANUAL, ASKWHENMODIFIED};
/** Preference default: Update linked file options */
const UpdateLinkOptions kLinkOptionsDefault= ASKWHENMODIFIED;

/** Preference prefix: Enable OPI feature for linked EPS files */
#define kEnableOPIPrefix nullptr
/** Preference suffix: Enable OPI feature for linked EPS files */
#define kEnableOPISuffix	((const char *)"enableOPI")
/** Preference default: Enable OPI feature for linked EPS files */
const bool kEnableOPIDefault = false;

/** Preference suffix: Clipboard, copy SVG code*/
#define kcopySVGCodeSuffix		"copySVGCode"
/** Preference suffix: Clipboard, copy SVG code*/
#define kcopySVGCBFormatSuffix		"copySVGCBFormat"
/** Preference suffix: Clipboard, copy as PDF*/
#define kcopyAsPDFSuffix		"copyAsPDF"
/** Preference suffix: Clipboard, copy as Illustrator clipboard */
#define kcopyAsAICBSuffix		"copyAsAICB"
/** Preference suffix: Clipboard, append extension */
#define kappendExtensionSuffix	"appendExtension"
/** Preference suffix: Clipboard, lowercase */
#define klowerCaseSuffix		"lowerCase"
/** Preference suffix: Clipboard, flatten */
#define kflattenSuffix			"flatten"
/** Preference suffix: Clipboard options */
#define kAICBOptionSuffix	    "AICBOption"



/** Preferences: Illustrator clipboard option values */
enum  AICBOptions {PRESERVE_PATH, PRESERVE_APPEARANCE_OVERPRINT};
/** Preference default:Clipboard options */
const AICBOptions kAICBOptionsDefault= PRESERVE_APPEARANCE_OVERPRINT;

/** @ingroup PreferenceKeys
	Version Cue preference */
#define kUseVersionCue			"useVersionCue"

/** @ingroup PreferenceKeys
	Whether screen display uses a black preserving color transformation
	for converting CMYK to RGB or gray. The black preserving transform maps CMYK
	0,0,0,1 to the darkest black available. Not colorimetrically accurate
	but sometimes preferable for viewing CMYK black line art and text. The
	default value is given by \c #kAIPrefDefaultOnscreenBlackPres. */
#define kAIPrefKeyOnscreenBlackPres			((const char*) "blackPreservation/Onscreen")
/** @ingroup PreferenceKeys
	Default value for \c #kAIPrefKeyOnscreenBlackPres. */
#define kAIPrefDefaultOnscreenBlackPres		true

/** @ingroup PreferenceKeys
	Whether printing and export uses a black preserving color transformation
	for converting CMYK to RGB or gray. The black preserving transform maps CMYK
	0,0,0,1 to the darkest black available. Not colorimetrically accurate
	but sometimes preferable for viewing CMYK black line art and text. The
	default value is given by \c #kAIPrefDefaultExportBlackPres. */
#define kAIPrefKeyExportBlackPres			((const char*) "blackPreservation/Export")
/** @ingroup PreferenceKeys
	Default value for \c #kAIPrefKeyExportBlackPres. */
#define kAIPrefDefaultExportBlackPres		true

/** @ingroup PreferenceKeys
	Sets the guide style (solid or dashed).
	The default value is given by \c #kAIPrefDefaultGuideStyle.  */
#define kAIPrefKeyGuideStyle ((const char*)"Guide/Style")
/** @ingroup PreferenceKeys
	The \c #kAIPrefKeyGuideStyle value for solid guides. */
#define kAIPrefGuideStyleSolid 0
/** @ingroup PreferenceKeys
	The \c #kAIPrefKeyGuideStyle value for dashed guides. */
#define kAIPrefGuideStyleDashed 1
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefKeyGuideStyle. */
#define kAIPrefDefaultGuideStyle kAIPrefGuideStyleSolid

/** @ingroup PreferenceKeys
	Sets the red component of the Guide color.
	The default value is given by \c #kAIPrefDefaultGuideColorRed.  */
#define kAIPrefKeyGuideColorRed ((const char*)"Guide/Color/red")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefKeyGuideColorRed. */
#define kAIPrefDefaultGuideColorRed		(0x4A3D/65535.0f)

/** @ingroup PreferenceKeys
	Sets the green component of the Guide color.
	The default value is given by \c #kAIPrefDefaultGuideColorGreen.  */
#define kAIPrefKeyGuideColorGreen ((const char*)"Guide/Color/green")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefKeyGuideColorGreen. */
#define kAIPrefDefaultGuideColorGreen		(1.0f)

/** @ingroup PreferenceKeys
	Sets the blue component of the Guide color.
	The default value is given by \c #kAIPrefDefaultGuideColorBlue.  */
#define kAIPrefKeyGuideColorBlue ((const char*)"Guide/Color/blue")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefKeyGuideColorBlue. */
#define kAIPrefDefaultGuideColorBlue		(1.0f)

/** @ingroup PreferenceKeys for Smart Guides (Snapomatic Plug-in)
	Sets the red component of the SmartGuide color.
	The default value is given by \c #kAIPrefDefaultSmartGuideColorRed.  */
#define kAIPrefKeySmartGuideColorRed ((const char*)"snapomatic/Color/red_19_2")
/** @ingroup PreferenceKeys for Smart Guides
	The default value for \c #kAIPrefKeySmartGuideColorRed. */
#define kAIPrefDefaultSmartGuideColorRed		(1.0f)

/** @ingroup PreferenceKeys for Smart Guides
	Sets the green component of the SmartGuide color.
	The default value is given by \c #kAIPrefDefaultGuideColorGreen.  */
#define kAIPrefKeySmartGuideColorGreen ((const char*)"snapomatic/Color/green_19_2")
/** @ingroup PreferenceKeys for Smart Guides (Snapomatic Plug-in)
	The default value for \c #kAIPrefKeySmartGuideColorGreen. */
#define kAIPrefDefaultSmartGuideColorGreen		(0x4A3D/65535.0f)

/** @ingroup PreferenceKeys for Smart Guides
	Sets the blue component of the SmartGuide color.
	The default value is given by \c #kAIPrefDefaultSmartGuideColorBlue.  */
#define kAIPrefKeySmartGuideColorBlue ((const char*)"snapomatic/Color/blue_19_2")
/** @ingroup PreferenceKeys for Smart Guides (Snapomatic Plug-in)
	The default value for \c #kAIPrefKeySmartGuideColorBlue. */
#define kAIPrefDefaultSmartGuideColorBlue		(1.0f)

/** @ingroup PreferenceKeys
	Whether to show the slice numbers or not.
	The default value is given by \c #kAIPrefDefaultShowSliceNumbers.  */
#define kAIPrefKeyShowSliceNumbers ((const char*)"plugin/AdobeSlicingPlugin/showSliceNumbers")
/** @ingroup PreferenceKeys
	Default value for \c #kAIPrefKeyShowSliceNumbers. */
#define kAIPrefDefaultShowSliceNumbers			true

/** @ingroup PreferenceKeys for Slicing feedback
	Sets the red component of the Slicing feedback color.
	The default value is given by \c #kAIPrefDefaultSlicingFeedbackColorRed.  */
#define kAIPrefKeySlicingFeedbackColorRed ((const char*)"plugin/AdobeSlicingPlugin/feedback/red")
/** @ingroup PreferenceKeys for Slicing feedback
	The default value for \c #kAIPrefKeySlicingFeedbackColorRed. */
#define kAIPrefDefaultSlicingFeedbackColorRed	(0xFFFF)

/** @ingroup PreferenceKeys for Slicing feedback
	Sets the green component of the Slicing feedback color.
	The default value is given by \c #kAIPrefDefaultSlicingFeedbackColorGreen.  */
#define kAIPrefKeySlicingFeedbackColorGreen ((const char*)"plugin/AdobeSlicingPlugin/feedback/green")
/** @ingroup PreferenceKeys for Slicing feedback
	The default value for \c #kAIPrefKeySlicingFeedbackColorGreen. */
#define kAIPrefDefaultSlicingFeedbackColorGreen	(0x4A3D)

/** @ingroup PreferenceKeys for Slicing feedback
	Sets the blue component of the Slicing feedback color.
	The default value is given by \c #kAIPrefDefaultSlicingFeedbackColorBlue.  */
#define kAIPrefKeySlicingFeedbackColorBlue ((const char*)"plugin/AdobeSlicingPlugin/feedback/blue")
/** @ingroup PreferenceKeys for Slicing feedback
	The default value for \c #kAIPrefKeySlicingFeedbackColorBlue. */
#define kAIPrefDefaultSlicingFeedbackColorBlue	(0x4A3D)

/** @ingroup PreferenceKeys
	Sets the greeking threshold for text drawing. Text rendered at a point size less than 
	or equal to the greeking threshold is rendered greeked.
	The default value is given by \c #kAIPrefDefaultTextGreekingThreshold.  */
#define kAIPrefKeyTextGreekingThreshold ((const char*)"text/greekingThreshold")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefKeyTextGreekingThreshold. */
#define kAIPrefDefaultTextGreekingThreshold		(6.0f)

/** @ingroup PreferenceKeys
	Sets the legacy gradient-mesh object conversion options when opening a legacy
	document (from an Illustrator version before CS 3). */
#define kAIPrefKeyLegacyGradientMeshConversionOptions ((const char*) "open/legacyGradientMeshConversion")
/** @ingroup PreferenceKeys
	Key values for \c #kAIPrefKeyLegacyGradientMeshConversionOptions. */
enum  LegacyGradientMeshConversionOptions {MESH_UNKNOWN, MESH_PRESERVE_SPOT, MESH_PRESERVE_APPEARANCE};

/** @ingroup PreferenceKeys
	Sets the tolerance preference for selection. Integer, a number of pixels. */
#define kAIPrefKeySelectionTolerance ((const char*) "selectionTolerance")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefKeySelectionTolerance. */
#define  kAIPrefDefaultSelectionTolerance (3)

/** @ingroup PreferenceKeys
	Sets the tolerance preference for selection in touch workspace. Integer, a number of pixels. */
#define kAIPrefKeyTWSSelectionTolerance ((const char*) "tws/SelectionTolerance")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefKeyTWSSelectionTolerance. */
#define  kAIPrefDefaultTWSSelectionTolerance (10)

/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefDefaultCornerAngleLimit. */
#define  kAIPrefDefaultCornerAngleLimit (177.0)

/** @ingroup PreferenceKeys
Determines whether strokes and effects will be scaled or not. */
#define kAIPrefKeyScaleStrokesAndEffects			((const char*)"scaleLineWeight")
/** @ingroup PreferenceKeys
	Determines whether or not anchor points will be highlighted on mouseover. */
#define kAIPrefKeyHighlightAnchorOnMouseover		((const char*)"highlightAnchorOnMouseOver")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefKeyHighlightAnchorOnMouseover. */
const bool kAIPrefKeyHighlightAnchorOnMouseoverDefault = true;

/** @ingroup PreferenceKeys
	Whether to show the legacy artboard conversion options when opening a legacy
	document (from an Illustrator version before CS 4). */
#define kShowArtboardConversionDialogKey 			((const char*) "LegacyArtboardOptions/ShowDialog")
/** @ingroup PreferenceKeys
	Sets the legacy artboard conversion options " Legacy Artboard" when opening a legacy
	document (from an Illustrator version before CS 4). */
#define kAIArtboardConversionDialogArtboardKey 		((const char*) "LegacyArtboardOptions/artboard")
/** @ingroup PreferenceKeys
	Sets the legacy artboard conversion options " Crop Area" when opening a legacy
	document (from an Illustrator version before CS 4). */
#define kAIArtboardConversionDialogCropAreaKey 		((const char*) "LegacyArtboardOptions/cropAreas")
/** @ingroup PreferenceKeys
	Sets the legacy artboard conversion options " Print tiles" when opening a legacy
	document (from an Illustrator version before CS 4). */
#define kAIArtboardConversionDialogTilesKey 			((const char*) "LegacyArtboardOptions/pageTiles")
/** @ingroup PreferenceKeys
	Sets the legacy artboard conversion options "Artwork Bounds" when opening a legacy
	document (from an Illustrator version before CS 4). */
#define kAIArtboardConversionDialogArtworkBoundsKey 	((const char*) "LegacyArtboardOptions/artworkBounds")

/** @ingroup PreferenceKeys
	Turns the Pixel Grid On/Off
	The default value is given by \c #kAIPrefDefaultShowPixelGrid.  */
#define kAIPrefKeyShowPixelGrid ((const char*)"Guide/ShowPixelGrid")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefKeyGuideColorRed. */
#define kAIPrefDefaultShowPixelGrid		TRUE

/** @ingroup PreferenceKeys
	Determines whether or not link info will be shown in links panel */
#define kAIPrefKeyShowLinkInfo		((const char*)"showLinkInfo")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefKeyShowLinkInfo. */
const bool kAIPrefKeyShowLinkInfoDefault = false;

/** @ingroup PreferenceKeys
	creative cloud pref - preferences and workspaces.
	The default value is given by \c #kAIPrefDefaultCreativeCloudPreferences.  */
#define kAIPrefCreativeCloudPreferences ((const char*)"CreativeCloud/preferences")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefCreativeCloudPreferences. */
#define kAIPrefDefaultCreativeCloudPreferences		TRUE

/** @ingroup PreferenceKeys
	creative cloud pref - Swatches
	The default value is given by \c #kAIPrefDefaultCreativeCloudSwatches.  */
#define kAIPrefCreativeCloudSwatches ((const char*)"CreativeCloud/Swatches")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefCreativeCloudSwatches. */
#define kAIPrefDefaultCreativeCloudSwatches		TRUE


/** @ingroup PreferenceKeys
	creative cloud pref - Presets
	The default value is given by \c #kAIPrefDefaultCreativeCloudPresets.  */
#define kAIPrefCreativeCloudPresets ((const char*)"CreativeCloud/Presets")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefCreativeCloudPresets. */
#define kAIPrefDefaultCreativeCloudPresets		TRUE

/** @ingroup PreferenceKeys
	creative cloud pref - Symbols
	The default value is given by \c #kAIPrefDefaultCreativeCloudSymbols.  */
#define kAIPrefCreativeCloudSymbols ((const char*)"CreativeCloud/Symbols")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefCreativeCloudSymbols. */
#define kAIPrefDefaultCreativeCloudSymbols		TRUE

/** @ingroup PreferenceKeys
	creative cloud pref - Brushes
	The default value is given by \c #kAIPrefDefaultCreativeCloudBrushes.  */
#define kAIPrefCreativeCloudBrushes ((const char*)"CreativeCloud/Brushes")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefCreativeCloudBrushes. */
#define kAIPrefDefaultCreativeCloudBrushes		TRUE

/** @ingroup PreferenceKeys
	creative cloud pref - Graphic Styles
	The default value is given by \c #kAIPrefDefaultCreativeCloudGraphicStyles.  */
#define kAIPrefCreativeCloudGraphicStyles ((const char*)"CreativeCloud/GraphicStyles")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefCreativeCloudGraphicStyles. */
#define kAIPrefDefaultCreativeCloudGraphicStyles		TRUE

/** @ingroup PreferenceKeys
	creative cloud pref - Workspaces
	The default value is given by \c #kAIPrefDefaultCreativeCloudWorkspaces.  */
#define kAIPrefCreativeCloudWorkspaces ((const char*)"CreativeCloud/Workspaces")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefCreativeCloudWorkspaces. */
#define kAIPrefDefaultCreativeCloudWorkspaces		TRUE

/** @ingroup PreferenceKeys
	creative cloud pref - Keyboard shortcuts
	The default value is given by \c #kAIPrefDefaultCreativeCloudKBS.  */
#define kAIPrefCreativeCloudKBS ((const char*)"CreativeCloud/KBS")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefCreativeCloudKeyboard shortcuts. */
#define kAIPrefDefaultCreativeCloudKBS		TRUE


/** @ingroup PreferenceKeys
	creative cloud pref - Asian Settings
	The default value is given by \c #kAIPrefDefaultCreativeCloudAsianSettings.  */
#define kAIPrefCreativeCloudAsianSettings ((const char*)"CreativeCloud/AsianSettings")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefCreativeCloudAsianSettings. */
#define kAIPrefDefaultCreativeCloudAsianSettings		TRUE

/** @ingroup PreferenceKeys
	creative cloud pref - Conflict Handling Action
	The default value is given by \c #kAIPrefDefaultCreativeCloudConflictHandling.  */
#define kAIPrefCreativeCloudConflictHandling ((const char*)"CreativeCloud/ConflictHandling")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefCreativeCloudConflictHandling. */
#define kAIPrefDefaultCreativeCloudConflictHandling		AIPreferenceUtil::kAskMe

/** @ingroup PreferenceKeys
	creative cloud pref - Sync Popup state
	The default value is given by \c #kAIPrefDefaultCreativeCloudSyncPopup.  */
#define kAIPrefCreativeCloudSyncPopup ((const char*)"CreativeCloud/SyncPopup")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefCreativeCloudSyncPopup. */
#define kAIPrefDefaultCreativeCloudSyncPopup		AIPreferenceUtil::kAllSettings

/** @ingroup PreferenceKeys
	Live Shape pref - Constrain dimensions
	The default value is given by \c #kAIPrefDefaultLiveShapesConstrainDimensions.  */
#define kAIPrefLiveShapesConstrainDimensions		((const char*)"LiveShapes/constrainDimensions")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefLiveShapesConstrainDimensions. */
#define kAIPrefDefaultLiveShapesConstrainDimensions		TRUE

/** @ingroup PreferenceKeys
	Live Shape pref - Constrain radii
	The default value is given by \c #kAIPrefDefaultLiveShapesConstrainRadii.  */
#define kAIPrefLiveShapesConstrainRadii		((const char*)"LiveShapes/constrainRadii")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefLiveShapeConstrainRadii. */
#define kAIPrefDefaultLiveShapesConstrainRadii		TRUE

/** @ingroup PreferenceKeys
	Live Shape pref - Constrain angles in pie
	The default value is given by \c #kAIPrefDefaultLiveShapesConstrainPieAngles.  */
#define kAIPrefLiveShapesConstrainPieAngles	((const char*)"LiveShapes/constrainPieAngles")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefLiveShapesConstrainPieAngles. */
#define kAIPrefDefaultLiveShapesConstrainPieAngles		FALSE

/** @ingroup PreferenceKeys
	Live Shape pref - Auto show shape properties UI on shape creation
	The default value is given by \c #kAIPrefDefaultLiveShapesAutoShowPropertiesUI.  */
#define kAIPrefLiveShapesAutoShowPropertiesUI		((const char*)"LiveShapes/autoShowPropertiesUIOnCreatingShape")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefLiveShapeAutoShowPropertiesUI. */
#define kAIPrefDefaultLiveShapesAutoShowPropertiesUI		FALSE

/** @ingroup PreferenceKeys
	Live Shape pref - Hide shape widgets for shape tool
	The default value is given by \c #kAIPrefDefaultLiveShapesHideWidgetsForShapeTool.  */
#define kAIPrefLiveShapesHideWidgetsForShapeTools		((const char*)"LiveShapes/hideWidgetsForShapeTools")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefLiveShapesHideWidgetsForShapeTool. */
#define kAIPrefDefaultLiveShapesHideWidgetsForShapeTools	FALSE

/** @ingroup PreferenceKeys
	Policy for preserving corners: governs the way corners are modified while transformations, e.g. scaling radii, maintaining corner radii value
	The default value is given by \c #kAIPrefDefaultPreserveCornersPolicy.  */
#define kAIPrefPreserveCornersPolicy					((const char*)"policyForPreservingCorners")
/** @ingroup PreferenceKeys
	Key values for \c #kAIPrefPreserveCornersPolicy. */
enum CornerPreservePolicy { kAIPrefScaleCornersRadii = 1, kAIPrefMaintainCornersRadii };
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefPreserveCornersPolicy. */
const CornerPreservePolicy kAIPrefDefaultPreserveCornersPolicy = kAIPrefMaintainCornersRadii;

/** @ingroup PreferenceKeys
 Performance pref - GPU Support detected*/
#define kAIPrefPerformanceGPUSupported ((const char*)"Performance/GPUSupported")
/** @ingroup PreferenceKeys
	Performance pref - Enable GPU rendering*/
#define kAIPrefPerformanceEnableGPU ((const char*)"Performance/EnableGPU_Ver19_2")

/** @ingroup PreferenceKeys
	Performance pref - Enable Animated Zoom*/
#define kAIPrefPerformanceAnimZoom ((const char*)"Performance/AnimZoom")

/** @ingroup PreferenceKeys
	Performance pref - Enable Thin Filled Paths */
#define kAIPrefPerformanceEnableThinFilledPaths ((const char*)"Performance/EnableThinFilledPaths")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefPerformanceEnableThinFilledPaths. */
#define kAIPrefDefaultPerformanceEnableThinFilledPaths		false

/** @ingroup PreferenceKeys
	Performance pref - Enable GPU rendering for CMYK */
#define kAIPrefPerformanceEnableCMYK ((const char*)"Performance/EnableCMYK")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefPerformanceEnableCMYK. */
#define kAIPrefDefaultPerformanceEnableCMYK		false

/** @ingroup PreferenceKeys
Performance pref - Display Setting */
#define kAIPrefPerformanceDisplaySetting ((const char*)"Performance/DisplaySetting")
/** @ingroup PreferenceKeys
The default value for \c #kAIPrefPerformanceDisplaySetting. */
#define kAIPrefDefaultPerformanceDisplaySetting		(0)

/** @ingroup PreferenceKeys
Performance pref - MSAA Value */
#define kAIPrefPerformanceMSAAValue ((const char*)"Performance/MSAAValue")
/** @ingroup PreferenceKeys
The default value for \c #kAIPrefPerformanceMSAAValue. */
#define kAIPrefDefaultPerformanceMSAAValue		(0)

/** @ingroup PreferenceKeys
	Crash Recovery pref - Automatically Save CheckBox Value*/
#define kAIPrefCrashRecoveryAutomaticallySave ((const char*)"CrashRecovery/AutomaticallySave")

/** @ingroup PreferenceKeys
	Crash Recovery pref - Minimum enforced time between two consecutive incremental save operations*/
#define kAIPrefCrashRecoveryIdleLoopTimeInterval ((const char*)"CrashRecovery/IdleLoopTimeInterval")

/** @ingroup PreferenceKeys
	Crash Recovery pref - Folder location where incremental files are saved*/
#define kAIPrefCrashRecoveryFolderLocation	((const char*)"CrashRecovery/RecoveryFolderLocation")

/** @ingroup PreferenceKeys
	Crash Recovery pref - Turn off for Complex file Checkbox value*/
#define kAIPrefCrashRecoveryTurnOffForComplexDocument	((const char*)"CrashRecovery/TurnOffForComplexDocument")

/** @ingroup PreferenceKeys
	Scale Illustrator UI */
#define kAIPrefScaleUI ((const char*)"UIPreferences/scaleUI")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefScaleUI. */
#define kAIPrefDefaultScaleUI		true

/** @ingroup PreferenceKeys
	Scale Illustrator UI to higher supported or lower supported scale factor. Value 0 means snap to lower supported scale factor while 1 means snap to higher one. */
#define kAIPrefSnapUIScaleFactor ((const char*)"UIPreferences/snapUIScaleFactor")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefSnapUIScaleFactor. */
#define kAIPrefDefaultSnapUIScaleFactor		1

/** @ingroup PreferenceKeys
	Touch Pref - Switch to Touch Workspace on Detaching Keyboard
	The default value is given by \c #kAIPrefDefaultTWSKeyboardDetach.  */
#define	kAIPrefTWSKeyboardDetach ((const char*)"TouchPreferenceUI/TWSKeyboardDetach")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefTWSKeyboardDetach. */
#define kAIPrefDefaultTWSKeyboardDetach		true
/** @ingroup PreferenceKeys
	Touch Pref - Use Precise Cursors
	The default value is given by \c #kAIPrefDefaultPreciseCursors.  */
#define kAIPrefPreciseCursors ((const char*)"TouchPreferenceUI/PreciseCursor")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefPreciseCursors. */
#define kAIPrefDefaultPreciseCursors	true
/** @ingroup PreferenceKeys
Determines whether or not to enable constrain scaling in Shaper in TWS. */
#define kAIPrefShaperConstrainScale			((const char*)"shaper/constrainScaling")
/** @ingroup PreferenceKeys
The default value for \c #kAIPrefShaperConstrainScale. */
#define kAIPrefShaperConstrainScaleDefault  false
/** @ingroup PreferenceKeys
	Touch Pref - Soft Message Default Duration
	The default value is given by \c #kAIPrefDefault/SoftMessageDuration.  */
#define kAIPrefSoftMessageDuration ((const char*)"TouchPreferenceUI/SoftMessageDuration")
	/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefSoftMessageDuration. */
#define kAIPrefDefaultSoftMessageDuration (4.0f)

/** @ingroup PreferenceKeys
ExpFeatures Pref - Enable Creative Cloud Charts
The default value is given by \c #kAIPrefDefaultEnableCCCharts.  */
#define kAIPrefEnableCCCharts ((const char*)"ExpFeaturesPreferenceUI/EnableCCCharts")
/** @ingroup PreferenceKeys
The default value for \c #kAIPrefEnableCCCharts. */
#define kAIPrefDefaultEnableCCCharts	false

/** @ingroup PreferenceKeys
	Making New Rectangular Area Text Auto Sizable by default */
#define kAIPrefTextBoxAutoSizing ((const char*)"text/autoSizing")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefTextBoxAutoSizing. */
#define kAIPrefTextBoxAutoSizingDefaultValue	false
		
/** @ingroup PreferenceKeys
Determines whether or not to show What's New Dialog */
#define kAIPrefDontShowMissingFontDlg		((const char*)"DontShowMissingFontDialogPreference")
/** @ingroup PreferenceKeys
	The default value for \c #kAIPrefShowMissingFontDlg. */
const bool kAIPrefDontShowMissingFontDlgDefault = false;

/** @ingroup PreferenceKeys
Determines whether or not UIDs are automatically assigned to art objects, in the document being created */
#define kAIPrefAutoAssignUIDsForDocCreated		((const char*)"AutoAssignUIDsForDocCreatedPreference")
/** @ingroup PreferenceKeys
The default value for \c #kAIPrefAutoAssignUIDsForDocCreated. */
const bool kAIPrefAutoAssignUIDsForDocCreatedDefault = false;

/** @ingroup PreferenceKeys
Determines whether or not UIDs are automatically assigned to art objects, in the document being opened */
#define kAIPrefAutoAssignUIDsForDocOpened		((const char*)"AutoAssignUIDsForDocOpenedPreference")
/** @ingroup PreferenceKeys
The default value for \c #kAIPrefAutoAssignUIDsForDocOpened. */
const bool kAIPrefAutoAssignUIDsForDocOpenedDefault = false;

/** @ingroup PreferenceKeys
Determines whether or not to hide corner widgets based on Angle */
#define kAIPrefHideCornerWidgetBasedOnAngle		((const char*)"liveCorners/hideCornerWidgetBasedOnAngle")
/** @ingroup PreferenceKeys
The default value for \c #kAIPrefHideCornerWidgetBasedOnAngle. */
const bool kAIPrefHideCornerWidgetBasedOnAngleDefault = true;

/** @ingroup PreferenceKeys
Sets the Corner Angle Limit for Hiding Corner Widgets */
#define kAIPrefCornerAngleLimit					((const char*)"liveCorners/cornerAngleLimit")

/** @ingroup PreferenceKeys
Determines whether or not to show bounding box */
#define kAIPrefShowBoundingBox					((const char*)"showBoundingBox")


#define kShowRecentFileWSKey					((const char*)"Hello/RecentFileWS")
/** @ingroup PreferenceKeys
The default value for \c #kShowRecentFileWSKey. */
const bool kAIPrefShowRecentFileWSDefault = false;

#define kShowHomeScreenWSKey					((const char*)"Hello/ShowHomeScreenWS")
/** @ingroup PreferenceKeys
The default value for \c #kShowHomeScreenWSKey. */
const bool kAIPrefShowHomeScreenWSDefault = true;

/** @ingroup PreferenceKeys
Determines whether or not to show Tool Guides. Used in AI 19.2 or greater */
#define kAISnappingPrefShowToolGuides			((const char*)"smartGuides/showToolGuides")
/** @ingroup PreferenceKeys
The default value for \c #kAISnappingPrefShowToolGuides. */
const bool kAISnappingPrefShowToolGuidesDefault = false;

/** Preference prefix: Number of Default Recent File  */
#define kRecentFileNumberPrefix nullptr
/** Preference suffix: Number of Default Recent File  */
#define kRecentFileNumberSuffix ((const char *)"RecentFileNumber")
/** Preference default:Number of Default Recent File */
const unsigned int kRecentFileNumberDefault = 20;
/** @ingroup PreferenceKeys
Determines the tolerance for snapping to angles while rotating a live shape. Used in AI 19.2 or greater */
#define kAISnappingPrefAngularTolerance			((const char*)"smartGuides/angularTolerance")
/** @ingroup PreferenceKeys
The default value for \c #kAISnappingPrefAngularTolerance. */
const ai::int32 kAISnappingPrefAngularToleranceDefault = 2;

/** @ingroup PreferenceKeys
Live Shape pref - Determines whether shapes created by Shape Tools(Rectangle, Polygon, Ellipse, Line) are live.
The default value is given by \c #kAIPrefDefaultCreateLiveShapes.  */
#define kAIPrefCreateLiveShapes					((const char*)"LiveShapes/createLiveShapes")
/** @ingroup PreferenceKeys
The default value for \c #kAIPrefCreateLiveShapes. */
#define kAIPrefDefaultCreateLiveShapes			TRUE

/** @ingroup PreferenceKeys
Linked files pref - Determines if the UNC(Universal Naming Convention) path needs to be used or the default
path of file needs to be used. Only makes sense for Windows. \c #kAIPrefUseUNCPath.  */
#define kAIPrefUseUNCPath					((const char*)"FilePath/UNCPath")
/** @ingroup PreferenceKeys
The default value for \c #kAIPrefUseUNCPath. */
#define kAIPrefDefaultUseUNCPath			TRUE

/** Preference default:Number of Default Recent Presets */
const unsigned int kRecentPresetsNumberDefault = 20;

#endif
