/*******************************************************************************
 *	ADOBE CONFIDENTIAL
 *
 *	Copyright 2018 Adobe
 *	All Rights Reserved.
 *
 *	NOTICE:  Adobe permits you to use, modify, and distribute this file in
 *	accordance with the terms of the Adobe license agreement accompanying
 *	it. If you have received this file from a source other than Adobe,
 *	then your use, modification, or distribution of it requires the prior
 *	written permission of Adobe.
*******************************************************************************/

#pragma once

/*******************************************************************************
 **
 **	Imports
 **
 **/

#include "AITypes.h"

#include "AIHeaderBegin.h"

/*******************************************************************************
 **
 **	Constants
 **
 **/


namespace ai
{
	namespace LiveEdit
	{

		// EPF (event processing frequency)
		namespace EPF
		{
			constexpr AIReal kMinimumLimitValue		{ 1.0 };	// 1000 ms per event
			constexpr AIReal kMaximumLimitValue		{ 60.0 };	// 1000/60 ms per event

			constexpr AIReal kUseGlobaLimitValue	{ 0.0 };	// Maps to system default
		}

	}
}

#include "AIHeaderEnd.h"
