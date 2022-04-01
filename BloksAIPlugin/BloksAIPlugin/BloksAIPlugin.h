#ifndef __BloksAIPlugin_h__
#define __BloksAIPlugin_h__

#include "IllustratorSDK.h"
#include "Plugin.hpp"
#include "BloksAIPluginID.h"

/**	Creates a new BloksAIPlugin.
@param pluginRef IN unique reference to this plugin.
@return pointer to new BloksAIPlugin.
*/
Plugin* AllocatePlugin(SPPluginRef pluginRef);

/**	Reloads the BloksAIPlugin class state when the plugin is
reloaded by the application.
@param plugin IN pointer to plugin being reloaded.
*/
void FixupReload(Plugin* plugin);

/**	Hooks BloksAIPlugin up as an Illustrator plug-in.
@ingroup BloksAIPlugin
*/
class BloksAIPlugin : public Plugin
{
public:
	/** Constructor.
	@param pluginRef IN reference to this plugin.
	*/
	BloksAIPlugin(SPPluginRef pluginRef);

	/** Destructor.
	*/
	virtual ~BloksAIPlugin();

	/**	Restores state of BloksAIPlugin during reload.
	*/
	FIXUP_VTABLE_EX(BloksAIPlugin, Plugin); // override

	/**	Initializes the plugin.
	@param message IN message sent by the plugin manager.
	@return kNoErr on success, other ASErr otherwise.
	*/
	ASErr StartupPlugin(SPInterfaceMessage * message); // override

	/**	Removes the plugin.
	@param message IN message sent by the plugin manager.
	@return kNoErr on success, other ASErr otherwise.
	*/
	ASErr ShutdownPlugin(SPInterfaceMessage * message); // override

protected:
	virtual ASErr Notify(AINotifierMessage* message); // override

private:
	AINotifierHandle fRegisterEventNotifierHandle;
	AINotifierHandle fRegisterSelectionChangedHandle;
	AINotifierHandle fRegisterUndoHandle;
	AINotifierHandle fRegisterRulerHandle;
};

#endif
