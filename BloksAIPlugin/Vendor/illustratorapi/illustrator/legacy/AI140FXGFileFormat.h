#ifndef __AI140FXGFileFormat__
#define __AI140FXGFileFormat__

/*
*        Name:	AIFXGFileFormat.h
*      Author:
*        Date:
*     Purpose:	Adobe Illustrator FXG Suite.
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 2007-2008 Adobe Systems Incorporated.
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
#include "AIFXGFileFormat.h"

#include "AIHeaderBegin.h"

/** @file AIFXGFileFormat.h */

/*******************************************************************************
**
** Constants
**
**/

#define kAI140FXGFileFormatSuite				kAIFXGFileFormatSuite
#define kAIFXGFileFormatSuiteVersion1			AIAPI_VERSION(1)
#define kAI140FXGFileFormatSuiteVersion			kAIFXGFileFormatSuiteVersion1
#define kAIFXGFileFormatVersion1				kAIFXGFileFormatSuiteVersion1


/*******************************************************************************
**
**	Types
**
**/

/**
	Streaming interface to be supplied by the client, to be used when calling
	\c #AIFXGFileFormatSuite::ExportFXGToStream()
*/
struct AI140FXGWriteStreamInterface {
	/**
		Callback to client to open an asset.
		@param stream	[in] The stream pointer that the client has passed to \c #AIFXGFileFormatSuite::ExportFXGToStream()
		@param assetType [in] Type of asset See \c AIFXGAssetTypeEnum
		@param assetName		[in/out] Name of asset. Client can change the input name, so that the export plug-in can use the changed name.
		@param mimeType		[in] Mime type of asset
		@param createUnique	[in] True if the client should create a new file instead of overwriting existing one. Client should
								change the asset name accordingly with the new name.
		@return		\c #kCanceledErr if client does not want to receive further write and close calls for this particular open-asset call.
	*/
	AIAPI AIErr		(*BeginAsset)		(AI140FXGWriteStreamInterface* stream, ai::int16 assetType, ai::UnicodeString& assetName, const ai::UnicodeString& mimeType, AIBoolean createUnique);

	/**
		Callback to client to close an opened asset.
		@param stream	[in] The stream pointer that the client has passed to \c #AIFXGFileFormatSuite::ExportFXGToStream()
		@param	assetType	[in]	The asset type to close.
		@return \c #kNoErr on success
	*/
	AIAPI AIErr		(*EndAsset)			(AI140FXGWriteStreamInterface* stream, ai::int16 assetType);

	/**
		Callback to client to set the write position in current stream.
		@param stream	[in] The stream pointer that the client has passed to \c #AIFXGFileFormatSuite::ExportFXGToStream()
		@param pos	[in] The 0-based position to set.
		@return kNoErr on Success
	*/
	AIAPI AIErr		(*SetPos)			(AI140FXGWriteStreamInterface* stream, ai::uint32 pos);

	/**
		Callback to client to write bytes to current stream. (Note that this function returns
		a constant value, not an error code.)
		@param stream	[in] The stream pointer that the client has passed to \c #AIFXGFileFormatSuite::ExportFXGToStream()
		@param buffer [in] A buffer to write to current stream
		@param maxToWrite [in] The maximum number of bytes to write
		@return actual bytes written
	*/
	AIAPI size_t	(*WriteBytes)		(AI140FXGWriteStreamInterface* stream, const ASUInt8* buffer, const size_t  maxToWrite);

	/**
		Callback for client to report whether it supports positionable stream interface.
		(Note that this function returns a constant value, not an error code.)
		@param stream	[in] The stream pointer that the client has passed to \c #AIFXGFileFormatSuite::ExportFXGToStream()
		@return True if current stream is positionable, false otherwise.
	*/
	AIAPI AIBoolean (*IsPositionable)	(AI140FXGWriteStreamInterface* stream);

	/**
		Callback to report the current position of the current stream. (Note that this function returns
		a constant value, not an error code.)
		@param stream	[in] The stream pointer that the client has passed to \c #AIFXGFileFormatSuite::ExportFXGToStream()
		@return The current position of current stream.
	*/
	AIAPI ai::uint32	(*GetCurPos)		(AI140FXGWriteStreamInterface* stream);

	/**
		Callback to determine the appropriate expand setting for an art object.
		If client returns \c #kAIFXGExpandArtOptionExpand, it must fill \c expandFlags; see \c #AIExpandSuite::Expand() for flags,
		(Note that this function returns a constant value, not an error code.)
		@param stream	[in] The stream pointer that the client has passed to \c #AIFXGFileFormatSuite::ExportFXGToStream()
		@param art [in]	The art for which an expand setting is needed.
		@param expandFlag [out] The expand flags setting when \c #kAIFXGExpandArtOptionExpand is returned.
		@return One of the values of  \c #AIFXGExpandArtOptionEnum, \c #kAIFXGExpandArtOptionNone for default processing.
	*/
	AIAPI ai::int16		(*GetExpandOptionForArt) (AI140FXGWriteStreamInterface* stream, AIArtHandle art, ai::int32* expandFlags);

	/**
		Callback to report whether client wants private data generation for an art object.
		If not, application private data corresponding to the art is not written.
		 (Note that this function returns a constant value, not an error code.)
		@param stream	[in] The stream pointer which the client has passed to AIFXGFileFormatSuite::ExportFXGToStream
		@param art [in]	The art for which private data should be generated.
		@return True if client wants private data generation for this particular art, false otherwise.
	*/
	AIAPI AIBoolean (*GeneratePrivateDataForArt)(AI140FXGWriteStreamInterface* stream, AIArtHandle art);

	/**
		Callback to retrieve the filepath/name of the current stream
		@param stream	[in] The stream pointer that the client has passed to \c #AIFXGFileFormatSuite::ExportFXGToStream()
		@param pulicID [out] The filepath/name of the current stream. This is used in open-asset calls.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr		(*GetPublicID)		(AI140FXGWriteStreamInterface* stream, ai::UnicodeString& publicID);

	/**
		Callback to retrieve the relative Image folder path, so that the \c BitmapGraphic FXG tag can create the
		proper relative path of the image source. For example, if client returns the path "MyFile.assets/images" and the image file name is MyImage.png,
		the entry in the \c BitmapGrapic tag is source="\@Embed('MyFile.assets/images/MyImage.png')".
		@param stream	[in] The stream pointer that the client has passed to \c #AIFXGFileFormatSuite::ExportFXGToStream()
		@param relImageFolderPath [out] The relative path to the image folder.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr		(*GetRelativeImageFolderPath) (AI140FXGWriteStreamInterface* stream, ai::UnicodeString& relImageFolderPath);

	/**
		Callback to move or copy images in an Artboard-specific folder when a particular artboard is exported.
		@param stream	[in] The stream pointer that the client has passed to \c #AIFXGFileFormatSuite::ExportFXGToStream()
		@param imageName [in] The name of the image to be moved or copied.
		@param relImagePath [in] Relative path to image folder where the image should be moved or copied so that the FXG is valid.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr		(*LinkImageIntoAssetFolder)(AI140FXGWriteStreamInterface* stream, const ai::UnicodeString& imageName, const ai::UnicodeString& relImagePath);

	/** Internal */
	AIAPI AIErr		(*DeleteAutoGeneratedImage)(AI140FXGWriteStreamInterface* stream,const ai::UnicodeString& imageName);
}
/**
Stream interface to be passed to \c #AIFXGFileFormatSuite::ExportFXGToStream()
*/
;

/*******************************************************************************
**
**	Suite
**
**/

/** @ingroup Suites
This suite provides functions that allow you to export an AI document or art object to FXG.

\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
\c #kAIFXGFileFormatSuite and \c #kAIFXGFileFormatVersion.
*/
struct AI140FXGFileFormatSuite{
	/**
		Creates an FXG save-options object with default values. This should be freed when no longer needed,
		using \c #DisposeFXGSaveParams()
		@param fxgSaveParams [out] Save options with default values.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*CreateFXGSaveParams) ( AIFXGFileFormatSaveParams* fxgSaveParams );

	/**
		Destroys the FXG save-options object created with \c #CreateFXGSaveParams()
		@param fxgSaveParams [in] The save-options object.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*DisposeFXGSaveParams) ( AIFXGFileFormatSaveParams fxgSaveParams );

	/**
		Retrieves the current FXG version value from an FXG save-options object.
		(Note that this function returns a constant value, not an error code.)
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@return The FXG version, an \c #AIFXGVersion value.
	*/
	AIAPI ai::int16 (*GetFXGSaveVersion) (AIFXGFileFormatSaveParams fxgSaveParams);

	/**
		Sets the FXG save version value in an FXG save-options object.
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@param fxgVersion [in] The FXG version, an \c #AIFXGVersion value.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*SetFXGSaveVersion) (AIFXGFileFormatSaveParams fxgSaveParams, ai::int16 fxgVersion);

	/**
		Retrieves the current "Preserve AI Editing capabilities" flag value from an FXG save-options object.
		(Note that this function returns a constant value, not an error code.)
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@return True if AI editing capabilities should be preserved using application private data.
	*/
	AIAPI AIBoolean (*GetFXGSavePreserveAIEditCapability) (AIFXGFileFormatSaveParams fxgSaveParams);

	/**
		Sets the "Preserve AI Editing capabilities" flag in an FXG save-options object.
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@param aiEditCap [in] true if editing capabilities should be preserved, false other wise.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*SetFXGSavePreserveAIEditCapability) (AIFXGFileFormatSaveParams fxgSaveParams, AIBoolean aiEditCap);

	/**
		Retrieves the current preserve policy for Text from an FXG save-options object.
		(Note that this function returns a constant value, not an error code.)
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@return  The preserve policy for Text, an \c #AIFXGPreservePolicy value.
	*/
	AIAPI ai::int16 (*GetFXGSaveTextPolicy) (const AIFXGFileFormatSaveParams fxgSaveParams);

	/**
		Sets the preserve policy for Text in an FXG save-options object.
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@param fxgTextPreservePolicy [in] The preserve policy for Text, an \c #AIFXGPreservePolicy value.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*SetFXGSaveTextPolicy) (AIFXGFileFormatSaveParams fxgSaveParams, ai::int16 fxgTextPreservePolicy);

	/**
		Retrieves the current preserve policy for FXG Filters from an FXG save-options object.
		(Note that this function returns a constant value, not an error code.)
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@return  The preserve policy for FXG Filters, an \c #AIFXGPreservePolicy value.
	*/
	AIAPI ai::int16 (*GetFXGSaveFilterPolicy) (AIFXGFileFormatSaveParams fxgSaveParams);

	/**
		Sets the preserve policy for FXG Filters in an FXG save-options object.
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@param fxgFilterPreservePolicy [in] The preserve policy for FXG Filters, an \c #AIFXGPreservePolicy value.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*SetFXGSaveFilterPolicy) (AIFXGFileFormatSaveParams fxgSaveParams, ai::int16 fxgFilterPreservePolicy);

	/**
		Retrieves the current preserve policy for Gradients from an FXG save-options object.
		(Note that this function returns
		a constant value, not an error code.)
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@return The preserve policy for Gradients, an \c #AIFXGPreservePolicy value.
	*/
	AIAPI ai::int16 (*GetFXGSaveGradientPolicy) (AIFXGFileFormatSaveParams fxgSaveParams);

	/**
		Sets the preserve policy for Gradients in an FXG save-options object.
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@param fxgFilterPreservePolicy [in] The preserve policy for Gradients, an \c #AIFXGPreservePolicy value.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*SetFXGSaveGradientPolicy) (AIFXGFileFormatSaveParams fxgSaveParams, ai::int16 fxgGradientPreservePolicy);

	/**
		Retrieves the "Include Symbols" flag from an FXG save-options object.
		(Note that this function returns a constant value, not an error code.)
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@return True if All Symbols should be written in FXG, whether they are used or not.
	*/
	AIAPI AIBoolean (*GetFXGSaveIncludeSymbol) (AIFXGFileFormatSaveParams fxgSaveParams);

	/**
		Sets the "Include Symbols" flag in an FXG save-options object.
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@param aiIncludeSymbol [in] True if all symbols should be exported, false if only used symbols should be exported
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*SetFXGSaveIncludeSymbol) (AIFXGFileFormatSaveParams fxgSaveParams, AIBoolean aiIncludeSymbol);

	/**
		Retrieves the "Include XMP" flag from an FXG save-options object.
		(Note that this function returns a constant value, not an error code.)
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@return True if XMP should be written in FXG,
	*/
	AIAPI AIBoolean (*GetFXGSaveIncludeXMP) (AIFXGFileFormatSaveParams fxgSaveParams);

	/**
		Sets the "Include Symbols" flag in an FXG save-options object.
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@param aiIncludeXMP [in] True if XMP  should be exported.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*SetFXGSaveIncludeXMP) (AIFXGFileFormatSaveParams fxgSaveParams, AIBoolean aiIncludeXMP);

	/**
		Retrieves the rasterize resolution from an FXG save-options object.
		(Note that this function returns a constant value, not an error code.)
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@param outCustomResolution [out] A custom resolution value if the returned value is \c #kAIFXGResolutionCustom
		@return The rasterize resolution, an \c #AIFXGRasterizeResolution value.
	*/
	AIAPI ai::int16 (*GetFXGSaveRasterizeResolution) (AIFXGFileFormatSaveParams fxgSaveParams, ai::int32* outCustomResolution);

	/**
		Sets the rasterize resolution in an FXG save-options object.
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@param fxgRasterizeResolution [in] The rasterize resolution, an \c #AIFXGRasterizeResolution value.
		@param customResolution [in] A custom resolution if the resolution value is \c #kAIFXGResolutionCustom
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*SetFXGSaveRasterizeResolution) (AIFXGFileFormatSaveParams fxgSaveParams,
		ai::int16 fxgRasterizeResolution, ai::int32 customResolution);

	/**
		Retrieves the "Downsample Linked Images" flag from an FXG save-options object.
		(Note that this function returns a constant value, not an error code.)
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@return True if linked images should be downsampled to 72 ppi, false otherwise.
	*/
	AIAPI AIBoolean (*GetFXGSaveDownsampleLinkedImages) (AIFXGFileFormatSaveParams fxgSaveParams);

	/**
		Sets the "Downsample Linked Images" flag in an FXG save-options object.
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@param aiDownSampleLinkedImages [in] True if Linked images should be downsampled to 72 ppi, false otherwise.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*SetFXGSaveDownsampleLinkedImages) (AIFXGFileFormatSaveParams fxgSaveParams,  AIBoolean aiDownSampleLinkedImages);

	/**
		Retrieves the "Clip To Active Artboard" flag from an FXG save-options object.
		(Note that this function returns a constant value, not an error code.)
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@return True if exported FXG file should be clipped to active artboard, false otherwise.
	*/
	AIAPI AIBoolean (*GetFXGSaveClipToActiveArtboard) (AIFXGFileFormatSaveParams fxgSaveParams);

	/**
		Sets the "Clip To Active Artboard" flag in an FXG save-options object.
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@param fxgClipToActiveArtboard [in] True if exported FXG file should be clipped to active artboard, false otherwise.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*SetFXGSaveClipToActiveArtboard) (AIFXGFileFormatSaveParams fxgSaveParams,  AIBoolean fxgClipToActiveArtboard);

	/**
		Retrieves the "WriteImages" flag from an FXG save-options object.
		(Note that this function returns a constant value, not an error code.)
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@return True if images should also be written while exporting FXG. If false, images are not written, which is useful
			when user is interested in only the XML code.
	*/
	AIAPI AIBoolean (*GetFXGSaveWriteImages) (AIFXGFileFormatSaveParams fxgSaveParams);

	/**
		Sets the "WriteImages" flag in an FXG save-options object.
		@param fxgSaveParams [in] A save-options object as returned by  \c #CreateFXGSaveParams().
		@param writeImages [in] True if images should be written while exporting FXG, false otherwise.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*SetFXGSaveWriteImages) (AIFXGFileFormatSaveParams fxgSaveParams, AIBoolean writeImages);

	/**
		Generates FXG to a file.
		@param art [in] Art which you want to export as FXG. Pass NULL to generate FXG for entire document.
		@param filepath [in] The file path for the master document FXG
		@param fxgSaveParams [in] The FXG save options parameters. See \c #AIFXGFileFormatSaveParams
		@param fxgExportFlags [in]  The export flags. See \c #AIFXGExportFlagEnum
		@param artBoardRange [in] If the export flag \c #kAIFXGExportFlagArtboards is passed, the artboard range.
		@param customProgressText [in] An optional message to display in the progress bar. If NULL, a default message is displayed.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*ExportFXGToFile) (AIArtHandle art, const ai::FilePath& filePath, AIFXGFileFormatSaveParams fxgSaveParams, ai::int32 fxgExportFlags, const ai::UnicodeString& artBoardRange, const ai::UnicodeString& customProgressText);

	/**
		Generates FXG to a stream through callbacks.
		@param art [in] The art which you want to export as FXG. Pass NULL to generate FXG for entire document.
		@param streamInterface [in] The stream implemenation with callbacks, See \c #AIFXGWriteStreamInterface
		@param fxgSaveParams [in]  The FXG save options parameters. See \c #AIFXGFileFormatSaveParams
		@param fxgExportFlags [in]  The export flags. See \c #AIFXGExportFlagEnum
		@param artBoardRange [in]  If the export flag \c #kAIFXGExportFlagArtboards is passed, the artboard range.
		@param customProgressText [in] An optional message to display in the progress bar. If NULL, a default message is displayed.
		@return \c #kNoErr on success.
	*/
	AIAPI AIErr (*ExportFXGToStream) (AIArtHandle art, AI140FXGWriteStreamInterface* streamInterface, AIFXGFileFormatSaveParams fxgSaveParams, ai::int32 fxgExportFlags, const ai::UnicodeString& artBoardRange);

} ;


#include "AIHeaderEnd.h"



#endif //__AI140FXGFileFormat__
