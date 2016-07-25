#ifndef __AI90Menu__
#define __AI90Menu__

/*
 *        Name:	AI90Menu.h
 *   $Revision: 10 $
 *      Author:	 
 *        Date:	   
 *     Purpose: Adobe Illustrator Menu Suites from before AI 10	
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

#ifndef __AIPlugin__
#include "AIPlugin.h"
#endif

#ifndef __ASHelp__
#include "ASHelp.h"
#endif

#ifndef __AIMenu__
#include "AIMenu.h"
#endif


#include "AIHeaderBegin.h"


/*******************************************************************************
 **
 **	Constants
 **
 **/

#define kAI90MenuSuite		"AI Menu Suite"
#define kAIMenuVersion5		AIAPI_VERSION(5)	// For AI7
#define kAIMenuVersion6		AIAPI_VERSION(6)	// For AI9



/*******************************************************************************
 **
 **	Suite
 **
 **/

// version 5
typedef struct {

	AIAPI AIErr (*AddMenuItem) ( SPPluginRef self, const char *name,
				AIPlatformAddMenuItemData *data, AIMenuItemOption options,
				AIMenuItemHandle *menuItem );

	AIAPI AIErr (*GetMenuItemName) ( AIMenuItemHandle menuItem, const char** name );
	AIAPI AIErr (*GetMenuItemOptions) ( AIMenuItemHandle menuItem, AIMenuItemOption *options );
	AIAPI AIErr (*SetMenuItemOptions) ( AIMenuItemHandle menuItem, AIMenuItemOption options );
	AIAPI AIErr (*GetMenuItemPlugin) ( AIMenuItemHandle menuItem,
				SPPluginRef *plugin );

	AIAPI AIErr (*CountMenuItems) ( long *count );
	AIAPI AIErr (*GetNthMenuItem) ( long n, AIMenuItemHandle *menuItem );

	AIAPI AIErr (*GetPlatformMenuItem) ( AIMenuItemHandle menuItem,
				AIPlatformMenuItem *platformMenuItem );

	AIAPI AIErr (*UpdateMenuItemAutomatically) ( AIMenuItemHandle menuItem,
				long action,
				long ifObjectIsInArtwork, long ifObjectIsNotInArtwork,
				long ifObjectIsSelected, long ifObjectIsNotSelected,
				long ifIsTrue, long ifIsNotTrue );
	AIAPI AIErr (*GetUpdateFlags)( long *inArtwork, long *isSelected, long *isTrue );
	/*-------------------------------------------------------------------------------------------*/
		
	AIAPI AIErr (*EnableItem) ( AIMenuItemHandle menuItem);
	AIAPI AIErr (*DisableItem) ( AIMenuItemHandle menuItem);
	AIAPI AIErr (*GetItemText) ( AIMenuItemHandle menuItem, char* itemCString );	// Get menuItem text. Different from GetMenuItemName() where the itemName doesn't got localized.
																					// where the length of itemCString is 256.

	AIAPI AIErr (*SetItemText) ( AIMenuItemHandle menuItem, const char* itemCString );	// Set menuItem text.
	AIAPI AIErr (*CheckItem) ( AIMenuItemHandle menuItem, AIBoolean bCheckIt );

	/* NOTE: SetItemIcon: On MSWindows: MAKEINTRESOURCE(iconSelector + 256) is the
		the bitmap resource ID for the menuItem.
		NOTE (2): SetItemIcon() will pass in the hInstance for the bitmap.
	*/
	AIAPI AIErr (*SetItemIcon) ( AIMenuItemHandle menuItem, short iconSelector );

	AIAPI AIErr (*GetItemMenuGroup) ( AIMenuItemHandle menuItem, AIMenuGroup *group );
	AIAPI AIErr (*AddMenuGroup) ( const char *name, AIMenuGroupOption options, const char *nearGroup,
				AIMenuGroup *group );
	AIAPI AIErr (*AddMenuGroupAsSubMenu) ( const char *name, AIMenuGroupOption options, AIMenuItemHandle menuItem, AIMenuGroup *group);
	AIAPI AIErr (*GetMenuGroupName) ( AIMenuGroup group, const char **name );
	AIAPI AIErr (*GetMenuGroupOptions) ( AIMenuGroup group, AIMenuGroupOption *options );
	AIAPI AIErr (*SetMenuGroupOptions) ( AIMenuGroup group, AIMenuGroupOption options );
	AIAPI AIErr (*GetMenuGroupRange) ( AIMenuGroup group, AIPlatformMenuHandle *theMenu,
				short *firstItem, short *numItems );
	AIAPI AIErr (*CountMenuGroups) ( long *count );
	AIAPI AIErr (*GetNthMenuGroup) ( long n, AIMenuGroup *group );

	AIAPI AIErr (*GetItemCmd) ( AIMenuItemHandle menuItem, short *cmdChar, short *modifiers );
	AIAPI AIErr (*SetItemCmd) ( AIMenuItemHandle menuItem, char cmdChar, short modifiers );

	// Currently supports function keys 1-15 (note: 1-based)
	AIAPI AIErr (*GetItemFunctionKey) ( AIMenuItemHandle menuItem, short *fkey, short *modifiers );
	AIAPI AIErr (*SetItemFunctionKey) ( AIMenuItemHandle menuItem, short fkey, short modifiers );
	
	AIAPI AIErr (*GetItemHelpID) ( AIMenuItemHandle menuItem, ASHelpID *helpID );
	AIAPI AIErr (*SetItemHelpID) ( AIMenuItemHandle menuItem, ASHelpID helpID );
	
} AIMenuSuite5;


// version 6
typedef struct {

	AIAPI AIErr (*AddMenuItem) ( SPPluginRef self, const char *name,
				AIPlatformAddMenuItemData *data, AIMenuItemOption options,
				AIMenuItemHandle *menuItem );

	AIAPI AIErr (*GetMenuItemName) ( AIMenuItemHandle menuItem, const char **name );
	AIAPI AIErr (*GetMenuItemOptions) ( AIMenuItemHandle menuItem, AIMenuItemOption *options );
	AIAPI AIErr (*SetMenuItemOptions) ( AIMenuItemHandle menuItem, AIMenuItemOption options );
	AIAPI AIErr (*GetMenuItemPlugin) ( AIMenuItemHandle menuItem,
				SPPluginRef *plugin );

	AIAPI AIErr (*CountMenuItems) ( long *count );
	AIAPI AIErr (*GetNthMenuItem) ( long n, AIMenuItemHandle *menuItem );

	AIAPI AIErr (*GetPlatformMenuItem) ( AIMenuItemHandle menuItem,
				AIPlatformMenuItem *platformMenuItem );

	AIAPI AIErr (*UpdateMenuItemAutomatically) ( AIMenuItemHandle menuItem,
				long action,
				long ifObjectIsInArtwork, long ifObjectIsNotInArtwork,
				long ifObjectIsSelected, long ifObjectIsNotSelected,
				long ifIsTrue, long ifIsNotTrue );
	AIAPI AIErr (*GetUpdateFlags)( long *inArtwork, long *isSelected, long *isTrue );
	/*-------------------------------------------------------------------------------------------*/
		
	AIAPI AIErr (*EnableItem) ( AIMenuItemHandle menuItem);
	AIAPI AIErr (*DisableItem) ( AIMenuItemHandle menuItem);
	AIAPI AIErr (*GetItemText) ( AIMenuItemHandle menuItem, char* itemCString );	// Get menuItem text. Different from GetMenuItemName() where the itemName doesn't got localized.
																					// where the length of itemCString is 256.

	AIAPI AIErr (*SetItemText) ( AIMenuItemHandle menuItem, const char* itemCString );	// Set menuItem text.
	AIAPI AIErr (*CheckItem) ( AIMenuItemHandle menuItem, AIBoolean bCheckIt );

	/* NOTE: SetItemIcon: On MSWindows: MAKEINTRESOURCE(iconSelector + 256) is the
		the bitmap resource ID for the menuItem.
		NOTE (2): SetItemIcon() will pass in the hInstance for the bitmap.
	*/
	AIAPI AIErr (*SetItemIcon) ( AIMenuItemHandle menuItem, short iconSelector );

	AIAPI AIErr (*GetItemMenuGroup) ( AIMenuItemHandle menuItem, AIMenuGroup *group );
	AIAPI AIErr (*AddMenuGroup) ( const char *name, AIMenuGroupOption options, const char *nearGroup,
				AIMenuGroup *group );
	AIAPI AIErr (*AddMenuGroupAsSubMenu) ( const char *name, AIMenuGroupOption options, AIMenuItemHandle menuItem, AIMenuGroup *group);
	AIAPI AIErr (*GetMenuGroupName) ( AIMenuGroup group, const char **name );
	AIAPI AIErr (*GetMenuGroupOptions) ( AIMenuGroup group, AIMenuGroupOption *options );
	AIAPI AIErr (*SetMenuGroupOptions) ( AIMenuGroup group, AIMenuGroupOption options );
	AIAPI AIErr (*GetMenuGroupRange) ( AIMenuGroup group, AIPlatformMenuHandle *theMenu,
				short *firstItem, short *numItems );
	AIAPI AIErr (*CountMenuGroups) ( long *count );
	AIAPI AIErr (*GetNthMenuGroup) ( long n, AIMenuGroup *group );

	AIAPI AIErr (*GetItemCmd) ( AIMenuItemHandle menuItem, short *cmdChar, short *modifiers );
	AIAPI AIErr (*SetItemCmd) ( AIMenuItemHandle menuItem, char cmdChar, short modifiers );

	// Currently supports function keys 1-15 (note: 1-based)
	AIAPI AIErr (*GetItemFunctionKey) ( AIMenuItemHandle menuItem, short *fkey, short *modifiers );
	AIAPI AIErr (*SetItemFunctionKey) ( AIMenuItemHandle menuItem, short fkey, short modifiers );
	
	AIAPI AIErr (*GetItemHelpID) ( AIMenuItemHandle menuItem, ASHelpID *helpID );
	AIAPI AIErr (*SetItemHelpID) ( AIMenuItemHandle menuItem, ASHelpID helpID );
	
	// new for version 6
			
	AIAPI AIErr (*IsItemEnabled) ( AIMenuItemHandle menuItem, ASBoolean *bEnabled);
	AIAPI AIErr (*IsItemChecked) ( AIMenuItemHandle menuItem, AIBoolean *bCheckIt );
	
} AIMenuSuite6;


#include "AIHeaderEnd.h"

#endif
