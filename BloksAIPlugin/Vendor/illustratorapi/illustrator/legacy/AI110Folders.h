#ifndef __AI110Folders__
#define __AI110Folders__

/*
 *        Name:	AI110Folders.h
 *   $Revision: 1 $
 *      Author:	 dmaclach
 *        Date:	   
 *     Purpose:	Adobe Illustrator 11.0 Folders Suite.
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

#include "AIFolders.h"

#include "AIHeaderBegin.h"

/** @file AI110Folders.h */

/*******************************************************************************
 **
 **	Suite name and version
 **
 **/

#define kAIFoldersSuiteVersion2			AIAPI_VERSION(2)
#define kAI110FoldersSuiteVersion		kAIFoldersSuiteVersion2
#define kAI110FoldersVersion			kAI110FoldersSuiteVersion

/*******************************************************************************
 **
 **	Suite
 **
 **/


/**
	The AIFoldersSuite provides APIs that return the locations of the standard
	folders used by Illustrator. The diagram below shows the layout of these folders
	and the corresponding identifiers.

@verbatim

  Local Hierarchy:
  
  	Adobe Illustrator X:						<- kAIRootFolderType
  		Adobe Illustrator X:					<- kAIPackageFolderType
  			Contents:							<- kAIContentsFolderType
  				Windows/MacOSClassic:			<- kAIApplicationFolderType
  					+The Executable
  					+Shared Libraries
  			Help:								<- kAIHelpFolderType
  				+HTML Help Files
  				images:							<- kAIHelpImagesFolderType
  					+Help Graphics
  			Helpers:							<- kAIHelpersFolderType
  				Preview In:						<- kAIPreviewInFolderType
  			Required:							<- kAIRequiredPluginsFolderType
  				+Required Plugins
  				Fonts:							<- kAIRequiredFontsFolderType
  					+Required Fonts
  		Legal:									<- kAILegalFolderType
  			+EULA
  		Plug-ins:								<- kAIPluginsFolderType - Can be changed By User   kAIStartupFileFolderType/kAIRidersFileFolderType both point here as well currently. This may change in the future.
  			Extensions:
  			Illustrator Filters:
  			Illustrator Formats - Other:
  			Illustrator Formats - Standard:
  			Photoshop Effects:					
  			Photoshop Filters:					
  			Photoshop Formats:					
  			Text Filters:						<- kAIHyphenationDictFolderType
  			Dictionaries:						<- kAIDictionariesFolderType/kAIHyphenationDictFolderType/kAISpellingDictFolderType (all three of these currently point at the same folder. This may change in the future. Please choose the one that is most appropriate for your usage.)
  			Tools:								
  			Tsume:								<- kAITsumeFolderType
  		Presets:								<- kAIPresetsFolderType
  			Actions:							<- kAIPresetActionsFolderType
  			Brushes:							<- kAIPresetBrushesFolderType
			Color Books:						<- kAIPresetColorBooksFolderType
  			Gradients:							<- kAIPresetGradientsFolderType
  			Keyboard Shortcuts:					<- kAIPresetKeyboardShortcutsFolderType
  			Patterns:							<- kAIPresetPatternsFolderType
  			Save for Web Settings:				<- kAISettingsFolderType
  				Color Tables:					<- kAIColorTableSettingsFolderType
  					+Color tables
  				Optimize:						<- kAIOptimizeSettingsFolderType
  					+Optimize Settings
  			Scripts:							<- kAIPresetScriptsFolderType
  			Styles:								<- kAIPresetStylesFolderType
  			Swatches:							<- kAIPresetSwatchesFolderType
  				Color Systems:					<- kAIPresetColorSystemsFolderType
  			Symbols:							<- kAIPresetSymbolsFolderType
  			Templates:							<- kAIPresetTemplatesFolderType
  				Blank Documents:				<- kAIPresetBlankDocumentsFolderType
  		Fonts:									<- kAIFontsFolderType
	  		Composite Fonts 					<- kAIFontsCFFolderType
				Temp							<- kAIFontsCFTempFolderType
  			CMaps:								<- kAIFontsCMapsFolderType
  		Sample Files:							<- kAISampleFilesFolderType
  			Graph Designs:						<- kAISampleGraphDesignsFolderType
  			Sample Art:							<- kAISampleArtFolderType
  				SVG:							<- kAISampleSVGFolderType
  				Data-Driven Graphics:			<- kAIDataDrivenGraphicsFolderType
  		Utilities:								<- kAIUtilitiesFolderType
  		
  
  
  System Hierarchies:
  		
  	The diagram below tries to describe the parts of the directory hierarchy of
  	Illustrator 10 that are located under system folders. The locations of such
  	directories are necessarily dependent on the OS. In the diagram a name
  	enclosed in square brackets [...] indicates a system dependent directory.
  	The values for these directories for each system are defined following the
  	diagram.
  
  	[PrimaryScratch]							<- kAIPrimaryScratchFolderType
  		+ primary scratch file location
  	[SecondaryScratch] 							<- kAISecondaryScratchFolderType
  		+ secondary scratch file location
  	[AIPreferences]								<- kAIPreferencesFolderType
  		+ preferences file location
  		+ plugin cache file location
  	[UserSupport]								<- kAIUserSupportFolderType
  		Adobe Illustrator X						<- kAIUserSupportAIFolderType
  			plugins	 							<- kAIUserSupportAIPluginsFolderType
  				+ plugins that are usable by the user who is logged in
  		Fonts									<- kAIUserSupportCommonFontsFolderType
  	[ApplicationSupportCommon]					<- kAIApplicationSupportCommonFolderType
  		Color  									<- kAIApplicationSupportCommonColorFolderType
  			Profiles 							<- kAIApplicationSupportCommonColorProfilesFolderType
  			Settings							<- kAIApplicationSupportCommonColorSettingsFolderType
  		typeSpt									<- kAIApplicationSupportCommonTypeSupportFolderType
  			Kinsoku Sets						<- kAIApplicationSupportCommonKinsokuSetFolderType
  			Mojikume Sets						<- kAIApplicationSupportCommonMojikumeSetFolderType
  		Fonts									<- kAIApplicationSupportCommonFontsFolderType
  			Reqrd								<- kAIApplicationSupportCommonFontsReqrdFolderType
  				Base							<- kAIApplicationSupportCommonFontsReqrdBaseFolderType
  				cmaps							<- kAIApplicationSupportCommonFontsReqrdCMapsFolderType
  		PDFL									<- kAIApplicationSupportCommonPDFLFolderType
  			PDFL5.0 							<- kAIApplicationSupportCommonPDFL5FolderType
  				cmaps 							<- kAIApplicationSupportCommonPDFL5CMapsFolderType
  				fonts							<- kAIApplicationSupportCommonPDFL5FontsFolderType
  		Printspt 								<- kAIApplicationSupportCommonPrintSupportFolderType
  		Workflow 								<- kAIApplicationSupportCommonWorkflowFolderType
  	[MyDocuments]								<- kAIMyDocumentsFolderType
  		 +default documents file location
  	[PPDs]										<- kAIPrinterDescriptionsFolderType
  		+ ppd location
  	[Logs]										<- kAILogsFolderType
  System Dependant Directories:
   
  	W2k/W9x
  	-------
  	PrimaryScratch = System definition of temporary but can be changed by user
  	SecondaryScratch = System definition of temporary but can be changed by user
  	AIPreferences = Documents and Settings\username\Application Data\Adobe\Adobe Illustrator X
  	UserSupport = Documents and Settings\username\Application Data\Adobe
  	ApplicationSupportCommon = Program Files\Common Files\Adobe
  	MyDocuments = Documents and Settings\username\My Documents
  	PPDs = unknown
  	Logs = Documents and Settings\username\Application Data\Adobe\Logs
  
  	WNT
  	---
  	PrimaryScratch = System definition of temporary but can be changed by user
  	SecondaryScratch = System definition of temporary but can be changed by user
  	AIPreferences = \system\profiles\username\Application Data\Adobe\Adobe Illustrator X
  	UserSupport = \system\profiles\username\Application Data\Adobe
  	ApplicationSupportCommon = Program Files\Common Files\Adobe
  	MyDocuments = \system\profiles\username\My Documents
  	PPDs = unknown
    Logs = \system\profiles\username\Application Data\Adobe\Logs
    
  	OSX
  	---
  	PrimaryScratch = System definition of temporary but can be changed by user
  	SecondaryScratch = System definition of temporary but can be changed by user
  	AIPreferences = ~/Library/Preferences/Adobe Illustrator X
  	UserSupport = ~/Library/Application Support/Adobe
  	ApplicationSupportCommon = /Library/Application Support/Adobe
  	MyDocuments = ~/Documents
  	PPDs = Libraries/Printers/PPDs
	Logs = ~/Library/Logs/Adobe Illustrator CS
	
@endverbatim
*/
typedef struct {

	// - version 1 api - 

	/** Get the name of the folder. The name buffer must be of size #kMaxPathLength. Only
		the name of the folder is returned not the full path.*/
	AIAPI AIErr (*GetFolderName)(AIFolderType type, char *name);


} AI110FoldersSuite;


#include "AIHeaderEnd.h"


#endif
