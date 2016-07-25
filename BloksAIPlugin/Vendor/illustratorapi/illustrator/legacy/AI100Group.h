#ifndef __AI100Group__
#define __AI100Group__

/*
 *        Name:	AIGroup.h
 *   $Revision: 6 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 10.0 Group Object Suite.
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


#ifndef __AIGroup__
#include "AIGroup.h"
#endif


#include "AIHeaderBegin.h"



/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAI100GroupSuite			"AI Group Suite"
#define kAIGroupSuiteVersion2		AIAPI_VERSION(2)
#define kAI100GroupSuiteVersion		kAIGroupSuiteVersion2


/*******************************************************************************
 **
 **	Suite
 **
 **/

typedef struct {

	AIAPI AIErr (*GetGroupClipped) ( AIArtHandle group, AIBoolean *clipped );
	AIAPI AIErr (*SetGroupClipped) ( AIArtHandle group, AIBoolean clipped );

	AIAPI AIErr (*GetGroupMaskLock) ( AIArtHandle group, AIBoolean *maskLocked );
	AIAPI AIErr (*SetGroupMaskLock) ( AIArtHandle group, AIBoolean maskLocked );

} AI100GroupSuite;


#include "AIHeaderEnd.h"


#endif
