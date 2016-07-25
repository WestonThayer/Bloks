#ifndef __AI140User__
#define __AI140User__

/*
*        Name: AI140User.h
*   $Revision: 15 $
*      Author:
*        Date:
*     Purpose: Adobe Illustrator User Utilities Suite.
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

#include "AIUser.h"

#include "AIHeaderBegin.h"

/** @file AI140User.h */


/*******************************************************************************
**
**	Constants
**
**/

// v.14.0
#define kAIUserSuite				"AI User Suite"
#define kAIUserSuiteVersion9		AIAPI_VERSION(9)
#define kAI140UserSuiteVersion			kAIUserSuiteVersion9
#define kAI140UserVersion				kAI140UserSuiteVersion

/*******************************************************************************
**
**	Types
**
**/

/** Information about the kinds of names allowed for a named entity (such as
layers, swatches, and styles). Used to generate a legal name, using
\c #AIUserSuite::NextName() and AIUserSuite::CopyOfName().

The following pseudocode indicates how you can create your own AutoNameGenerator class by publicly inheriting AIAutoNameGenerator
and following the implementation guidelines.

@code
class AutoNameGenerator : public AIAutoNameGenerator {
public:
// Constructor for a name generator. Its supplied with the pluginref in
// case the name generator needs to look in the plugin's resources e.g for
// the default name. The next new name index is supplied since the plugin
// probably needs to store this in its globals so that it can be preserved
// across unload and reload.
AutoNameGenerator (SPPluginRef pluginref, int nextNameIndex)
{
// fill in fDefaultName
GetDefaultName(pluginref);

// initialize the base members
// note kMaxCollectionStringLength accounts for null terminator and maximumLength does not
maximumLength = kMaxCollectionStringLength-1;
uniqueNames = true;
baseName = fDefaultName;
nextNewNameIndex = nextNameIndex;
HasName = sHasName;
}

private:
void GetDefaultName (SPPluginRef pluginref)
{
// Somehow initialize fDefaultName with the default name for the
// collection. The pluginref is probably needed in order to look
// up the name in the plugin resources.
}

AIErr hasName (const ai::UnicodeString &name, AIBoolean &hasit)
{
// Code to answer the question. When comparing 'name' against
// names of objects in the collection it's important to use the
// AIUserSuite::SameName() API. The name generation process does
// not use a simple string comparison.
}

static AIAPI AIErr sHasName (AIAutoNameGenerator &self, const ai::UnicodeString &name, AIBoolean &hasit)
{
return static_cast<AutoNameGenerator&>(self).hasName(name, hasit);
}

ai::UnicodeString fDefaultName;
};
@endcode
*/

/*******************************************************************************
**
**	Suite
**
**/

/** @ingroup Suites
This suite provides utility functions for working with Illustrator,
including unit conversion utilities and a progress bar.

\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
\c #kAIUserSuite and \c #kAIUserSuiteVersion.
*/
struct AI140UserSuite {

	/** Reports whether a user has canceled the current operation.
	(Note that this function returns a boolean value, not an error code.)
	@return	True if the user has canceled an operation
	by pressing Command-dot or clicking Cancel or Stop in the
	progress bar.
	*/
	AIAPI AIBoolean (*Cancel) ( void );

	/** Updates the progress bar.
	(Note that this function does not return an error code.)
	@param current A number between 0 and \c max that represents
	how far the operation has progressed.
	@param max The maximum value, representing 100% progress.
	*/
	AIAPI void (*UpdateProgress) ( long current, long max );

	/**	Sets the text message displayed in the progress bar. If not provided,
	the text line is blank.
	(Note that this function does not return an error code.)
	@param text The text message.
	*/
	AIAPI void (*SetProgressText) ( const ai::UnicodeString& text );

	/** Explicitly close the progress bar if one is currently shown.
	(Note that this function does not return an error code.)
	*/
	AIAPI void (*CloseProgress) ( void );

	/**	Converts a number of document points to a Unicode string, using
	the period as a decimal separator.
	(Note that this function does not return an error code.)
	@param value The value to convert.
	@param precision The number of digits to the right of the decimal,
	in the range [0..4].
	@param string [out] A buffer in which to return the converted value, at
	least 12 characters.
	*/
	AIAPI void (*AIRealToString) ( AIReal value, short precision, ai::UnicodeString& string );

	/**	Converts a Unicode string containing a number to an \c #AIReal value,
	using the period as a decimal separator.
	(Note that this function does not return an error code.)
	@param string The string to convert.
	@param value  [out] A buffer in which to return the converted value.
	If the string is not a number, this is set to \c #kAIRealUnknown.
	*/
	AIAPI void (*StringToAIReal) ( const ai::UnicodeString& string, AIReal *value );

	/**	Converts a number of document points to a Unicode string, using the localized
	international utilities (IU) decimal separator.
	(Note that this function does not return an error code.)
	@param value The value to convert.
	@param precision The number of digits to the right of the decimal,
	in the range [0..4].
	@param string [out] A buffer in which to return the converted value, at
	least 12 characters.
	*/
	AIAPI void (*IUAIRealToString) ( AIReal value, short precision, ai::UnicodeString& string );

	/**	Converts a Unicode string containing a number to an \c #AIReal value,
	using the localized international utilities (IU) decimal separator.
	(Note that this function does not return an error code.)
	@param string The string to convert.
	@param value  [out] A buffer in which to return the converted value.
	If the string is not a number, this is set to \c #kAIRealUnknown.
	*/
	AIAPI void (*IUStringToAIReal) ( const ai::UnicodeString& string, AIReal *value );

	/**	Converts a number of document points to a formatted Unicode string containing
	a number and ruler units, using the localized international utilities (IU)
	decimal separator, and the passed preference for precision. If passed precision value is -1 
	then user preference for precision is used.
	Uses the currently set ruler units, which can be inches, points, or centimeters.
	(Note that this function does not return an error code.)
	@param value The value to convert.
	@param precision The number of digits to the right of the decimal,
	in the range [0..4]. Pass -1 if user preference for precision should be used.
	@param string [out] A buffer in which to return the converted value, at
	least 12 characters.
	*/
	AIAPI AIErr (*IUAIRealToStringUnits) ( AIReal value, int precision, ai::UnicodeString& string );

	/** Converts a formatted Unicode string containing a number expressed in ruler units
	to an \c #AIReal value in points. The current ruler units for the artwork
	are used as the original units to scale the result, and the user's
	preferences for precision are applied.
	(Note that this function does not return an error code.)
	@param string The string to convert, which uses the localized international utilities (IU)
	decimal separator. It can contain a unit specifier, one of "in", "pt", or "cm".
	If no unit specifier is included, uses the current ruler units.
	@param value [out] A buffer in which to return the converted value.
	If the string is not a number, this is set to \c #kAIRealUnknown.
	*/
	AIAPI void (*IUStringUnitsToAIReal) ( const ai::UnicodeString& string, AIReal *value );

	/** Retrieves a string representing the current ruler units.
	@param format The format for the result, one of:
	<br> \c #kShortUnits
	<br> \c #kLongSingularUnits
	<br> \c #kLongPluralUnits
	<br> If, for instance, the current unit is inches, the returned string
	would be "in", "inch", or "inches".
	@param string [out] A buffer in which to return the units string, at least 20 characters.
	*/
	AIAPI AIErr (*GetUnitsString) ( short format, ai::UnicodeString& string );

	/**	Converts an Illustrator units constant value to an \c #ADMUnits constant value.
	For example, the equivalent of \c #kPointsUnits is \c #kADMPointUnits.
	@param aiUnits The value to convert.
	@param admUnits [out] A buffer in which to return the converted value.
	*/
	AIAPI AIErr (*AIUnitsToADMUnits) ( short aiUnits, ADMUnits *admUnits);

	/**	Converts an \c #ADMUnits constant value to an Illustrator units constant value.
	For example, the equivalent of \c #kADMPointUnits is \c #kPointsUnits.
	@param admUnits The value to convert.
	@param aiUnits [out] A buffer in which to return the converted value.
	*/
	AIAPI AIErr (*ADMUnitsToAIUnits) ( ADMUnits admUnits, short *aiUnits);

	/**	Retrieves the base name of a global object, stripping off any additional
	token that was added to make the name unique (by a function such as
	\c #AICustomColorSuite::NewCustomColorName(), for example).
	@param name [in, out] A string in which to pass a unique name and
	return the base name. The string is modified in place.
	*/
	AIAPI AIErr (*GetGlobalObjectDisplayName)( ai::UnicodeString& name );

	/** Opens the appropriate application to edit a placed or raster object.
	This is equivalent to an option-double-click on the object with the selection tool.
	@param art The placed or raster art object.
	@return \c #kApplicationNotFoundErr error if the application is not found.
	<br> \c #kObjectNotLinkedErr error if the object is not a placed or raster object.
	*/
	AIAPI AIErr (*EditInOriginalApp) ( AIArtHandle art );

	/** Runs an "Idle Event" that allows the application to do various idle-time things like update its selection view and state.  Can be useful if
	you have code that has its own message processing.  */
	AIAPI AIErr (*AppIdle) ( void );

	/**	Builds a directory menu.  Available only in Mac OS.  Builds a menu consisting of the specified path as well as all parent directories of that path.
	@param menu	 The platform-specific menu object.
	@param fileSpec	The file object for the directory.
	*/
	AIAPI AIErr (*BuildDirectoryMenu) ( AIPlatformMenuHandle menu, const ai::FilePath &fileSpec);

	/**	Retrieves a directory.  Available only in Mac OS.  Returns a filespec pertaining to the 'index' item inside of the menu returned by BuildDirectoryMenu.
	@param fileSpec The file object for the directory.
	@param index The 0-based index of the directory.
	*/
	AIAPI AIErr (*GetIndexedDirectorySpec) ( ai::FilePath &fileSpec, int index);

	/**	Reveals a file in the Finder.  Available only in Mac OS.
	@param fileSpec	 The file object for the file.
	*/
	AIAPI AIErr (*RevealTheFile) ( const ai::FilePath &fileSpec);

	/** Disables (dims) the cancel or stop button in the progress bar.
	(Note that this function does not return an error code.)
	*/
	AIAPI void (*DisableProgressCancel) ( void );

	/** Reports whether it is safe to allocate memory. Call when a timer
	or other  asynchronous event triggers an action that allocates memory.
	Not needed when handling notifications or user events; the plug-in does not receive
	these when it is not ok to allocate memory.
	(Note that this function returns a boolean value, not an error code.)
	@param True if it is safe to allocate memory. False if it is not safe; in this case,
	reschedule the action and try again later.
	*/
	AIAPI AIBoolean (*OKToAllocateMemory) ( void );

	// New for AI 11
	/** Retrieves the current date and time.
	@param outValue [out] A buffer in which to return the current date-time value.
	*/
	AIAPI AIErr (*GetDateAndTime)(AIUserDateTime *outValue);

	/* Formats a date into a Unicode string.
	@param inValue The date to format, or \c NULL to format the current date-time value.
	@param formatFlag The format to use, one of:
	<br> \c #kAIShortDateFormat
	<br> \c #kAILongDateFormat
	<br> \c #kAIAbbrevDateFormat
	@param dateStringUS [out] A buffer in which to return the formatted date string.
	*/
	AIAPI AIErr (*GetDateString)(const AIUserDateTime *inValue, const int formatFlag, ai::UnicodeString& dateStringUS);

	/* Formats a time into a Unicode string.
	@param inValue The time to format, or \c NULL to format the current date-time value.
	@param formatFlag The format to use, one of:
	<br> \c #kAIShortTimeFormat
	<br> \c #kAILongTimeFormat
	@param dateStringUS [out] A buffer in which to return the formatted time string.
	*/
	AIAPI AIErr (*GetTimeString)(const AIUserDateTime *inValue, const int formatFlag, ai::UnicodeString& dateStringUS);

	/** Retrieves the year value from a date-time.
	@param inValue The date-time value, or \c NULL to get the current date-time.
	@param year [out] A buffer in which to return the value.
	*/
	AIAPI AIErr (*GetYear)(const AIUserDateTime *inValue, int *year);

	/** Retrieves the month value from a date-time.
	@param inValue The date-time value, or \c NULL to get the current date-time.
	@param year [out] A buffer in which to return the value.
	*/
	AIAPI AIErr (*GetMonth)(const AIUserDateTime *inValue, int *month);

	/** Retrieves the day value from a date-time.
	@param inValue The date-time value, or \c NULL to get the current date-time.
	@param year [out] A buffer in which to return the value.
	*/
	AIAPI AIErr (*GetDay)(const AIUserDateTime *inValue, int *day);

	/** Retrieves the hour value from a date-time.
	@param inValue The date-time value, or \c NULL to get the current date-time.
	@param year [out] A buffer in which to return the value.
	*/
	AIAPI AIErr (*GetHour)(const AIUserDateTime *inValue, int *hour);

	/** Retrieves the minute value from a date-time.
	@param inValue The date-time value, or \c NULL to get the current date-time.
	@param year [out] A buffer in which to return the value.
	*/
	AIAPI AIErr (*GetMinute)(const AIUserDateTime *inValue, int *minute);

	/** Retrieves the second value from a date-time.
	@param inValue The date-time value, or \c NULL to get the current date-time.
	@param year [out] A buffer in which to return the value.
	*/
	AIAPI AIErr (*GetSecond)(const AIUserDateTime *inValue, int *second);

	/** Retrieves the day-of-week value from a date-time.
	@param inValue The date-time value, or \c NULL to get the current date-time.
	@param year [out] A buffer in which to return the value.
	*/
	AIAPI AIErr (*GetDayOfWeek)(const AIUserDateTime *inValue, int *dayOfWeek);

	/**	Launches an application, and optionally opens the current document in it.
	@param spFileSpec The file specification for the application's executable.
	@param openDoc True to open the current document in the new application.
	*/
	AIAPI AIErr (*LaunchApp)(const ai::FilePath &spFileSpec, ASBoolean openDoc);

	/** Generates an appropriate name for a named object, such as
	a layer, swatch, or style, according to the naming rules for that
	collection.
	@param set The naming rules.
	@param name [out] An ai::UnicodeString in which to return the generated name.
	*/
	AIAPI AIErr (*NextName) (AIAutoNameGenerator &set, ai::UnicodeString &name);

	/** Generates an appropriate name for a copy of a named object, such as
	a layer, swatch, or style, according to the naming rules for that
	collection.
	@param set The naming rules.
	@param original	Original name to copy (may be an empty string).
	@param copy [out] An ai::UnicodeString in which to return the generated name.
	*/
	AIAPI AIErr (*CopyOfName) (AIAutoNameGenerator &set, const ai::UnicodeString &original, ai::UnicodeString &copy);

	/** Tests for equality of names within a collection of named objects.
	Use in the \c #AIAutoNameGenerator::HasName() callback function
	to test whether an automatically generated name matches a name
	already in the collection.
	@param name1 The first name.
	@param name2 The second name.
	@param same [out] An AIBoolean reference in which to return true if the names
	are the same.
	*/
	AIAPI AIErr (*SameName) (const ai::UnicodeString &name1, const ai::UnicodeString &name2, AIBoolean &same);

	/** Not implemented. (Installs a custom progress reporting mechanism.)
	@return \c #kNotImplementedErr.
	*/
	AIAPI AIErr (*PushCustomProgress) (AICustomProgressSuite *suite);

	/**  Not implemented. (Removes the most recently installed custom progress reporting mechanism.)
	@return \c #kNotImplementedErr.
	*/
	AIAPI AIErr (*PopCustomProgress) ();

	/** Opens a platform-specific dialog for saving a file.
	@param title Dialog title.
	@param AIPlatformFileDlgOpts File types to save. Can be \c NULL.
	@param defaultName Default file name to appear in dialog. Can be \c NULL.
	@param ioFilePath [in, out] A buffer in which to pass the directory to browse or \c NULL, and
	return the full path of the file chosen by the user.
	*/
	AIAPI AIErr (*PutFileDialog)(const ai::UnicodeString &title, const AIFileDialogFilters*, const ai::UnicodeString &defaultName, ai::FilePath &ioFilePath);

	/** Opens a platform-specific dialog for opening a file.
	@param title Dialog title.
	@param AIPlatformFileDlgOpts File types to open. Can be \c NULL.
	@param ioFilePath [in, out] A buffer in which to pass the directory to browse or \c NULL, and
	return the full path of the file chosen by the user.
	*/
	AIAPI AIErr (*GetFileDialog)(const ai::UnicodeString &title, const AIFileDialogFilters*, ai::FilePath &ioFilePath);

	/** Opens a platform-specific dialog for choosing a folder.
	@param title Dialog title.
	@param ioFilePath [in, out] A buffer in which to pass the folder to browse or \c NULL, and
	return the full path of the folder chosen by the user.
	*/
	AIAPI AIErr (*GetDirectoryDialog)(const ai::UnicodeString &title, ai::FilePath &ioFilePath);

	/** Displays an alert dialog with a warning icon and OK and Cancel buttons.
	@param msg The message to display.
	@param defaultOk True to make the OK button the default, false to make Cancel the default.
	@param dontShowKey A preference key to use with the "Do not show again" checkbox,
	in which to store the user's choice and save it in the application preferences file.
	When \c NULL, the dialog does not include the checkbox.
	@return True if the dialog was dismissed with the OK button,
	false if it was canceled.
	*/
	AIAPI AIBoolean (*OKCancelAlert) (const ai::UnicodeString& msg, AIBoolean defaultOk, const char* dontShowKey);

	/** Displays an alert dialog with a warning icon and an OK button.
	@param msg The message to display.
	@param dontShowKey A preference key to use with the "Do not show again" checkbox,
	in which to store the user's choice and save it in the application preferences file.
	When \c NULL, the dialog does not include the checkbox.
	@return Nothing.
	*/
	AIAPI void (*WarningAlert) (const ai::UnicodeString& msg, const char* dontShowKey);
};



#if defined(MAC_ENV) || defined(WIN_ENV)
/**	 @ingroup Suites
This suite provides utilities specific to the Mac OS platform.

\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
\c #kAIMacUserSuite and \c #kAIMacUserSuiteVersion.
*/
typedef struct {

	/** In Mac OS only, a callback procedure for a platform-specific 
	modal dialog, called in response to a user-interaction event. 
	Pass this function pointer in the \c filterproc parameter to the 
	Mac OS function \c ModalDialog().

	This callback allows you to update the Illustrator document in
	response to events in the modal dialog, which would otherwise prevent
	any activity in the application while the dialog is shown.

	@param theDialog The window object for the dialog.
	@param theEvent A pointer to the event object for the event that triggered the callback.
	@param itemHit [out] Optional. A buffer in which to return the dialog result. 
	Could be 0 (no result, as the event was not consumed), 1 (the OK button was clicked) or 2 (the Cancel button was clicked).
	@return True if the event was consumed, false if it was not.
	*/
	AIAPI AIBoolean (*ModalFilterProc) ( AIWindowRef theDialog, AIEvent *theEvent, short *itemHit );

	/**	Displays a color swatch preview in a platform window, similar to the one
	shown in the Swatch palette.
	@param window The window object.
	@param swatchRect A pointer to the region in which to display the preview,
	in coordinates relative to the window's origin.
	@param colorSpec A pointer to the swatch color.
	*/
	AIAPI AIErr (*PreviewColorSwatch) ( AIWindowRef window, AIRect *swatchRect, AIColor *colorSpec );

} AI140MacUserSuite;
#endif

#include "AIHeaderEnd.h"


#endif
