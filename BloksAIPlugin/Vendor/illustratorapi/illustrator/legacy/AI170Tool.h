#ifndef __AI170Tool__
#define __AI170Tool__

/*
 *        Name:	AI170Tool.h
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Tool Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2011 Adobe Systems Incorporated.
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

#ifndef __AIArt__
#include "AIArt.h"
#endif

#ifndef __AIEvent__
#include "AIEvent.h"
#endif

#ifndef __AIFixedMath__
#include "AIFixedMath.h"
#endif

#ifndef __AIPlugin__
#include "AIPlugin.h"
#endif

#ifndef __AIToolNames__
#include "AIToolNames.h"
#endif


#ifndef __ASHelp__
#include "ASHelp.h"
#endif

#ifndef FLT_MAX
#include <float.h>
#endif

#include "AITool.h"
#include "AIHeaderBegin.h"
/** @file AI170Tool.h */


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAI170ToolSuite				kAIToolSuite
#define kAIToolSuiteVersion13		AIAPI_VERSION(13)
#define kAI170ToolSuiteVersion		kAIToolSuiteVersion13
#define kAI170ToolVersion			kAI170ToolSuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/

/**	@ingroup Suites
	This suite allows you to provide plug-in tools for Illustrator.
	Plug-in tools can work on existing artwork or create new objects.
	Tools that you add appear in the Illustrator Tool palette in their own set,
	or as part of an existing tool set. Use the functions in this suite
	to add tools, set options, and control the tool’s appearance in the palette.

	Typically, you set the options that control the behavior of a plug-in tool
	when you install the tool with \c #AIToolSuite::AddTool(). You can modify
	them later with \c #AIToolSuite::SetToolOptions().

  	\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
		\c #kAIToolSuite and \c #kAIToolVersion.

	@section Toolsets Toolsets and Groups in the Tools Palette

	In the Tools palette, \e a toolset is a collection related tools.
	When there is more than one tool in a toolset, only the frontmost tool's
	icon is shown in the palette, with a triangle in the lower left corner
	to indicate the presence of additional tools. The entire toolset
	is shown when the user holds the mouse button down on the topmost tool.

	A \e group is a collection of toolsets. Groups are separated by vertical
	space in the palette.

	To create a new group or toolset, pass \c #kNoTool for
	\c #AIAddToolData::sameGroupAs or \c #AIAddToolData::sameToolsetAs.
	For example, to create a new tool group:
	@code
toolData.title = "MyTool1";
toolData.tooltip = "MyTool1 Tooltip";
toolData.sameGroupAs = kNoTool;
toolData.sameToolsetAs = kNoTool;
	@endcode

	To add a new toolset to this group:
	@code
toolData.title = "MyTool2";
toolData.tooltip = "MyTool2 Tooltip";
error = sTool->GetToolNumberFromName("MyTool1", &toolData.sameGroupAs);
toolData.sameToolsetAs = kNoTool;
	@endcode

	To add tools to this toolset:
	@code
toolData.title = "MyTool2a";
toolData.tooltip = "Tool2a Tooltip";
error = sTool->GetToolNumberFromName("MyTool1",	&toolData.sameGroupAs);
error = sTool->GetToolNumberFromName("MyTool2", &toolData.sameToolsetAs);
	@endcode

	@section ToolBehavior Tool Behavior

	Implement tool behavior by defining handlers for the caller/selector pairs
	and messages that plug-in tools receive, particularly the mouse selectors.
	Check for selectors in the plug-in's main function.

	Your mouse selector handlers can create or modify art objects directly.
	A tool can select and work on several art objects at once.
	The application updates the window between calls to the plug-in, so the
	new or changed artwork appears as the mouse moves.
	Use \c #AIUndoSuite::UndoChanges() before processing the tool drag,
	in order to maintain a known artwork state from which to redraw changes.

	Because multiple  plug-ins can be running at once,
	the artwork state can change in the course of using your tool.
	To verify that a specific artwork state exists, you can use a plug-in
	notifier to indicate that the artwork selection or properties
	have been changed. See the \c #AINotifierSuite.

	The caller for tool plug-ins is \c #kCallerAITool.

	These selectors are sent:
	<br> \c #kSelectorAIEditToolOptions
	<br> \c #kSelectorAITrackToolCursor
	<br> \c #kSelectorAIToolMouseDown
	<br> \c #kSelectorAIToolMouseDrag
	<br> \c #kSelectorAIToolMouseUp
	<br> \c #kSelectorAISelectTool
	<br> \c #kSelectorAIDeselectTool
	<br> \c #kSelectorAIReselectTool

	These notifiers are related to tools:
	<br> \c #kAIUserToolChangedNotifier
	<br> \c #kAIToolSelectedNotifier
	<br> \c #kAIToolDeselectedNotifier
	<br> \c #kAIToolClearStateNotifier
	<br> \c #kAIToolTitleChangedNotifier	
	<br> \c #kAIToolTooltipChangedNotifier
	<br> \c #kAIToolHelpIDChangedNotifier
	<br> \c #kAIToolChangedNotifier
	<br> \c #kAIToolWindowChangedNotifier
	<br> \c #kAIToolSuspendNotifier
	<br> \c #kAIToolResumeNotifier
	<br> \c #kAIEyedropperDragNotifier

 */
struct AI170ToolSuite {

	/** Installs a plug-in tool. Use at startup.
			@param self This plug-in.
			@param name The unique name of this tool.
			@param data	Information on how to display this tool in the Tool palette.
			@param options Option flags that control the tool's behavior, a logical OR
				of \c #AIToolOptions constants.
			@param tool	[out] A buffer in which to return the tool reference. If you
				install multiple tools, save to compare to the tool reference in tool
				message data.
		*/
	AIAPI AIErr (*AddTool) ( SPPluginRef self, const char *name,
				AIAddToolData *data, ai::int32 options,
				AIToolHandle *tool );

	/** For internal use only */
	AIAPI AIErr (*AddToolPrivate) ( SPPluginRef self, const char *name,
		AIAddToolDataPrivate *data, ai::int32 options,
		AIToolHandle *tool );

	/** Retrieves the unique identifying name of a tool.
		To get the localizable title that appears in the UI, use \c #GetToolTitle().
			@param tool The tool reference.
			@param name [out] A pointer to point to the name string. Do
				not modify this string.
		*/
	AIAPI AIErr (*GetToolName) ( AIToolHandle tool, char **name );

	/** Retrieves the option flags of a tool. To retain the existing flags when
		setting options with \c #SetToolOptions(), obtain them with this function
		and do a logical OR with the new flags.
			@param tool The tool reference.
			@param options [out] A buffer in which to return the options value, a logical
				OR of \c #AIToolOptions constants.
	  	*/
	AIAPI AIErr (*GetToolOptions) ( AIToolHandle tool, ai::int32 *options );

	/** Sets the option flags of a tool. To retain the existing flags when
		setting options, obtain them with \c #GetToolOptions()
		and do a logical OR with the new flags.
			@param tool The tool reference.
			@param options The new options value, a logical OR of \c #AIToolOptions constants.
		*/
	AIAPI AIErr (*SetToolOptions) ( AIToolHandle tool, ai::int32 options );

	/** Retrieves the plug-in that installed a tool.
			@param tool The tool reference.
			@param plugin [out] A buffer in which to return the	plug-in reference,
				which can be used with \c #AIPluginSuite functions.
		*/
	AIAPI AIErr (*GetToolPlugin) ( AIToolHandle tool, SPPluginRef *plugin );

	/** Retrieves the currently selected plug-in tool. If the current tool
		is a built-in tool, returns NULL.
		See \c #AIToolboxSuite::GetCurrentToolType() or \c #GetCurrentToolName()
		for retrieving the current tool including built-in tools.
			@param tool	[out] A buffer in which to return the tool reference.
		*/
	AIAPI AIErr (*GetSelectedTool) ( AIToolHandle *tool );

	/** Selects a plug-in tool programmatically. This is the same as the user
		selecting the tool in the Tool palette.
		To select built-in tools, see \c #SetSelectedToolByName()
			@param tool The tool reference.
		*/
	AIAPI AIErr (*SetSelectedTool) ( AIToolHandle tool );

	/** Gets the number of installed plug-in tools. Use with \c #GetNthTool()
		to iterate through plug-in tools.
			@param count [out] A buffer in which to return the number of tools.
		*/
	AIAPI AIErr (*CountTools) ( ai::int32 *count );

	/** Retrieves a tool by index position. Use with \c #CountTools()
		to iterate through plug-in tools.
			@param n The 0-based position index.
			@param tool	[out] A buffer in which to return the tool reference.
		*/
	AIAPI AIErr (*GetNthTool) ( ai::int32 n, AIToolHandle *tool );

	/** Retrieves a plug-in tool by its tool number, as assigned when it is created
		with \c #AddTool(), and obtained by calling \c #GetToolNumberFromHandle.
		See @ref Toolsets.
		If the toolNum is the number of a built-in tool, returns NULL, since
		built-in tools do not have an AIToolHandle.
			@param toolNum The tool number.
			@param tool	[out] A buffer in which to return the tool reference.
		*/
	AIAPI AIErr (*GetToolHandleFromNumber) ( AIToolType toolNum,  AIToolHandle *tool );

	/** Retrieves a tool number from a tool's unique name. Use to find the numbers of
		built-in tools, in order to place your tool in an existing group or toolset.
		See @ref Toolsets.
			@param name The tool name. The names of Illustrator's built-in tools
				can be found in \c AIToolNames.h.
			@param toolNum [out] A buffer in which to return the tool number.
		*/
	AIAPI AIErr (*GetToolNumberFromName) ( const char *name, AIToolType *toolNum );

	/** Retrieves a tool number for a tool. Use to find the numbers of
		plug-in tools, in order to place your tool in an existing group or toolset.
		See @ref Toolsets.
			@param tool The tool reference.
			@param toolNum [out] A buffer in which to return the tool number. 	 */
	AIAPI AIErr (*GetToolNumberFromHandle) ( AIToolHandle tool, AIToolType *toolNum );

	/** Retrieves the unique name of a tool from its number. To get the localizable
		title that appears in the UI, use \c #GetToolTitle().
			@param toolNum The tool number.
			@param name	[out] A pointer to point to the name string. Do not modify
				this string. Copy it immediately to use it.
		 */
	AIAPI AIErr (*GetToolNameFromNumber) ( AIToolType toolNum, char **name );

	/** Retrieves the localizable title of a tool, which appears in the UI.
		To get the unique, identifying name, use \c #GetToolName().
			@param tool The tool reference.
			@param title [out] A pointer to point to the title string. Do not modify
				this string.
		*/
	AIAPI AIErr (*GetToolTitle) ( AIToolHandle tool, char **title );

	/** Sets the localizable title of a tool, which appears in the UI.
			@param tool The tool reference.
			@param title The new title string.
		*/
	AIAPI AIErr (*SetToolTitle) ( AIToolHandle tool, const char *title );


	/** Retrieves the tooltip string for a tool.
			@param tool The tool reference.
			@param tooltip [out] A pointer to point to the tooltip string. Do not modify
				this string.
		*/
	AIAPI AIErr (*GetTooltip) ( AIToolHandle tool, char **tooltip );

	/** Sets the tooltip string for a tool.
			@param tool The tool reference.
			@param tooltip The new tooltip string.
		 */
	AIAPI AIErr (*SetTooltip) ( AIToolHandle tool, const char *tooltip );

	/** Retrieves the help-system identifier for a tool.
			@param tool The tool reference.
			@param helpID [out] A buffer in which to return the help ID,
				which can be an integer or a pooled string.
		*/
	AIAPI AIErr (*GetToolHelpID) ( AIToolHandle tool, ASHelpID *helpID );

	/** Sets the help-system identifier for a tool.
			@param tool The tool reference.
			@param helpID The new help ID, which can be an integer or a pooled string.
		 */
	AIAPI AIErr (*SetToolHelpID) ( AIToolHandle tool, ASHelpID helpID );

	/** Determines which labeled fields are displayed in the Info palette for a tool.
		Typically called once at startup to initialize the Info palette.
			@param tool The tool reference.
			@param infoVars A pointer to the first member of an array of
				information variables, which correspond to labeled fields
				in Illustrator’s Info palette, as defined in \c #AIToolInfoVariable.
				Only the fields included in this array are shown for the tool.
				To initialize or set the values in the fields, use \c #SetToolInfoVarValues().
		 */
	AIAPI AIErr (*SetToolInfoVars) ( AIToolHandle tool, const ai::int32 infoVars[] );

	/** Sets field values in the Info palette. Only those fields specified by
		\c #SetToolInfoVars() are displayed in the palette.
			@param infoVars A pointer to the first member of an array of
				information variables, which correspond to labeled fields
				in Illustrator’s Info palette. This is the same array specified
				by \c #SetToolInfoVars().
			@param values A pointer to the first member of an array of values,
				whose positions match those in the \c infoVars array.

			\b Example:
@code
AIErr UpdateInfoPalette( AIToolHandle tool, AIRealPoint origin, AIArtHandle art )
{
	ASErr error = kNoErr;
	if (art) {
		static const long infoVars = { kInfoDocX, kInfoDocY, kInfoSizeX, kInfoSizeY, kInfoEndOfList };
		AIReal *infoValues[4];
		AIReal temp[2];
		AIRealRect artBounds;
		error = sAIArt->GetArtTransformBounds( art,0, kStroke, &artBounds);
		if ( error )
			return error;
		temp[0] = artBounds.right - artBounds.left;
		temp[1] = artBounds.bottom - artBounds.top;
		infoValues[0] = &origin.h;
		infoValues[1] = &origin.v;
		infoValues[2] = temp;
		infoValues[3] = temp +1;
		error = sAITool->SetToolInfoVarValues( infoVars, (void**)infoValues);
		if ( error )
			return error;
	}
}
@endcode
		*/
	AIAPI AIErr (*SetToolInfoVarValues) ( const ai::int32 *infoVars,  void **values );

	/** Reports whether a pressure-sensitive device such as a graphics tablet
		was available on application startup.
			@param hasPressure [out] A buffer in which to return true if
				a pressure-sensitive device is in use.
		*/
	AIAPI AIErr (*SystemHasPressure) ( AIBoolean *hasPressure );

	// New for AI10

	/** @deprecated Obsolete. Do not use. */
	AIAPI AIErr (*GetToolNullEventInterval) (AIToolHandle tool, AIToolTime *outTime);

	/** @deprecated Obsolete. Do not use. */
	AIAPI AIErr (*SetToolNullEventInterval) (AIToolHandle tool, AIToolTime inTime);

	// New for AI13

	/** Selects a plug-in tool, but does not highlight
		it in the palette or show its tool name in the status bar of the document
		window. Indicates this \e soft selection by setting the \c isSoftMode flag.
		\c #SetSelectedTool() turns this flag off.
			@param tool The tool reference.
		*/
	AIAPI AIErr (*SetSoftSelectedTool) ( AIToolHandle tool );

	/** Reports whether there is currently a \e soft tool selection.
		Soft mode is entered when a tool, such as the rectangle tool, is
		selected and the user implicitly overrides this by drawing with the eraser
		end of a tablet stylus.
			@param isSoftMode [out] A buffer in which to return true if there is a
				soft tool selection.
		*/
	AIAPI AIErr (*IsSoftModeSelection) ( AIBoolean *isSoftMode );

	/** Retrieves the name of the tool that will be temporarily selected  by pressing Ctrl (in Windows)
		or Cmd (in MacOS) key while using this tool.
		Effective only if the tool has set the option \c #kToolWantsAlternateSelectionTool.
			@param tool This tool.
			@param name A buffer in which to return the name of the alternate selection tool.
	*/
	AIAPI AIErr (*GetAlternateSelectionToolName) (AIToolHandle tool, char **name);

	/** Sets the tool that will be temporarily selected by pressing Ctrl (in Windows)
		or Cmd (in MacOS) key while using this tool.
		Effective only if the tool has set the option \c #kToolWantsAlternateSelectionTool.
			@param tool This tool.
			@param name The name of the alternate selection tool.
	*/
	AIAPI AIErr (*SetAlternateSelectionToolName) (AIToolHandle tool, const char* alternateTool);

	// New for AI16: support for plug-in access to built-in tools

	/** Retrieves the unique name of the currently selected tool. This is the same
	name you get from calling \c #AIToolboxSuite::GetCurrentToolType()
	followed by \c #GetToolNameFromNumber().
			@param name	[out] A pointer to point to the name string. Do not modify
								this string. Copy it immediately to use it.
	 */
	AIAPI AIErr (*GetCurrentToolName) ( const char **name );

	/** Returns the numerical identifier of the most recently used built-in selection tool,
            and optionally retrieves the unique name of the tool, from \c AIToolNames.h.
            (Note that this function returns an \c #AIToolType, not an error code.)
            @param name     [out][optional] A buffer in which to return the name string.
                            Do not modify this string. Copy it immediately to use it.
            @return The numerical identifier.
    */

	AIAPI AIToolType (*GetLastUsedSelectionTool) ( const char **name );

	/** Select a tool by its unique name identifier. May be either the name of a plug-in tool,
		as obtained from an AIToolHandle by calling \c #GetToolName(), or one of the tool name
		constants from AIToolNames.h.
			@param name The name of the tool to be selected.
		Returns kBadParameterErr if there is no tool with the input name.
	 */
	AIAPI AIErr (*SetSelectedToolByName) ( const char *name );


};


#include "AIHeaderEnd.h"


#endif
