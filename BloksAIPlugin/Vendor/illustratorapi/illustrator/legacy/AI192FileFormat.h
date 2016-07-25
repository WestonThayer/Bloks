#ifndef __AI192FileFormat__
#define __AI192FileFormat__

/*
 *        Name:	AI192FileFormat.h
 *   $Revision: 25 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator File Format Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2014 Adobe Systems Incorporated.
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
#include "AIFileFormat.h"

#include "AIHeaderBegin.h"

/** @file AI192FileFormat.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/
#define kAI192FileFormatSuite				"AI File Format Suite"
#define kAI192FileFormatSuiteVersion13		AIAPI_VERSION(13)
#define kAI192FileFormatSuiteVersion		kAI192FileFormatSuiteVersion13
#define kAI192FileFormatVersion				kAI192FileFormatSuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/

/**	@ingroup Suites
	This suite provides functions for creating and managing file-format plug-ins,
	which extend the number of file formats that Illustrator can read and write.

	Reading a format can be transparent to the user; when a file of the
	defined type is selected in the Open dialog, your file format plug-in
	creates artwork in the Illustrator document. If there is a plug-in that writes
	a file format, that format appears in the Save As dialog as an option for the user
	to select. If it is selected, the plug-in walks the artwork tree and writes out
	information on the artwork in the appropriate manner. If your plug-in needs more
	parameters for either reading or writing, it defines a modal dialog to interact
	with the user.

	Plug-ins tell Illustrator about the file formats they
	support by specifying platform file information: the type (such as \c 'ART3')
	in Mac OS, or the extension (such as \c '.AI') in Windows. Plug-ins also indicate
	what read/write capabilities they support.

	One plug-in can register multiple formats. Illustrator handles some parts of the
	file I/O process, and the plug-in does the rest.

	A file-format plug-in receives message actions telling it to:

	\li Check if a file can be read, The Check selector is sent only to plug-ins
		that can read files. It extends the simple type checking done by the  Open dialog.
	\li Ask for parameters.  This selector can be ignored if the plug-in does not need
		user input.
	\li Go. In response, your plug-in executes the read or write operation.

	If a file format plug-in can read, files of its registered file type appear
	in the file list of the Open dialog. In addition to screening by file type,
	Illustrator sends a selector giving a plug-in a chance to check that the
	file can be read. This is useful in the case of text files or files from a
	different file system. If more than one format matches the type, Illustrator
	determines which plug-in should actually open the file, asking the user if necessary.

	If a file format plug-in supports both reading and writing, when reading it should
	store any information about the file needed to write the file back to disk. It can
	store data (for example, the pixel depth of an EPS preview) in the plug-ins globals,
	or in a parameter block. The reference to a block should be attached to the document
	using \c #AIDocumentSuite::SetDocumentFileFormatParameters(). Illustrator keeps this
	parameter-block reference with the document. The plug-in can retrieve it when the
	document is being saved.

	When the user does a Save, by default Illustrator uses the same file format that was
	used to read the file. If the file format does not support writing, the Save As
	dialog appears to let the user choose the save format. All file format plug-ins
	that support saving appear in the format menu of this dialog.

	If you need information from the user to open or save a file, you can present a
	dialog when the ask-for-parameters message is received. When saving files, this
	will be after the Save As dialog has appeared. Your plug-in should save the
	information it collects, keeping it with the document to use for later saves.

	When the go message is received, file formats that read files typically parse
	the input file and create Illustrator artwork using API calls. File formats for
	saving Illustrator artwork traverse the artwork database and write out all
	pertinent information.

	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAI192FileFormatSuite and \c #kAI192FileFormatVersion.

*/
struct AI192FileFormatSuite {

	/** Adds a file format to the standard file dialog.
		Call during startup to install a plug-in file format.
			@param self	A reference to this plug-in, which adds the format.
			@param name	The unique name of the new file format. You can use
				your company name with a descriptor to make it unique.
				Not displayed or localized.
			@param data	Information about the file format.
			@param options File format operations that this plug-in supports.
				A logical OR of these \c #AIFileFormatOptions values:
				\verbatim
kFileFormatRead
kFileFormatImportArt
kFileFormatExport
kFileFormatExportSelection
kFileFormatPlaceArt
kFileFormatImportStyles
kFileFormatSuppliesPrintRecordOption
kFileFormatIsDefaultOption
kFileFormatConvertTemplate
kFileFormatLinkArt
kFileFormatWrite
kFileFormatNoAutoCheckFormat
kFileFormatSkipStartupObjectsOption
kFileFormatHasExtendedData
kFileFormatSuppressUI
kFileFormatCheckAlways
\endverbatim
			@param fileFormat [out] A buffer in which to return  the handle of
				the new plug-in file format. If you install multiple file formats,
				store this reference in the plug-ins \c globals record, so that your
				plug-in can use it to determine which file format command is to be processed.
				@param extendedOptions File format extended operations that this plug-in supports. A logical OR of these \c #AIFFExtendedOptions values:                        
				\verbatim
				kNoExtendedOptions
				kSaveMultiArtboards
				kFileFormatPlaceInTouch
				\endverbatim


			@see \c #AddFileFormatEx()
	*/
	AIAPI AIErr (*AddFileFormat) ( SPPluginRef self, const char *name,
				PlatformAddFileFormatData *data, ai::int32 options, AIFileFormatHandle *fileFormat ,  ai::int32 extendedOptions);

	/** Retrieves the name of a file format.
			@param fileFormat The file format.
			@param name [out] A buffer in which to return the name string, as
				passed to \c #AddFileFormat(). Do not modify this string.
		*/
	AIAPI AIErr (*GetFileFormatName) ( AIFileFormatHandle fileFormat, char **name );

	/** Retrieves the option flags of a file format.
			@param fileFormat The file format.
			@param options [out] A buffer in which to return the options, a logical OR of
				\c #AIFileFormatOptions values
		*/
	AIAPI AIErr (*GetFileFormatOptions) ( AIFileFormatHandle fileFormat, ai::int32 *options );

	/** Sets the option flags of a file format, which specify what file operations can be handled.
			 @param fileFormat The file format.
			 @param options The options, a logical OR of \c #AIFileFormatOptions values
	*/
	AIAPI AIErr (*SetFileFormatOptions) ( AIFileFormatHandle fileFormat, ai::int32 options );

	/** Retrieves a reference to the plug-in that installed a file format,
		to be passed to \c #AIPluginSuite functions.
			@param fileFormat The file format.
			@param plugin [out] A buffer in which to return the plug-in reference.
		*/
	AIAPI AIErr (*GetFileFormatPlugin) ( AIFileFormatHandle fileFormat,
				SPPluginRef *plugin );

	/** Gets the number of installed plug-in file formats.
		Use with \c #GetNthFileFormat() to iterate through all plug-in formats.
			@param count [out] A buffer in which to return the number of formats.
		*/
	AIAPI AIErr (*CountFileFormats) ( ai::int32 *count );

	/** Retrieves a plug-in file format reference by position index.
		Use with \c #CountFileFormats() to iterate through all installed formats.
			@param n The index, in the range <code>[1..numFormats]</code>.
			@param fileFormat [out] A buffer in which to return the file format reference.

		*/
	AIAPI AIErr (*GetNthFileFormat) ( ai::int32 n, AIFileFormatHandle *fileFormat );

	/** Retrieves the file extension for a plug-in file format.
			@param fileFormat The file format.
			@param extension [out] A buffer in which to return the file extension string.
		*/
	AIAPI AIErr (*GetFileFormatExtension) ( AIFileFormatHandle fileFormat, char *extension );

	/** Adds a plug-in file format. This extended version allows you to specify
		a list of Mac OS file types. Call during startup to install a plug-in file format.
			@param self	A reference to this plug-in, which adds the format.
			@param name	The unique name of the new file format. You can use
				your company name with a descriptor to make it unique.
				Not displayed or localized.
			@param dataEx	Information about the file format. This extended version
				uses a data structure with additional fields that allow you to
				specify a list of Mac OS file types. Use \c #SetFileFormatFilter()
				to specify a creator/type pair as the file filter.
			@param options File format operations that this plug-in supports.
				A logical OR of \c #AIFileFormatOptions values.
				When the format is called with a Go selector,
				one of these flags is set in the \c option field to indicate the
				requested operation.
			@param fileFormat [out] A buffer in which to return  the handle of
				the new plug-in file format. If you install multiple file formats,
				store this reference in the plug-ins \c globals record, so that your
				plug-in can use it to determine which file format command is to be processed.
				@param extendedOptions File format extended operations that this plug-in supports. A logical OR of these \c #AIFFExtendedOptions values:                        
				\verbatim
				kNoExtendedOptions
				kSaveMultiArtboards
				kFileFormatPlaceInTouch
				\endverbatim
				
			@see \c #AddFileFormat(), \c #SetFileFormatFilter()
		*/
	AIAPI AIErr (*AddFileFormatEx) ( SPPluginRef self, const char *name,
				PlatformAddFileFormatExData *dataEx, ai::int32 options, AIFileFormatHandle *fileFormat, ai::int32 extendedOptions );

	/** Retrieves the localizable display name of a plug-in file format.
			@param fileFormat The file format.
			@param szTitle [out] A buffer in which to return the display name.
		*/
	AIAPI AIErr (*GetFileFormatTitle) ( AIFileFormatHandle fileFormat, char *szTitle );

	/** Retrieves the Mac OS file types for a plug-in file format.
			@param fileFormat The file format.
			@param maxNumTypes [in, out] A buffer in which to specify the maximum number
				and return the actual number of values in \c typeList.
			@param typeList [out] A buffer in which to return the 4-character Mac OS type codes.
			@see \c #GetFileFormatCreatorType()	to get the full Mac OS file information.
		*/
	AIAPI AIErr (*GetFileFormatType) ( AIFileFormatHandle fileFormat, ai::int32 *maxNumTypes, ai::int32 *typeList );

	/** Associates a file format with a file type filter. File types are specified by (creator, type)
		pairs in Mac OS, and by filename extensions in Windows.
		@note This function extends the \c #AddFileFormat() and \c #AddFileFormatEx() functions
		by allowing filters based on (creator, type) pairs in Mac OS, rather than simple type values.
			@param fileFormat The file format.
			@param numPairs In Mac OS, the number of (creator, type) pairs specified in \c pairList.
				Ignored in Windows.
			@param pairList In Mac OS, a pointer to an array of (creator, type) pairs. These can use
				the Mac OS wild-card value '****' for creator or type. Ignored in Windows.
			@param extensions In Windows, a comma-delimited list of DOS-style extensions that
				are filtered in the Open dialog, or appended to the file name in the
				Saves As dialog. For example, \c "ai,eps".
		*/
	AIAPI AIErr (*SetFileFormatFilter) ( AIFileFormatHandle fileFormat, ai::int32 numPairs, AICreatorTypePair *pairList, const char* extensions );

	/** Retrieves the file type filter for a file format, as specified by (creator, type)
		pairs for Mac OS.
			@param fileFormat The file format.
			@param maxNumTypes [in, out] A buffer in which to specify the maximum number
				and return the actual number of (creator, type) pairs specified in \c pairList.
			@param pairList [out] A buffer in which to return the array of (creator, type) pairs.
		*/
	AIAPI AIErr (*GetFileFormatCreatorType) ( AIFileFormatHandle fileFormat, ai::int32 *maxNumPairs, AICreatorTypePair *pairList );

	/** Invokes the File > Save dialog, allowing you to filter the available file formats.
			@param options Limits available file formats to those that support these
				write operations. A logical OR of write operation constants:<br>
				\c #kFileFormatExport<<br>
				\c #kFileFormatWrite
			@param dlgTitle	The title for the Save dialog.
			@param fileSpec	[in, out] A buffer in which to pass the initial file specification
				and return the user-chosen specification.
			@param fileFormat [out] A buffer in which to return the user-chosen file format.
			@param good	[out] A buffer in which to return true if the user clicked Save,
				or false if the user clicked Cancel.
	  */
	AIAPI AIErr (*PutFile) (ai::int32 options, const unsigned char *dlgTitle, ai::FilePath &fileSpec, AIFileFormatHandle *fileFormat, AIBoolean *good );

	/** Sets the priority of a file format. which determines the order in which Illustrator
		searches through formats in deciding which one to use to open a file. The first format
		found that handles a file type is used to open the file.
			@param fileFormat The file format.
			@param priority The new priority, an \c #AIFileFormatPriority value,
		*/
	AIAPI AIErr (*SetFileFormatPriority) ( AIFileFormatHandle fileFormat, ai::int32 priority );

	/** Finds all plug-in file formats that can perform a specified operation for a file.
			@param options The operation, a \c #AIFileFormatOptions value.
			@param file	The file.
			@param maxMatches The maximum number of formats to return.
			@param matchingFormats [out] An array of size \c maxMatches in which to return the matching file formats.
			@param numMatches [out] A buffer in which to return the number of matching file formats found.
		*/
	AIAPI AIErr (*FindMatchingFileFormats) ( ai::int32 options, const ai::FilePath &file, ai::int32 maxMatches, AIFileFormatHandle matchingFormats[], ai::int32* numMatches );

	/** Obsolete */
	AIAPI AIErr (*ResolveImportConflicts) ();

	/** Reports the version of Illustrator in which a raster file
		format, for example the JPEG file format plug-in, was converted from
		using raster art to using placed art in order to perform a place link
		operation. The information is needed so that Illustrator knows when it
		should convert placed linked art back to raster art when saving to a
		legacy file format. For example, if the JPEG file format used raster art
		in version 10 and started using placed art in version 11 then
		Illustrator must convert placed linked JPEG images back to raster art
		when saving to a version 10 or earlier Illustrator file.
		(Note that this function returns a version value, not an error code.)
			@param fileFormat The file format.
			@return The Illustrator version. The default version is 0,
				meaning that placed objects are not converted on export.
			@see \c #SetFirstVersionUsingPlacedArt() to set the version.
		*/
	AIAPI AIVersion (*GetFirstVersionUsingPlacedArt) (AIFileFormatHandle fileFormat);

	/** Sets the version of Illustrator in which a raster file
		format was converted from using raster art to using placed art
		in order to perform a place link operation.
			@param fileFormat The file format.
			@param The Illustrator version value. The default version is 0,
				meaning that placed objects are not converted on export.
			@see \c #GetFirstVersionUsingPlacedArt().
		*/
	AIAPI AIErr (*SetFirstVersionUsingPlacedArt) (AIFileFormatHandle fileFormat, AIVersion version);

	/** Retrieves the Illustrator startup profile type from the XMP metadata embedded in a file.
			@param file  The file path.
			@param docStartupProfile [out] A buffer in which to return the Illustrator
				startup profile constant.  If the information is not in the metadata,
				or if the file does not contain XMP metadata, this is \c #kAIStartupProfileUnknown.
			@return  The error \c #kBadParameterErr if file is empty or does not exist.
		*/
	AIAPI AIErr (*GetFileStartupProfileType) (const ai::FilePath &file, AIDocumentStartupProfile *docStartupProfile);

	/** Retrieves the Illustrator default document profile from the startup-profile type.
			@param docStartupProfile The startup profile type.
			@param profile [out] A buffer in which to return the file-path object for the default document profile.
			@return	The error \c #kCantHappenErr if the file does not exists. <br>
					The error \c #kBadParameterErr if the startup profile is invalid,
	*/
	AIAPI AIErr (*GetStartupFileOfType) (const AIDocumentStartupProfile docStartupProfile, ai::FilePath &profile);

	/** Retrieves the extended option flags of a file format.
		@param fileFormat The file format.
		@param extendedOptions [out] A buffer in which to return the extended options
		\c #AIFFExtendedOptions values
			\verbatim
			kNoExtendedOptions
			kSaveMultiArtboards
			kFileFormatPlaceInTouch
			\endverbatim
	*/
	AIAPI AIErr (*GetFileFormatExtendedOptions) ( AIFileFormatHandle fileFormat, ai::int32 *extendedOptions );

	/** Sets the extended option flags of a file format, which specify what file operations can be handled.
		@param fileFormat The file format.
		@param extendedOptions File format operations that this plug-in supports. A logical OR of these 
		\c #AIFFExtendedOptions values:                        
			\verbatim
			kNoExtendedOptions
			kSaveMultiArtboards
			kFileFormatPlaceInTouch
			\endverbatim
	*/
	AIAPI AIErr (*SetFileFormatExtendedOptions) ( AIFileFormatHandle fileFormat, ai::int32 extendedOptions);
} ;

#include "AIHeaderEnd.h"

#endif
