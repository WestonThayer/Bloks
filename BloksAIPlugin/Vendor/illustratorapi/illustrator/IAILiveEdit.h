/*******************************************************************************
* ADOBE CONFIDENTIAL
*
* Copyright 2018 Adobe
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

#include "AILiveEdit.h"
#include "AILiveEditConstants.h"
#include "AutoSuite.h"


/*******************************************************************************
**
**	Variables
**
**/

extern_declare_suite_optional(AILiveEdit)	// Clients need to define separately
											// with extern_define_suite_optional


/*******************************************************************************
**
**	Utility Classes
**
**/

namespace ai
{

	// A class to wrap ChangeContinueStartNotify() and ChangeContinueEndNotify()
	// in a scope.
	class StLiveEditContinueChangeNotifyHelper final
	{
	public:
		StLiveEditContinueChangeNotifyHelper()
		{
			try
			{
				if (sAILiveEdit)
				{
					sAILiveEdit->ChangeContinueStartNotify();
				}
			}
			catch (...)
			{
			}
		}
		~StLiveEditContinueChangeNotifyHelper()
		{
			try
			{
				if (sAILiveEdit)
				{
					sAILiveEdit->ChangeContinueEndNotify();
				}
			}
			catch (...)
			{
			}
		}
	};

	// A class to wrap ChangeBeginNotify() and ChangeFinishNotify() in a scope.
	class StLiveEditBeginFinishChangeNotifyHelper final
	{
	public:
		StLiveEditBeginFinishChangeNotifyHelper(
			const LiteralString& inFeatureName,
			AIReal inEPFOverrideValue = LiveEdit::EPF::kUseGlobaLimitValue)
		{
			try
			{
				if (sAILiveEdit)
				{
					sAILiveEdit->ChangeBeginNotify(inFeatureName,
													inEPFOverrideValue);
				}
			}
			catch (...)
			{
			}
		}
		~StLiveEditBeginFinishChangeNotifyHelper()
		{
			try
			{
				if (sAILiveEdit)
				{
					sAILiveEdit->ChangeFinishNotify();
				}
			}
			catch (...)
			{
			}
		}
	};

	// A class to wrap SuspendLiveEditing() and ResumeLiveEditing() in a scope.
	class StLiveEditSuspender final
	{
	public:
		StLiveEditSuspender()
		{
			try
			{
				if (sAILiveEdit)
				{
					sAILiveEdit->SuspendLiveEditing();
				}
			}
			catch (...)
			{
			}
		}
		~StLiveEditSuspender()
		{
			try
			{
				if (sAILiveEdit)
				{
					sAILiveEdit->ResumeLiveEditing();
				}
			}
			catch (...)
			{
			}
		}
	};

}	// namespace ai
