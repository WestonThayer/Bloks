#ifndef __AI90PluginGroup__
#define __AI90PluginGroup__

/*
 *        Name:	AI90PluginGroup.h
 *     Purpose:	Adobe Illustrator 9.0 Plugin Group Suite.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1995-2007 Adobe Systems Incorporated.
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

#include "AIPluginGroup.h"


#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAI90PluginGroupSuite			"AI Plugin Group Suite"
#define kAI90PluginGroupSuiteVersion	AIAPI_VERSION(2)
#define kAI90PluginGroupVersion			kAI90PluginGroupSuiteVersion




/*******************************************************************************
 **
 **	Suite
 **
 **/

typedef struct {

	AIAPI AIErr (*AddAIPluginGroup) ( SPPluginRef self, char *name, AIAddPluginGroupData *data, long options, AIPluginGroupHandle *entry );
	AIAPI AIErr (*UseAIPluginGroup) ( AIArtHandle art, AIPluginGroupHandle entry );

	AIAPI AIErr (*GetAIPluginGroupName) ( AIPluginGroupHandle entry, char **name );
	AIAPI AIErr (*GetAIPluginGroupVersion) ( AIPluginGroupHandle entry, long *major, long *minor );
	AIAPI AIErr (*GetAIPluginGroupDescription) ( AIPluginGroupHandle entry, char **desc );
	AIAPI AIErr (*GetAIPluginGroupOptions) ( AIPluginGroupHandle entry, long *options );
	AIAPI AIErr (*GetAIPluginGroupPlugin) ( AIPluginGroupHandle entry, SPPluginRef *plugin );

	AIAPI AIErr (*CountAIPluginGroups) ( long *count );
	AIAPI AIErr (*GetNthAIPluginGroup) ( long index, AIPluginGroupHandle *entry );

	AIAPI AIErr (*GetPluginArtName) ( AIArtHandle art, char **name );
	AIAPI AIErr (*SetPluginArtName) ( AIArtHandle art, char *name );
	AIAPI AIErr (*GetPluginArtVersion) ( AIArtHandle art, long *major, long *minor );
	AIAPI AIErr (*SetPluginArtVersion) ( AIArtHandle art, long major, long minor );
	AIAPI AIErr (*GetPluginArtPluginGroup) ( AIArtHandle art,  AIPluginGroupHandle *entry );
	AIAPI AIErr (*SetPluginArtPluginGroup) ( AIArtHandle art );
	AIAPI AIErr (*GetPluginArtEditArt) ( AIArtHandle art, AIArtHandle *editArt );
	AIAPI AIErr (*SetPluginArtEditArt) ( AIArtHandle art, AIArtHandle editArt );
	AIAPI AIErr (*GetPluginArtResultArt) ( AIArtHandle art, AIArtHandle *resultArt  );
	AIAPI AIErr (*SetPluginArtResultArt) ( AIArtHandle art, AIArtHandle resultArt  );
	
	AIAPI AIErr (*GetPluginArtDataCount) ( AIArtHandle art, unsigned long *count );
	AIAPI AIErr (*SetPluginArtDataCount) ( AIArtHandle art, unsigned long count );
	AIAPI AIErr (*GetPluginArtDataRange) ( AIArtHandle art, void *data, unsigned long index, unsigned long count );
	AIAPI AIErr (*SetPluginArtDataRange) ( AIArtHandle art, void *data, unsigned long index, unsigned long count );

	AIAPI AIErr (*MarkPluginArtDirty) ( AIArtHandle art );	// say that an AIUpdateArt notification is needed
	AIAPI AIErr (*MarkPluginArtClean) ( AIArtHandle art );	// say that one isn't

} AI90PluginGroupSuite;

/* Note on MarkPluginArtDirty and MarkPluginArtClean:

	Ordinarily, AIPluginGroup takes care of detecting when a PluginGroup object needs
	to have the resultArt rebuilt. (An AI Update message is sent once when the object
	is first created, and thereafter whenever the group's data or any object in the
	editGroup has been edited outside of the AI Update message handling itself.) 
	But occasionally the default rules are inadequate.

	Some objects may have external dependencies not detectable by the suite support,
	such as referencing a pattern or other global object, an artwork attribute such
	as the page size, etc. Such plugins will usually detect relevant changes via other
	notifications, and for ease of implementation, may wish to trigger the update by
	calling MarkPluginArtDirty.
	
	Conversely, it is often the case that in processing a menu command, tool action,
	etc., a PluginGroup object will first modify the editArt contents and/or the
	object's data, and then rebuild the resultArt. The modifications to the editArt
	or data will mark the plugin object dirty, causing a redundant update if the
	resultArt has already been synced. Calling MarkPluginArtClean will prevent this.
*/

#include "AIHeaderEnd.h"

#endif

