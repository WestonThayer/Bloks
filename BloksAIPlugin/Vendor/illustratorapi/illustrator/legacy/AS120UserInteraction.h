#ifndef __AS120UserInteraction__
#define __AS120UserInteraction__

/*
 *        Name:	AS120UserInteraction.h
 *   $Revision: 1 $
 *      Author:	 Andy Bachorski
 *        Date:	   
 *     Purpose:	Adobe Standard User Interaction Suite
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2001-2007 Adobe Systems Incorporated.
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

#include "ASUserInteraction.h"
#include "AIHeaderBegin.h"

/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAS120UserInteractionSuite			"AS User Interaction Suite"
#define kASUserInteractionSuiteVersion1		1
#define kAS120UserInteractionSuiteVersion	kASUserInteractionSuiteVersion1


/*******************************************************************************
 **
 **	Suite
 **
 **/

typedef struct {

	//	The allowable level of interaction for the application (server).  
	//	This property is the maximum level of interaction allowed with regard 
	//	to displaying modal dialogs & alerts.  Value is persistent until 
	//	explicitly changed.  
	//
	//	Will be exposed in application's scripting interface as a property of 
	//	the application.  Could be exposed in application preference dialog.
	//
	//	Default value - kASInteractWithAll
	//
	ASAPI ASInteractionAllowed	(*GetInteractionAllowed) ( void );
	ASAPI ASErr					(*SetInteractionAllowed) ( ASInteractionAllowed allowed );
	

	//	Check to see if it is allowable to interact with the user in the current 
	//	application context.  Value returned is determined by the settings of 
	//	InteractionAllowed and by the current script execution context.
	//
	ASAPI ASBoolean 			(*InteractWithUser) ( void );

} AS120UserInteractionSuite;


#include "AIHeaderEnd.h"

#endif //	__AS120UserInteraction__

