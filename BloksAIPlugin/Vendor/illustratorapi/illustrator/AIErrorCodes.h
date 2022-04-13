/*************************************************************************
*
* ADOBE CONFIDENTIAL
*
* Copyright 2019 Adobe
*
* All Rights Reserved.
*
* NOTICE: Adobe permits you to use, modify, and distribute this file in
* accordance with the terms of the Adobe license agreement accompanying
* it. If you have received this file from a source other than Adobe,
* then your use, modification, or distribution of it requires the prior
* written permission of Adobe.
*
**************************************************************************/

#pragma once

enum AIErrorCode : ai::int32
{
    kAICoreErrorRangeStart							= 0x00000001, // = 1.    Start of Error Range used by Illustrator core (app) only
    kAICoreErrorRangeEnd							= 0x00000800, // = 2048. End of Error Range used by Illustrator core (app) only

    //----------------------------------------------------------------------------------------------------------
    kAICommonErrorRangeStart						= kAICoreErrorRangeEnd + 1, // = 2049. Start of Error Range used by Illustrator plugins and core (app)

    kAIAlreadyExportingSameDocument					= kAICommonErrorRangeStart + 1, // = 2050 //Returned if there is already a request being processed to export the same document.
    kAIOriginalNetworkPathDoesNotExist				= kAICommonErrorRangeStart + 2, //Original network path is not found, may be it is called when optimized open/save is not being performed
    kAIScratchFolderNotAvailable					= kAICommonErrorRangeStart + 3, //Scratch folder is not accessible
    kAISufficientScratchDiskSpaceNotAvailable		= kAICommonErrorRangeStart + 4, //Scratch folder does not have enough space
    kAIMultipleArtboardInASingleArtboardWorkflow    = kAICommonErrorRangeStart + 5, //Work flow does not support Multiple artboard documents
    kAIPreConditionNotMet							= kAICommonErrorRangeStart + 6, //Pre-condition for an work-flow is not met
    kAIFeatureNotOptedIn							= kAICommonErrorRangeStart + 7, //Feature not opted-in
    kAIFeatureNotEnabled							= kAICommonErrorRangeStart + 8, //Feature not enabled
	kAIFileCopyToNetworkLocationFailed				= kAICommonErrorRangeStart + 9,  //File could not be copied to a network location, may be due to network failure
	kAIJSONParsingFailed							= kAICommonErrorRangeStart + 10, //Error When Parsing A JSON value
	kAIVerificationFailedErr						= kAICommonErrorRangeStart + 11, // = 2060 //Error when Document Corruption Verification is failed
	kAIFileReadError								= kAICommonErrorRangeStart + 12, //Error when reading a file
	kAIFileRenameError								= kAICommonErrorRangeStart + 13, //Error while renaming file
	kAICorruptLinkErr								= kAICommonErrorRangeStart + 14, //Error while opening a linked file due to Corruption
	kAICantCutAllArtboardsErr                       = kAICommonErrorRangeStart + 15, //Artboard Copy-Paste Error 
    kAINoSpaceToPasteArtboardErr                    = kAICommonErrorRangeStart + 16, //Artboard Copy-Paste Error - No Space left after copy
    kAIHTTPErr										= kAICommonErrorRangeStart + 17,
	kAIDXFDWGSDKErr                                 = kAICommonErrorRangeStart + 18, // Error when calling RealDWG api
    kAILiveEditTimeExceededErr                      = kAICommonErrorRangeStart + 19, // Error in case of live edit fallback occured during operation.
	kAIJsonValueNotAMapErr							= kAICommonErrorRangeStart + 20,
    kAIFileNotFoundErr                              = kAICommonErrorRangeStart + 21, // = 2070
    kAIFileGenratedByForegroundSaveNotFoundErr      = kAICommonErrorRangeStart + 22,
	kAINotACloudDocumentErr							= kAICommonErrorRangeStart + 23,
	kAINotALocalDocumentErr							= kAICommonErrorRangeStart + 24,
	kCloudDocumentAlreadyOpeningErr					= kAICommonErrorRangeStart + 25, //The cloud document is already in open 
	kAINotOnMainThreadError							= kAICommonErrorRangeStart + 26,
	kAINoFeatureFound								= kAICommonErrorRangeStart + 27,
    kAISignatureNotValid                            = kAICommonErrorRangeStart + 28,
	kAIUserNotRegisteredWithCloudErr                = kAICommonErrorRangeStart + 29,
    kAIInvalidToolBoxDrawerTileViewErr              = kAICommonErrorRangeStart + 30,
    kAIRepeatArtIsolationModeNotActiveErr           = kAICommonErrorRangeStart + 31, // = 2080
    kAIFileDeleteError                              = kAICommonErrorRangeStart + 32, 
    kAIDirectoryDeleteError                         = kAICommonErrorRangeStart + 33,
    kAIFastExportFailedErr                          = kAICommonErrorRangeStart + 34,
    kAICantHibernateInvalidDocType                  = kAICommonErrorRangeStart + 35,
    kAICantHibernatePreferenceOff                   = kAICommonErrorRangeStart + 36,
    kAIInvalidHibernateInfoFile                     = kAICommonErrorRangeStart + 37,
    kAIFileFormatNotFoundErr                        = kAICommonErrorRangeStart + 38,
    kAITaskCantBeScheduledErr                       = kAICommonErrorRangeStart + 39,
    kAILiveEffectNotFoundErr                        = kAICommonErrorRangeStart + 40,
    kAIUserNotLoggedInToCCErr                       = kAICommonErrorRangeStart + 41, // = 2090
    kAILiveEffectParamsNotFoundErr                  = kAICommonErrorRangeStart + 42,
    kAILiveEffectVisibilityHiddenErr                = kAICommonErrorRangeStart + 43,
    kAIFileCopyErr                                  = kAICommonErrorRangeStart + 44,
    kUITaskGroupExistsError                         = kAICommonErrorRangeStart + 45,
    kUITaskGroupDoesNotExistError                   = kAICommonErrorRangeStart + 46,
    kUITaskGroupInvalidHandle                       = kAICommonErrorRangeStart + 47,
    kAIUnsupportedSkiaFeatureErr                    = kAICommonErrorRangeStart + 48,
	kAIUnsupportedAGMGPUFeatureErr                  = kAICommonErrorRangeStart + 49,
    kAISkipEffectExecutionErr                       = kAICommonErrorRangeStart + 50,
    kAICodecNotAvailableErr                         = kAICommonErrorRangeStart + 51,
    kAIPDFFormatUnknownErr                          = kAICommonErrorRangeStart + 52,
    kAICantErr                                      = kAICommonErrorRangeStart + 53,
    kAINotEnoughRAMErr                              = kAICommonErrorRangeStart + 54,
    kAIBrokenJPEGErr                                   = kAICommonErrorRangeStart + 55,
    kAIPluginLoadingErr                             = kAICommonErrorRangeStart + 56,
    kAIFileReadWriteErr                             = kAICommonErrorRangeStart + 57,
	


    //Robin Specific errors
    kAIRobinErrorCodeStarted						= kAICommonErrorRangeStart + 1100, // = 3149
    kAIRobinClientNotRegisteredWithVulcanErr		= kAIRobinErrorCodeStarted + 1, // = 3150
    kAIRobinServiceIsDownErr						= kAIRobinErrorCodeStarted + 2,
    kAIRobinCommunicationBrokenErr					= kAIRobinErrorCodeStarted + 3,
    kAIRobinServiceFailedToOpenFileErr				= kAIRobinErrorCodeStarted + 4,
	kAIRobinJobFailedUptoMaxTimesErr				= kAIRobinErrorCodeStarted + 5,
	kAIRobinNoErrorCodeInFailedResponseMsgErr		= kAIRobinErrorCodeStarted + 6,
	kAIRobinAckOfMessageNotReceivedErr			    = kAIRobinErrorCodeStarted + 7,
	kAIRobinFallbackAllAsServiceInactiveErr			= kAIRobinErrorCodeStarted + 8,
	kAIRobinFallbackAllAsServiceNotRunningErr		= kAIRobinErrorCodeStarted + 9,
	kAIRobinCommandFallbackNotImplementedErr		= kAIRobinErrorCodeStarted + 10,
	kAIRobinCrashedWhileExecutingJobErr				= kAIRobinErrorCodeStarted + 11, // = 3160
	kAIRobinRealErrorConvertedToCancelErr			= kAIRobinErrorCodeStarted + 12,
    
	kAIRobinErrorCodeEnded							= kAICommonErrorRangeStart + 1200,
   
    kAICommonErrorRangeEnd							= 0x0000FFFF, //End of Error Range used by Illustrator plugins and core (app)
    
    //----------------------------------------------------------------------------------------------------------

    kAIThirdPartySDKErrorRangeStart					= 0x00010000, //Start of Error range reserved for use by SDK
	kAIThirdPartySDKErrorRangeEnd					= 0x0001FFFF, //End   of Error range reserved for use by SDK
};

