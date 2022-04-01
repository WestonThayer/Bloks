/*************************************************************************
*
* ADOBE CONFIDENTIAL
*
* Copyright 2008 Adobe
*
* All Rights Reserved.
*
* NOTICE: Adobe permits you to use, modify, and distribute this file in
* accordance with the terms of the Adobe license agreement accompanying
* it. If you have received this file from a source other than Adobe,
* then your use, modification, or distribution of it requires the prior
* written permission of Adobe.
*
**************************************************************************/

#ifndef _AI_BASIC_TYPES_
#define _AI_BASIC_TYPES_

#include "ASConfig.h"

#include <stdint.h>
#include <stddef.h>

namespace ai
{
	using int8			= int8_t;
	using uint8			= uint8_t;
	using int16			= int16_t;
	using uint16		= uint16_t;
	using int32			= int32_t;
	using uint32		= uint32_t;
	using int64			= int64_t;
	using uint64		= uint64_t;

	using sizediff_t	= ptrdiff_t;
	using intptr		= intptr_t;
	using uintptr		= uintptr_t;
	using SizeType		= size_t;

} // namespace ai

using AIReal = double;
using AIFloat = float;

/** Double-byte numeric value */
using AIDouble = double;

/** Rectangle specified with \c #AIDouble coordinates.*/
struct AIDoubleRect {
    AIDouble left, top, right, bottom;
};

using AIRealRect = AIDoubleRect;
using AIRealRectPtr = AIRealRect*;

typedef struct _t_AIFloatRect {
	AIFloat left, top, right, bottom;
} AIFloatRect, *AIFloatRectPtr;

typedef struct _t_AIRealMatrix {
	AIReal a, b, c, d, tx, ty;
	/** Sets to Identity.*/
	void Init()
	{
		a = 1.0; b = 0.0;
		c = 0.0; d = 1.0;
		tx = 0.0; ty = 0.0;
	}
	bool operator==(const _t_AIRealMatrix& other) const
	{
		return a == other.a && b == other.b &&
			   c == other.c && d == other.d &&
			   tx == other.tx && ty == other.ty;
	}
} AIRealMatrix, *AIRealMatrixPtr;

typedef struct _t_AIRealPoint {
	AIReal h, v;
	bool operator==(const _t_AIRealPoint& other) const
	{
		return h == other.h && v == other.v;
	}
} AIRealPoint, *AIRealPointPtr;

// AIRect is the same size and layout as a Windows RECT.
/** Rectangle value in Windows (same as \c RECT) */
typedef struct _t_AIRect {
    /** Coordinate values */
    ai::int32 left, top, right, bottom;
} AIRect;

// AIPoint is the same size and layout as a Windows POINT.
/** Point value in Windows (same as \c Point) */
typedef struct _t_AIPoint  {
    /** Coordinate values */
    ai::int32 h, v;
} AIPoint;

//
//
// Platform dependant natively aligned structures
//
//

/** True (1) or false (0) */
#ifdef MAC_ENV
/** Mac OS only. the same as Mac OS \c Boolean.     */
typedef unsigned char AIBoolean;
#endif

#ifdef WIN_ENV
/** Windows only. the same as  Windows \c BOOL. */
typedef int AIBoolean;
#endif

#ifdef LINUX_ENV
typedef unsigned char AIBoolean;
#endif

#endif // _AI_BASIC_TYPES_

