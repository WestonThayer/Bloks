#include "IllustratorSDK.h"
#include "BloksAIPlugin.h"
#include "BloksAIPluginSuites.h"
#include "SDKPlugPlug.h"
#include "AICSXS.h"
#include "AIMenuCommandNotifiers.h"

Plugin* AllocatePlugin(SPPluginRef pluginRef)
{
	return new BloksAIPlugin(pluginRef);
}

void FixupReload(Plugin* plugin)
{
	BloksAIPlugin::FixupVTable((BloksAIPlugin*) plugin);
}

BloksAIPlugin::BloksAIPlugin(SPPluginRef pluginRef) : Plugin(pluginRef)
{
	fRegisterSelectionChangedHandle = NULL;
	fRegisterUndoHandle = NULL;
	fRegisterRulerHandle = NULL;
	strncpy(fPluginName, kBloksAIPluginName, kMaxStringLength);
}

BloksAIPlugin::~BloksAIPlugin()
{
}

ASErr BloksAIPlugin::StartupPlugin(SPInterfaceMessage *message)
{
	ASErr error = kNoErr;
	error = Plugin::StartupPlugin(message);

	if (!error)
	{
		// Keep ourselves in memory to recieve events
		//error = Plugin::LockPlugin(true);
	}

	if (!error)
	{
		// Register for selection changed
		error = sAINotifier->AddNotifier(
			fPluginRef,
			"Bloks",
			kAIArtSelectionChangedNotifier,
			&fRegisterSelectionChangedHandle);
	}

	if (!error)
	{
		// Register for undo
		error = sAINotifier->AddNotifier(
			fPluginRef,
			"Bloks",
			kAIUndoCommandPreNotifierStr,
			&fRegisterUndoHandle);
	}

	if (!error)
	{
		// Register for show/hide rulers
		error = sAINotifier->AddNotifier(
			fPluginRef,
			"Bloks",
			kAIShowHideRulersCommandPreNotifierStr,
			&fRegisterRulerHandle);
	}

	sAIUser->MessageAlert(ai::UnicodeString("Hello from BloksAIPlugin!"));

	return error;
}

ASErr BloksAIPlugin::ShutdownPlugin(SPInterfaceMessage *message)
{
	ASErr error = kNoErr;

	if (!error)
	{
		// Allow ourselves to leave memory
		//error = Plugin::LockPlugin(false);
	}

	sAIUser->MessageAlert(ai::UnicodeString("Goodbye from BloksAIPlugin!"));

	if (!error)
	{
		error = Plugin::ShutdownPlugin(message);
	}

	return error;
}

ASErr BloksAIPlugin::Notify(AINotifierMessage* message)
{
	ASErr error = kNoErr;

	if (message->notifier == fRegisterSelectionChangedHandle)
	{
		csxs::event::EventErrorCode result = csxs::event::kEventErrorCode_Success;
		SDKPlugPlug plug;
		plug.Load(sAIFolders);

		csxs::event::Event ev = {
			"com.adobe.csxs.events.SelectionChanged",
			csxs::event::kEventScope_Application,
			"ILST",
			"microsoft.design.bloks",
			"selectionchanged"
		};

		result = plug.DispatchEvent(&ev);

		if (result != csxs::event::kEventErrorCode_Success)
		{
			error = 1;
		}

		plug.Unload();
	}
	else if (message->notifier == fRegisterUndoHandle)
	{
		csxs::event::EventErrorCode result = csxs::event::kEventErrorCode_Success;
		SDKPlugPlug plug;
		plug.Load(sAIFolders);

		csxs::event::Event ev = {
			"com.adobe.csxs.events.PreUndo",
			csxs::event::kEventScope_Application,
			"ILST",
			"microsoft.design.bloks",
			"preundo"
		};

		result = plug.DispatchEvent(&ev);

		if (result != csxs::event::kEventErrorCode_Success)
		{
			error = 1;
		}

		plug.Unload();
	}
	else if (message->notifier == fRegisterRulerHandle)
	{
		csxs::event::EventErrorCode result = csxs::event::kEventErrorCode_Success;
		SDKPlugPlug plug;
		plug.Load(sAIFolders);

		csxs::event::Event ev = {
			"com.adobe.csxs.events.PreShowHideRulers",
			csxs::event::kEventScope_Application,
			"ILST",
			"microsoft.design.bloks",
			"preshowhiderulers"
		};

		result = plug.DispatchEvent(&ev);

		if (result != csxs::event::kEventErrorCode_Success)
		{
			error = 1;
		}

		plug.Unload();
	}

	return error;
}
