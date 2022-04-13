/*******************************************************************************
* ADOBE CONFIDENTIAL 
*
* Copyright 2017 Adobe
* All Rights Reserved.
*
* NOTICE: Adobe permits you to use, modify, and distribute this file in 
* accordance with the terms of the Adobe license agreement accompanying 
* it. If you have received this file from a source other than Adobe, 
* then your use, modification, or distribution of it requires the prior 
* written permission of Adobe. 
*******************************************************************************/

#pragma once

/*******************************************************************************
 **
 **	Imports
 **
 **/

#include "IAILiteralString.h"
#include "AITool.h"

#include "AIHeaderBegin.h"

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAILiveEditSuite				"AI Live Edit Suite"
#define kAILiveEditSuiteVersion2		AIAPI_VERSION(2)
#define kAILiveEditSuiteVersion			kAILiveEditSuiteVersion2
#define kAILiveEditVersion				kAILiveEditSuiteVersion


/*******************************************************************************
 **
 **	Suite
 **
 **/


struct AILiveEditSuite
{

	/**	Reports whether current interactive art manipulation is in Live Editing
		mode.
		
		@note	This is the method one would call to determine whether to 
				render appearance live or not during art manipulation.
		*/
	AIAPI AIBool8 (*IsLiveEditingAdvisable) ();

    /** Reports whether current interactive art manipulation is in abandoned
        mode.
     
        @note	This is the method one would call to determine whether
        		rendering live appearances has been abandoned during this art
				manipulation.
        */
    AIAPI AIBool8 (*IsLiveEditingAbandoned) ();

	/**	Register a plugin tool to participate in live editing. Registering
		causes future tool usage to automatically make live edit calls
		\c ChangeBeginNotify(), \c ChangeContinueStartNotify(),
		\c ChangeContinueEndNotify() and \c ChangeFinishNotify() appropriately.

		@param	inPluginTool		Tool handle of the plugin tool.

		@param	inFeatureName		Feature name to be used in live editing
									session. This can be any unique string like
									tool or widget name. Must not be empty
									string.
		
		@param	inEPFOverrideValue	Specify EPF (event processing frequency)
									override value for this tool. Valid value
									range is from
									\c #ai::LiveEdit::EPF::kMinimumLimitValue
									to
									\c #ai::LiveEdit::EPF::kMaximumLimitValue.
									To use the global (default) EPF value use
									\c #ai::LiveEdit::EPF::kUseGlobaLimitValue.

        @note	Feature names starting with "ai::" are reserved for use by
				Adobe plugins.

		@see	\c #AIToolSuite::AddTool(), \c #DeregisterLiveEditPluginTool()
		*/
	AIAPI AIErr (*RegisterLiveEditPluginTool) (AIToolHandle inPluginTool,
		const ai::LiteralString& inFeatureName, AIReal inEPFOverrideValue);

	/**	Deregister a previously registered plugin tool so that it no longer
		participates in live editing.

		@param	inPluginTool		Tool handle of the plugin tool.
	
		@see	\c #AIToolSuite::AddTool(), \c #RegisterLiveEditPluginTool()
		*/
	AIAPI AIErr (*DeregisterLiveEditPluginTool) (AIToolHandle inPluginTool);

	/**	Widget manipulating art interactively must call this method at the
		beginning of the manipulation session (mouse-down/touch-start).
		Tools registered using \c RegisterLiveEditPluginTool() calls this
		automatically at appropriate time.

		@param	inFeatureName		Feature name to be used in live editing
									session. This can be any unique string like
									tool or widget name. Must not be empty
									string.

		@param	inEPFOverrideValue	Specify EPF (event processing frequency)
									override value for this manipulation
									session. Valid value range is from
									\c #ai::LiveEdit::EPF::kMinimumLimitValue
									to
									\c #ai::LiveEdit::EPF::kMaximumLimitValue.
									To use the global (default) EPF value use
									\c #ai::LiveEdit::EPF::kUseGlobaLimitValue.
		
		@note	This call must be balanced with a later call to
				\c #ChangeFinishNotify().

		@see	class \c #StLiveEditBeginFinishChangeNotifyHelper
		*/
	AIAPI AIErr (*ChangeBeginNotify) (const ai::LiteralString& inFeatureName,
		AIReal inEPFOverrideValue);

	/**	Widget manipulating art interactively must call this method when it
		starts processing a change event (mouse-drag/touch-move).
		Tools registered using \c RegisterLiveEditPluginTool() calls this
		automatically at appropriate time.

		@note	This call must be balanced with a later call to
				\c #ChangeContinueEndNotify() and must occur after a call to
				\c #ChangeBeginNotify() but before \c #ChangeFinishNotify().

		@see	class \c #StLiveEditContinueChangeNotifyHelper
		*/
	AIAPI AIErr (*ChangeContinueStartNotify) ();

	/**	Widget manipulating art interactively must call this method when it
		ends processing a change event (mouse-drag/touch-move).
		Tools registered using \c RegisterLiveEditPluginTool() calls this
		automatically at appropriate time.

		@note	This call must be balanced with an earlier call to
				\c #ChangeContinueStartNotify() and must occur after a call to
				\c #ChangeBeginNotify() but before \c #ChangeFinishNotify().

		@see	class \c #StLiveEditContinueChangeNotifyHelper
		*/
	AIAPI AIErr (*ChangeContinueEndNotify) ();

	/**	Widget manipulating art interactively must call this method at the end
		of the manipulation session (mouse-up/touch-end/touch-cancel).
		Tools registered using \c RegisterLiveEditPluginTool() calls this
		automatically at appropriate time.

		@note	This call must be balanced with an earlier call to
				\c #ChangeBeginNotify().

		@see	class \c #StLiveEditBeginFinishChangeNotifyHelper
		*/
	AIAPI AIErr (*ChangeFinishNotify) ();

	/**	Call this method to temporarily suspend Live Editing session.

		@note	This call must be balanced with a later call to
				\c #ResumeLiveEditing().

		@see	class \c #StLiveEditSuspender
		*/
	AIAPI AIErr (*SuspendLiveEditing) ();

	/**	Call this method to resume the suspended Live Editing session.

		@note	This call must be balanced with an earlier call to
				\c #SuspendLiveEditing().

		@see	class \c #StLiveEditSuspender
		*/
	AIAPI AIErr (*ResumeLiveEditing) ();

};


#include "AIHeaderEnd.h"
