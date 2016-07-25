#ifndef __AI60Property__
#define __AI60Property__

/*
 *        Name:	AIProperty.h
 *   $Revision: 2 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 6.0 Plug-in Property Suite.
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

#ifndef __AITypes__
#include "AITypes.h"
#endif

#ifndef __AI60Plugin__
#include "AI60Plugin.h"
#endif


#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kSelectorAI60AcquireProperty	"AI Acquire Property"
#define kSelectorAI60ReleaseProperty	"AI Release Property"


/*******************************************************************************
 **
 ** Types
 **
 **/

typedef struct {

	AIPluginData d;

	long vendorID;
	long propertyKey;
	long propertyID;

	void *property;
	long refCon;
	AIBoolean cacheable;

} AIPropertyMessage;


#include "AIHeaderEnd.h"


#endif
