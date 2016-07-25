#ifndef __AI100Folders__
#define __AI100Folders__

/*
 *        Name:	AI100Folders.h
 *     Purpose:	Adobe Illustrator 10.0 Folders Suite.
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

#include "AIFolders.h"

#include "AIHeaderBegin.h"

/*******************************************************************************
 **
 **	Suite name and version
 **
 **/

#define kAI100FoldersSuite				kAIFoldersSuite
#define kAIFoldersSuiteVersion1			AIAPI_VERSION(1)
#define kAI100FoldersSuiteVersion		kAIFoldersSuiteVersion1


 /*******************************************************************************
 **
 **	Suite
 **
 **/


typedef struct {

	// - version 1 api - 
	AIAPI AIErr (*GetFolderName)(AIFolderType type, char *name); // kMaxPathLength size buffer assumed, folder name only (not path).

} AI100FoldersSuite;


#include "AIHeaderEnd.h"


#endif
