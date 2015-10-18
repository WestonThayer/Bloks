#ifndef _AI_BASIC_TYPES_
#define _AI_BASIC_TYPES_

/*
* Name: AIBasicTypes.h
* Author: Started by Pushp
* Date: November, 2008
* Purpose: Adobe Illustrator Definitions of Basic Types
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 2008 Adobe Systems Incorporated.
* All rights reserved.
*
* NOTICE:  Adobe permits you to use, modify, and distribute this file
* in accordance with the terms of the Adobe license agreement
* accompanying it. If you have received this file from a source other
* than Adobe, then your use, modification, or distribution of it
* requires the prior written permission of Adobe.
*
*/

//TODO: To use C99 data types instead of raw data types and defined new data types for 64 bit readiness [Pushp]

#include <stddef.h>
#include "ASConfig.h"
#if defined(MAC_ENV)
#include <stdint.h>
#include <sys/types.h>
#endif



namespace ai
{
	typedef signed char		int8;
	typedef unsigned char	uint8;
	typedef signed short	int16;
	typedef unsigned short	uint16;

#if defined(_WIN32)
	typedef __int64				int64;
	typedef unsigned __int64	uint64;
	typedef __int32		int32;
	typedef unsigned __int32	uint32;
#endif

#if defined(MAC_ENV)
	typedef int64_t			int64;
	typedef u_int64_t			uint64;
	typedef int32_t		int32;
	typedef u_int32_t	uint32;
#endif
	typedef ptrdiff_t		sizediff_t;
	typedef intptr_t		intptr;
	typedef uintptr_t		uintptr;
	typedef size_t			SizeType;
}

#endif // _AI_BASIC_TYPES_
