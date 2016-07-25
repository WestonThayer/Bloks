//========================================================================================
//  
//  $File: //ai_stream/rel_20_0/devtech/sdk/public/samplecode/common/mac/Plugin.r $
//
//  $Revision: #1 $
//
//  Copyright 1987 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

// This resource file handles PIPL resources for the Illustrator SDK projects.

#include "PiPL.r"

//This defines the name of the plug-in, this is left blank otherwise this file would be project specific
#ifndef PIPL_PLUGIN_NAME
#error Need to define plugin name
//#define PIPL_PLUGIN_NAME ""
#endif

//Define this if your plugin exports any suites. This will guarantee them being earlier in the load order
#ifndef PIPL_EXPORT
#define PIPL_EXPORT 0
#else
// There is no need to define suites, just turning on the export flag is enough, however,
// if you do define exported suites, the list should like the one below: 
// The first entry is the suite name, the second is the suite version.
	#ifndef PIPL_EXPORTED_SUITES
	#define PIPL_EXPORTED_SUITES { "Exported Suite", 1 }
	#endif
#endif

#ifndef PIPL_MESSAGE
#define PIPL_MESSAGE 0
//Define PIPL_MESSAGES to a List of the Messages you want from PiPL.r if you want to be able to use messages
//#define PIPL_MESSAGES startupRequired,purgeCache,shutdownRequired,acceptProperty
#endif

//If you are an adaptor plugin, define this
#ifndef PIPL_ADAPTOR
#define PIPL_ADAPTOR 0
#endif

#define TARGET ADBECodeCarbon
#ifndef PPC_PIPL_ENTRY
#define PPC_PIPL_ENTRY	0,0,""
#endif
#define TARGET1 ADBECodeMachO
#ifndef PIPL_ENTRY
#define PIPL_ENTRY	""
#endif
#define TARGET2 ADBECodeMacIntel32
#ifndef PIPL_ENTRY
#define PIPL_ENTRY	""
#endif

resource 'PiPL' (16000, PIPL_PLUGIN_NAME " PiPL", purgeable)
{
	{	
		ADBEKind {'SPEA'},
		InterfaceVersion { 2 },
		TARGET 
		{
			PPC_PIPL_ENTRY
		},
		TARGET1
		{
		    PIPL_ENTRY
		},
		TARGET2
		{
			PIPL_ENTRY
		},
	#if PIPL_EXPORT
		Exports 
		{
			PIPL_EXPORTED_SUITES
		},
	#endif
	#if PIPL_MESSAGE
		Messages 
		{
			PIPL_MESSAGES
		},
	#endif
	#if PIPL_ADAPTOR
		AdapterVersion { 2 }
	#endif
		InternalName
		{
			PIPL_PLUGIN_NAME
		}
	}
};
