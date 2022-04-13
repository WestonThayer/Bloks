//========================================================================================
//
//  ADOBE CONFIDENTIAL
//
//  File: PluginCommon.hpp
//  Author: Angad Gupta
//  DateTime: 07-June-2021
//  Change: Macros to maching c/c++ externs.
//
//  Copyright 2021 Adobe Systems Incorporated
//  All Rights Reserved.
//
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//
//========================================================================================

#pragma once

#if defined(STATIC_LINKED_PLUGIN)
	#define AI_EXTERN_C_BEGIN
	#define AI_EXTERN_C_END
#else
	#if defined(__cplusplus)
		#define AI_EXTERN_C_BEGIN 		extern "C"  {
		#define AI_EXTERN_C_END			} //extern "C"
	#else
		#define AI_EXTERN_C_BEGIN
		#define AI_EXTERN_C_END
	#endif
#endif //!STATIC_LINKED_PLUGIN

