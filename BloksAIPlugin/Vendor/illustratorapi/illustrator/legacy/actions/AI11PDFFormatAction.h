#ifndef _AIPDFFORMATACTION_H_
#define _AIPDFFORMATACTION_H_

/*
 *        Name:	AIPDFFormatAction.h
 *   $Revision: 1 $
 *      Author:	Hiromi M. Watanabe
 *        Date:	7/24/2002  
 *     Purpose:	Adobe Illustrator 11.0 PDF Action Parameters.
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


// -----------------------------------------------------------------------------
//	Types.
// -----------------------------------------------------------------------------

// option set
typedef enum _AIPDFOptionSet 
{ 
	kAIPDFOptionSetCustom  = 0

} AIPDFOptionSet;


typedef enum _AIPDFFlattenStyle
{ 
	kAIPDFFlattenStyleCustom  = 0

} AIPDFFlattenStyle;



// compatibility
typedef enum _AIPDFCompatibility 
{ 
	kAIPDFCompatibility13  = 0x0013, // Acrobat 4, PDF 1.3
	kAIPDFCompatibility14  = 0x0014,  // Acrobat 5, PDF 1.4
	kAIPDFCompatibility15  = 0x0015  // Acrobat 6, PDF 1.5

} AIPDFCompatibility;


// color image compression
typedef enum _AIPDFImageCompression 
{ 
	kAIPDFImageNoCompression = 0,
	kAIPDFImageCompressionAutomaticJPEGMinimum,
	kAIPDFImageCompressionAutomaticJPEGLow,
	kAIPDFImageCompressionAutomaticJPEGMedium,
	kAIPDFImageCompressionAutomaticJPEGHigh,
	kAIPDFImageCompressionAutomaticJPEGMaximum,
	kAIPDFImageCompressionJPEGMinimum,
	kAIPDFImageCompressionJPEGLow,
	kAIPDFImageCompressionJPEGMedium,
	kAIPDFImageCompressionJPEGHigh,
	kAIPDFImageCompressionJPEGMaximum,
	kAIPDFImageCompressionAutomaticJPEG2000Minimum,
	kAIPDFImageCompressionAutomaticJPEG2000Low,
	kAIPDFImageCompressionAutomaticJPEG2000Medium,
	kAIPDFImageCompressionAutomaticJPEG2000High,
	kAIPDFImageCompressionAutomaticJPEG2000Maximum,
	kAIPDFImageCompressionAutomaticJPEG2000Lossless,
	kAIPDFImageCompressionJPEG2000Minimum,
	kAIPDFImageCompressionJPEG2000Low,
	kAIPDFImageCompressionJPEG2000Medium,
	kAIPDFImageCompressionJPEG2000High,
	kAIPDFImageCompressionJPEG2000Maximum,
	kAIPDFImageCompressionJPEG2000Lossless,
	kAIPDFImageCompressionZIP8bit,
	kAIPDFImageCompressionZIP4bit

} AIPDFImageCompression;



// monochrome image compression
typedef enum _AIPDFMonochromeImageCompression 
{ 
	kAIPDFMonochromeImageNoCompression = 0,
	kAIPDFMonochromeImageCompressionCCITTG3,
	kAIPDFMonochromeImageCompressionCCITTG4,
	kAIPDFMonochromeImageCompressionZIP,
	kAIPDFMonochromeImageCompressionRunLength

} AIPDFMonochromeImageCompression;



// downsampling kind
typedef enum _AIPDFDownsampling
{
	kAIPDFNoDownsampling = 1,
	kAIPDFAverageDownsampling,
	kAIPDFSubsampling,
	kAIPDFBicubicsampling

} AIPDFDownsampling;


typedef enum _AIPDFEncryptionLevel
{
	kAIPDF40bitEncryption = 1,
	kAIPDF128bitEncryption 

} AIPDFEncryptionLevel;

typedef enum _AIPDFOverprintOptions
{
	kAIPDFOPPreserve = 1,
	kAIPDFOPDiscard

} AIPDFOverprintOptions;


typedef enum _AIPDFPrinterType
{
	kAIPDFPrintMarksStandard = 1,
	kAIPDFPrintMarksJapanese

} AIPDFPrinterType;

typedef enum _AIPDFPrinterMarkWeight
{
	kAIPDFPrintMarksWeight0125 = 1,
	kAIPDFPrintMarksWeight025,
	kAIPDFPrintMarksWeight05

} AIPDFPrinterMarkWeight;


typedef enum _AIPDFPrintingPermit
{
	kAIPDFPrint128NoneIndex = 1,
	kAIPDFPrint128LowResIndex,
	kAIPDFPrint128HighResIndex,
	kAIPDFPrint40NoneIndex,
	kAIPDFPrint40HighResIndex

} AIPDFPrintingPermit;

typedef enum _AIPDFChangesPermit
{
	kAIPDFChanges128NoneIndex = 1,
	kAIPDFChanges128EditPageIndex,
	kAIPDFChanges128FillFormIndex,
	kAIPDFChanges128CommentIndex,
	kAIPDFChanges128AnyIndex,
	kAIPDFChanges40NoneIndex,
	kAIPDFChanges40CommentIndex,
	kAIPDFChanges40PageLayoutIndex,
	kAIPDFChanges40AnyIndex

} AIPDFChangesPermit;


// -----------------------------------------------------------------------------
// Action: kAIExportDocumentAction
// Purpose: These are additional parameters for export to PDF
// Parameters:
//	The following parameters are standard to the export action 
//	- kAIExportDocumentNameKey, string: the file name to export as.
//	- kAIExportDocumentFormatKey, string:
//			kAIPDFFileFormat to export PDF
//	- kAIExportDocumentExtensionKey, string:
//			kAIPDFFileFormatExtension
// file format and extensions for saving as an uncompressed SVG file.
#define kAIPDFFileFormat									"PDF File Format"
#define kAIPDFFileFormatExtension							"pdf"


const ActionParamKeyID kAIPDFPageIndexKey					= 'page'; // integer, page index
const ActionParamKeyID kAIPDFCropToKey						= 'crop'; // enum, AIPDFCropTo
const ActionParamKeyID kAIPDFPageCountKey					= 'pgct'; // integer, page count

const ActionParamKeyID kAIPDFOptionSetKey					= 'optn'; // integer, option set index.  
const ActionParamKeyID kAIPDFOptionSetNameKey				= 'opnm'; // string, option set entry name

const ActionParamKeyID kAIPDFCompatibilityKey				= 'comp'; // enum AIPDFCompatibility, compatibility
const ActionParamKeyID kAIPDFRoundTripKey					= 'rdtr'; // bool, include round trip information, aka PGF
const ActionParamKeyID kAIPDFGenerateThumbnailsKey			= 'thum'; // bool, generate thumbnails
const ActionParamKeyID kAIPDFViewPDFFileKey					= 'vpdf'; // bool, view PDF file after saving
const ActionParamKeyID kAIPDFFastWebViewKey					= 'fwev'; // bool, optimize for fast web view

const ActionParamKeyID kAIPDFColorImageCompressionKindKey	= 'cknd'; // enum AIPDFImageCompression, color image compression kind
const ActionParamKeyID kAIPDFColorImageTileKey				= 'ctil'; // int, color image tile size
const ActionParamKeyID kAIPDFColorImageResampleKindKey		= 'crsl'; // enum, color image resample kind
const ActionParamKeyID kAIPDFColorImageResolutionKey		= 'cres'; // int, color image resolution (dpi)
const ActionParamKeyID kAIPDFColorImageResampleAboveKey		= 'crab'; // int, resample color image above resolution (dpi)

const ActionParamKeyID kAIPDFGrayscaleImageCompressionKindKey = 'gknd'; // enum AIPDFImageCompression, gray scale image compression kind
const ActionParamKeyID kAIPDFGrayscaleImageTileKey			= 'gtil'; // int, grayscale image tile size
const ActionParamKeyID kAIPDFGrayscaleImageResampleKindKey	= 'grsl'; // enum, grayscale image resample 
const ActionParamKeyID kAIPDFGrayscaleImageResolutionKey 	= 'gres'; // int, grayscale image resolution
const ActionParamKeyID kAIPDFGrayImageResampleAboveKey		= 'grab'; // int, resample grayscale image above resolution (dpi)

const ActionParamKeyID kAIPDFMonochromeImageCompressionKindKey 	= 'mknd'; // enum AIPDFMonochromeImageCompression, monochrome image kind
const ActionParamKeyID kAIPDFMonochromeImageResampleKindKey	= 'mrsl'; // enum, monochrome image resample
const ActionParamKeyID kAIPDFMonochromeImageResolutionKey	= 'mres'; // int, monochrome image resolution
const ActionParamKeyID kAIPDFMonochromeImageResampleAboveKey= 'mrab'; // int, resample monochrome image above resolution (dpi)

const ActionParamKeyID kAIPDFCompressArtKey					= 'cart'; // bool, compress art

const ActionParamKeyID kAIPDFTrimMarksKey					= 'ptrm'; // bool, Trim Marks
const ActionParamKeyID kAIPDFRegMarksKey					= 'preg'; // bool, Registration Marks
const ActionParamKeyID kAIPDFColorBarsKey					= 'pclb'; // bool, Color Bars
const ActionParamKeyID kAIPDFPageInfoKey					= 'ppgi'; // bool, Page Info
const ActionParamKeyID kAIPDFPrinterMarkTypeKey				= 'pmtp'; // enum, printer mark type
const ActionParamKeyID kAIPDFTrimMarkWeightKey				= 'ptmw'; // enum, Trim Marks weight
const ActionParamKeyID kAIPDFOffsetFromArtworkKey			= 'post'; // int, offset from artwork  
const ActionParamKeyID kAIPDFBleedTopKey					= 'btop'; // int, bleed top  
const ActionParamKeyID kAIPDFBleedBottomKey					= 'bbtm'; // int, bleed bottom  
const ActionParamKeyID kAIPDFBleedLeftKey					= 'blft'; // int, bleed left  
const ActionParamKeyID kAIPDFBleedRightKey					= 'brht'; // int, bleed right  
const ActionParamKeyID kAIPDFBleedLinkKey					= 'brht'; // bool, bleed link  

const ActionParamKeyID kAIPDFEmbedICCProfilesKey			= 'emic'; // bool, embed ICC profiles
const ActionParamKeyID kAIPDFEmbedFontsKey					= 'embd'; // bool, embed fonts  **TO BE REMOVED**
const ActionParamKeyID kAIPDFSubsetFontsKey					= 'sbst'; // bool, subset fonts **TO BE REMOVED**
const ActionParamKeyID kAIPDFSubsetFontsRatioKey			= 'rato'; // real, subset fonts ratio

const ActionParamKeyID kAIPDFGenerateAcrobatLayersKey		= 'aclr'; // bool, generate Acrobat layers
const ActionParamKeyID kAIPDFOverprintKey					= 'pvop'; // enum, overprint
const ActionParamKeyID kAIPDFFlatteningStyleKey 			= 'flsy'; // enum, AIPDFFlatteningStyle
const ActionParamKeyID kAIPDFFlatteningStyleNameKey 		= 'flsn'; // string, AIPDFFlatteningStyle

const ActionParamKeyID kAIPDFFlattenMaxResolutionKey		= 'fmax'; // real, flattening style max resolution
const ActionParamKeyID kAIPDFFlattenMinResolutionKey		= 'fmin'; // real, flattening style min resolution
const ActionParamKeyID kAIPDFFlattenVectorBalanceKey		= 'fvba'; // int, flattening style vector balance
const ActionParamKeyID kAIPDFFlattenClipComplexRegionsKey	= 'fccr'; // bool, flattening style clip complex regions
const ActionParamKeyID kAIPDFFlattenOutlineStrokesKey		= 'fosk'; // bool, flattening style outline strokes
const ActionParamKeyID kAIPDFFlattenOutlineTextKey			= 'fotx'; // bool, flattening style outline text
const ActionParamKeyID kAIPDFFlattenPrinterResolutionKey	= 'fprs'; // real, flattening style printer resolution

const ActionParamKeyID kAIPDFUserPasswordRequiredKey		= 'usrq'; // bool, user password 
const ActionParamKeyID kAIPDFUserPasswordKey				= 'usps'; // string, user password 
const ActionParamKeyID kAIPDFMasterPasswordRequiredKey		= 'msrq'; // bool, master password 
const ActionParamKeyID kAIPDFMasterPasswordKey				= 'msps'; // string, master password 

const ActionParamKeyID kAIPDFPrintingPermKey 				= 'pmpr'; // enum, Printing Allowed
const ActionParamKeyID kAIPDFChangesPermKey 				= 'pmch'; // enum, Changes Allowed
			
const ActionParamKeyID kAIPDFEnableCopyKey					= 'ebcp'; // bool, Enable copying  (128-bit) 
const ActionParamKeyID kAIPDFEnableAccessKey				= 'ebac'; // bool, Enable access  (128-bit)  
const ActionParamKeyID kAIPDFEnableCopyAccessKey			= 'ebca'; // bool, Enable copying and access  (40-bit) 
const ActionParamKeyID kAIPDFEnablePlaintextMetaKey			= 'ebpt'; // bool, Enable Plaintext Metadata

const ActionParamKeyID kAIPDFIncludeLinkedFilesKey			= 'link'; // bool, include linked files


#endif //_AIPDFFORMATACTION_H_
