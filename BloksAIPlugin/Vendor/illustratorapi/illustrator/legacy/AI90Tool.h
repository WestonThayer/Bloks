/*
 *        Name:	AI90Tool.h
 *   $Revision: #5 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 9.0 Tool Suite.
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
#ifndef __AI90Tool__
#define __AI90Tool__



/*******************************************************************************
 **
 **	Imports
 **
 **/

#include "AITool.h"

#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAI90ToolSuite			kAIToolSuite
#define kAIToolSuiteVersion8	AIAPI_VERSION(8)
#define kAI90ToolSuiteVersion	kAIToolSuiteVersion8

/*******************************************************************************
 **
 **	Suite
 **
 **/

typedef struct {

	AIAPI AIErr (*AddTool) ( SPPluginRef self, char *name,
				AIAddToolData *data, long options, 
				AIToolHandle *tool );
	
	AIAPI AIErr (*GetToolName) ( AIToolHandle tool, char **name );
	AIAPI AIErr (*GetToolOptions) ( AIToolHandle tool, long *options );
	AIAPI AIErr (*SetToolOptions) ( AIToolHandle tool, long options );
	AIAPI AIErr (*GetToolPlugin) ( AIToolHandle tool, SPPluginRef *plugin );

	AIAPI AIErr (*GetSelectedTool) ( AIToolHandle *tool );
	AIAPI AIErr (*SetSelectedTool) ( AIToolHandle tool );

	AIAPI AIErr (*CountTools) ( long *count );
	AIAPI AIErr (*GetNthTool) ( long n, AIToolHandle *tool );

	AIAPI AIErr (*GetToolHandleFromNumber) ( AIToolType toolNum,  AIToolHandle *tool );
	AIAPI AIErr (*GetToolNumberFromName) ( char *name, AIToolType *toolNum );
	AIAPI AIErr (*GetToolNumberFromHandle) ( AIToolHandle tool, AIToolType *toolNum );
	AIAPI AIErr (*GetToolNameFromNumber) (AIToolType toolNum, char **name);   // Caller must copy result immediately

	AIAPI AIErr (*GetToolTitle) ( AIToolHandle tool, char **title );
	AIAPI AIErr (*SetToolTitle) ( AIToolHandle tool, char *title );
	AIAPI AIErr (*GetToolIcon) ( AIToolHandle tool, ADMIconRef *icon );
	AIAPI AIErr (*SetToolIcon) ( AIToolHandle tool, ADMIconRef icon );
	AIAPI AIErr (*GetTooltip) ( AIToolHandle tool, char **tooltip );
	AIAPI AIErr (*SetTooltip) ( AIToolHandle tool, char *tooltip );
	AIAPI AIErr (*GetToolHelpID) ( AIToolHandle tool, ASHelpID *helpID );
	AIAPI AIErr (*SetToolHelpID) ( AIToolHandle tool, ASHelpID helpID );

	AIAPI AIErr (*SetToolInfoVars) ( AIToolHandle tool, const long * infoVars );
	AIAPI AIErr (*SetToolInfoVarValues) ( const long *infoVars,  void **values );
	
	AIAPI AIErr (*SystemHasPressure) ( ASBoolean *hasPressure );
	
} AI90ToolSuite;


#include "AIHeaderEnd.h"


#endif
