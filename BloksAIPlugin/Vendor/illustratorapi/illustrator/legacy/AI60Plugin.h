#ifndef __AI60Plugin__
#define __AI60Plugin__

/*
 *        Name:	AIPlugin.h
 *   $Revision: 4 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 6.0 Plug-in Suite.
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

#ifndef __AI60Basic__
#include "AI60Basic.h"
#endif

#ifndef __SPPlugins__
#include "SPPlugs.h"
#endif


#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAI60PluginSuite				"AI Plugin Suite"
#define kAI60PluginSuiteVersion			AIAPI_VERSION(2)
#define kAI60PluginVersion				kAI60PluginSuiteVersion
#if Macintosh
#define kAI60MacPluginSuite				"AI Mac Plugin Suite"
#define kAI60MacPluginSuiteVersion		AIAPI_VERSION(2)
#define kAI60MacPluginVersion			kAI60MacPluginSuiteVersion
#endif


// These are a plug-in's messages:
#define kSelectorAI60StartupPlugin	"AI Startup Plug-in"
#define kSelectorAI60UnloadPlugin		"AI Unload Plug-in"
#define kSelectorAI60ReloadPlugin		"AI Reload Plug-in"
#define kSelectorAI60ShutdownPlugin	"AI Shutdown Plug-in"
#define kSelectorAI60AboutPlugin		"AI About Plug-in"


// These are the options available to a plug-in.
#define kPluginWantsResultsAutoSelectedOption	(1L<<1)


// These are a plug-in's possible states.
#define kPluginIsBuiltinState					(1L<<0)
#define kPluginIsResidentState					(1L<<1)
#define kPluginIsBrokenState					(1L<<2)
#define kPluginIsStartedState					(1L<<3)

#define kCantGetPluginCodePropertyErr		'PLCP'
#define kCantGetPluginCodeErr				'PLCO'
#define kPluginIsBrokenErr					'PLBR'
#define kPluginInternalErr					'PLIN'
#define kCantGetPiPLErr						'PLPI'
#define kCorruptPiPLErr						'PLP?'


/*******************************************************************************
 **
 ** Types
 **
 **/

// This is a reference to a plug-in. It is never dereferenced.
//typedef struct _t_AIPluginOpaque *AIPluginHandle;
typedef  SPPluginRef AIPluginHandle;

// The contents of a plug-in message.
typedef struct {
	AIPluginHandle self;
	void *globals;
	AIBasicSuite *basic;
} AIPluginData;

typedef struct {
	AIPluginData d;
} AIPluginMessage;


/*******************************************************************************
 **
 ** Suite
 **
 **/

typedef struct {

	AIAPI AIErr (*GetPluginOptions) ( AIPluginHandle plugin, long *options );
	AIAPI AIErr (*SetPluginOptions) ( AIPluginHandle plugin, long options );
	
	AIAPI AIErr (*GetPluginInterfaceVersion) ( AIPluginHandle plugin, long *interfaceVersion );
	AIAPI AIErr (*GetPluginGlobals) ( AIPluginHandle plugin, void **globals );
	AIAPI AIErr (*SetPluginGlobals) ( AIPluginHandle plugin, void *globals );
	AIAPI AIErr (*GetPluginState) ( AIPluginHandle plugin, long *state );
	
	AIAPI AIErr (*CountPlugins) ( long *count );
	AIAPI AIErr (*GetNthPlugin) ( long n, AIPluginHandle *plugin );
	AIAPI AIErr (*GetRunningPlugin) ( AIPluginHandle *plugin );
	
	AIAPI AIErr (*SetupPluginData) ( AIPluginHandle plugin, AIPluginData *data );
	AIAPI AIErr (*CallPlugin) ( AIPluginHandle plugin, const char *selector, void *message );
	AIAPI AIErr (*EmptyPluginData) ( AIPluginHandle plugin, AIPluginData *data );

} AI60PluginSuite;


#if Macintosh

typedef char AIISAType;

typedef struct {

	AIAPI AIErr (*MacXGetPluginFSSpec) ( AIPluginHandle plugin, SPPlatformFileSpecification *file );
	AIAPI AIErr (*MacXGetPluginArchitecture) ( AIPluginHandle plugin, AIISAType *architecture );

} AIMacPluginSuite;
#endif


#include "AIHeaderEnd.h"


#endif
