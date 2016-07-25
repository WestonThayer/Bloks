#ifndef __AI192User__
#define __AI192User__

/*
 *        Name: AIUser.h
 *   $Revision: 15 $
 *      Author:
 *        Date:
 *     Purpose: Adobe Illustrator User Utilities Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2016 Adobe Systems Incorporated.
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

/** @file AIUser.h */


/************************************************************************s*******
 **
 **	Constants
 **
 **/

// v.14.0
#define kAI192UserSuite					kAIUserSuite
#define kAI192UserSuiteVersion12		AIAPI_VERSION(12)
#define kAI192UserSuiteVersion			kAI192UserSuiteVersion12
#define kAI192UserVersion				kAI192UserSuiteVersion

#if Macintosh || MSWindows
#define kAI192MacUserSuite				kAIMacUserSuite
#define kAI192MacUserSuiteVersion6		AIAPI_VERSION(6)
#define kAI192MacUserSuiteVersion		kAI192MacUserSuiteVersion5
#define kAI192MacUserVersion			kAI192MacUserSuiteVersion
#endif

/** @ingroup Suites
	This suite provides utility functions for working with Illustrator,
	including unit conversion utilities and a progress bar.

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAI192UserSuite and \c #kAI192UserSuiteVersion.
	*/
struct AI192UserSuite {

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
	AIAPI void (*UpdateProgress) ( ai::int32 current, ai::int32 max );

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
	AIAPI AIErr (*IUAIRealToStringUnits) ( AIReal value, ai::int32 precision, ai::UnicodeString& string );

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
	AIAPI AIErr (*GetIndexedDirectorySpec) ( ai::FilePath &fileSpec, ai::int32 index);

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
	AIAPI AIErr (*GetDateString)(const AIUserDateTime *inValue, const ai::int32 formatFlag, ai::UnicodeString& dateStringUS);

	/* Formats a time into a Unicode string.
			@param inValue The time to format, or \c NULL to format the current date-time value.
			@param formatFlag The format to use, one of:
				<br> \c #kAIShortTimeFormat
				<br> \c #kAILongTimeFormat
			@param dateStringUS [out] A buffer in which to return the formatted time string.
		*/
	AIAPI AIErr (*GetTimeString)(const AIUserDateTime *inValue, const ai::int32 formatFlag, ai::UnicodeString& dateStringUS);

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


	/** Opens a platform-specific dialog for saving a file.
     		@param title Dialog title.
			@param AIFileDialogFilters File types to save. Can be \c NULL.
			@param defaultName Default file name to appear in dialog. Can be \c NULL.
			@param ioFilePath [in, out] A buffer in which to pass the directory to browse or \c NULL, and
				return the full path of the file chosen by the user.
		*/
	AIAPI AIErr (*PutFileDialog)(const ai::UnicodeString &title, const AIFileDialogFilters*, const ai::UnicodeString &defaultName, ai::FilePath &ioFilePath);

	/** Opens a platform-specific dialog for opening a file.
     		@param title Dialog title.
			@param AIFileDialogFilters File types to open. Can be \c NULL.
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
			@return Nothing. It does not return AIErr
		*/
	AIAPI void (*WarningAlert) (const ai::UnicodeString& msg, const char* dontShowKey);

	/** Displays an modal alert dialog with a warning icon and an OK button which doesnot get dismissed on ESC key.
			@param msg The message to display.
			@param dontShowKey A preference key to use with the "Do not show again" checkbox,
			in which to store the user's choice and save it in the application preferences file.
			When \c NULL, the dialog does not include the checkbox.
			@return Nothing. It does not return AIErr
			*/
	AIAPI void (*MessageAlertEx) (const ai::UnicodeString& msg, const char* dontShowKey);

	/** Displays a predefined dialog with a yes/no question.
		The dialog displays text specified with a unicodeString, and
		buttons with default labels Yes, No, and Cancel.
		@param msg The text string.
		@return The \c #AIAnswer constant for the button pressed to dismiss the dialog,
		or \c #kAIAnswer_Invalid in case of error.
		@see \c #ErrorAlert(), \c #MessageAlert(), \c #YesNoAlert()
		*/
	AIAPI AIAnswer (*QuestionAlert)(const ai::UnicodeString &msg);

	/** Displays a predefined dialog with a yes/no question.
		The dialog displays text specified with a unicodeString, and
		buttons with default labels Yes and No.
		@param msg The text string.
		@return The \c #AIAnswer constant for the button pressed to dismiss the dialog,
		or \c #kAIAnswer_Invalid in case of error.
		@see \c #ErrorAlert(), \c #MessageAlert(), \c #QuestionAlert()
		*/
	AIAPI AIAnswer (*YesNoAlert)(const ai::UnicodeString &msg);

	/** Displays a predefined dialog that informs the user that an error occurred.
		The dialog displays text specified with a unicodeString, with the platform-specific
		error icon at the left, and an OK button.
		@param msg The text string.
		@return Nothing.It doesnot return an AIErr
		@see \c #MessageAlert(),  \c #QuestionAlert(), \c #YesNoAlert()
		*/
	AIAPI void (*ErrorAlert)(const ai::UnicodeString &msg);

	/** Displays a predefined dialog with an informational message.
		The dialog displays text specified with a unicodeString, with the
		platform-specific message icon at the left, and an OK button.
		@param msg The text string.
		@return Nothing.It doesnot return an AIErr
		@see \c #ErrorAlert(), \c #QuestionAlert(), \c #YesNoAlert()
		*/
	AIAPI void (*MessageAlert)(const ai::UnicodeString &msg);

	/**	Invokes the platform-specific color picker dialog.
	@param inLocation[int]	The position of the dialog.	 (-1, -1) centers the dialog on the screen.
	@param inColor[in]	The initially selected color value.
	@param outColor	[out] A buffer in which to return the selected color.
	@return True if the user selected a color, false otherwise.
	*/
	AIAPI AIBoolean (*ChooseFromOSColorPicker) (const AIPoint &inLocation,
		const AIRGBColor& inColor, AIRGBColor* outColor);

	/** Evaluates a numeric expression to create a formatted string suitable for display.
	Call, for example, when a numeric edit control loses focus or the user presses "=".
	If the result of evaluation is not a valid numeric value as per options specified, it is recommended that
	the associated control display the last known-good value, or a blank string
	accompanied by a beep or other error indicator.

	@param expr [in] The expression to be evaluated (typically entered by the user
	in the control).
	@param options [in] An \c #AIExpressionOptions structure that determines how
	a numeric result is obtained. Specifies the units for the
	result, a range to which the result is clipped, and the precision.
	@param evaluatedExpr [out] A buffer in which to return the formatted display string.
	@param isChanged [out] A buffer in which to return true if the result of evaluation
	is different from result of user input. Example in case of non numeric input or out of bounds input.
	@param numericValue [out] A buffer in which to return the numeric value, according to the specified options.
	*/
	AIAPI AIErr (*EvaluateExpression)(const ai::UnicodeString& expr, const AIExpressionOptions& options, ai::UnicodeString& evaluatedExpr,
		AIBoolean & isChanged , AIDouble& numericValue);

	/** Invokes a modal dialog in which the user must input text. The dialog cannot be dismissed
		until text is entered. If default text is provided, however, the user can dismiss the
		dialog without changing that text.

		@param title The title for the dialog
		@param messageText A text message to display above the input field, or NULL to display no message.
		@param label The label for the text field.
		@param ioName [in/out] On input, a default string for the text field. This is replaced by text that
			the user enters, if any.
		@param IsValidInputProc A function pointer to a validation callback that validates the input as typed by the user.
			The first parameter to this call is a \c #AIValidationStage constant that reports whether the call is
			made upon text entry, or upon dismissal of the dialog.
		@param userdata Developer-defined user data to be passed to the validation callback.
		@param maxInputChars The maximum number of characters that user can enter in the text field.
	 */
	AIAPI AIErr (*GetInputFromUser) ( const ai::UnicodeString &title, const ai::UnicodeString* messageText, const ai::UnicodeString &label, ai::UnicodeString& ioField, IsValidInputProc validator, void *userdata, ai::int32 maxInputChars);

	/**  Creates a singleton resource manager instance to be used for cursors.
		Call once for a plugin, after startup is completed.	Destroy the instance on
		application shutdown (not plug-in shutdown).
		@param inRscMgr [out] A buffer in which to return the resource-manager handle.
		@see DisposeCursorResourceMgr()
	*/
	AIAPI AIErr (*CreateCursorResourceMgr)(SPPluginRef, AIResourceManagerHandle* inRscMgr);

	/**  Sets the image to be used for the plug-in's cursor.
		@param cursorID The resource ID of the cursor, or a \c #AIPredefinedCursor
			constant value to use one of the predefined cursors. Cursor images must be
			in PNG format.
		@param inRscMgr The resource manager, as returned by \c #CreateCursorResourceMgr().
	*/
	AIAPI AIErr (*SetCursor)(ai::int32 cursorID, AIResourceManagerHandle inRscMgr);

	/**  Disposes of the plug-in's singleton resource manager. Call once when
		 \c #kAIApplicationShutdownNotifier is received. Do not call as part of plug-in shutdown.
		@param The resource manager handle, as returned on creation.
	*/
	AIAPI AIErr (*DisposeCursorResourceMgr)(AIResourceManagerHandle);

	/** Reports the current language in use.
	 @param lang [out] A buffer in which to return the language code.
	 */
	AIAPI AIErr (*GetAILanguageCode)(ai::UnicodeString& lang);
    
	/** Reports the maximum scale factor for all the screens in a Mac OS system,
            or the application's UI scale factor in a Windows system.
            @return The scale factor.
    */

	AIAPI AIReal (*GetMaximumScaleFactorOnSystem)();


	/** Reports the ratio of Art Scale factor and View Scale Factor.
		(ArtScaleFactor/ ViewScaleFactor)
    */
	AIAPI AIReal(*GetArtToViewScaleFactor)(AIDocumentViewHandle view);
};

#include "AIHeaderEnd.h"


#endif
