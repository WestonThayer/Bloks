#include "IllustratorSDK.h"
#include "BloksAIPlugin.h"
#include "BloksAIPluginSuites.h"
#include "SDKPlugPlug.h"
#include "AICSXS.h"

#define BLOKS_EVENT_ID "com.adobe.csxs.events.SilentTransformRequestedEvent"

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
	fRegisterEventNotifierHandle = NULL;
	fRegisterSelectionChangedHandle = NULL;
	strncpy(fPluginName, kBloksAIPluginName, kMaxStringLength);
}

BloksAIPlugin::~BloksAIPlugin()
{
}

static void TestEventHandler(const csxs::event::Event* const eventParam, void* const context)
{
	// We don't care who sends the event, we just do the action
	ai::UnicodeString dataStr(eventParam->data);
	
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
		// Register to be notified of when we can register for CSXS events
		error = sAINotifier->AddNotifier(
			fPluginRef,
			"Register Event Notify",
			kAICSXSPlugPlugSetupCompleteNotifier,
			&fRegisterEventNotifierHandle);
	}

	if (!error)
	{
		// Register for selection changed
		error = sAINotifier->AddNotifier(
			fPluginRef,
			"Register Selection Changed",
			kAIArtSelectionChangedNotifier,
			&fRegisterSelectionChangedHandle);
	}

	sAIUser->MessageAlert(ai::UnicodeString("Hello from BloksAIPlugin!"));

	return error;
}

ASErr BloksAIPlugin::ShutdownPlugin(SPInterfaceMessage *message)
{
	ASErr error = kNoErr;

	if (!error)
	{
		// Deregister for our transform event
		csxs::event::EventErrorCode result = csxs::event::kEventErrorCode_Success;
		SDKPlugPlug plug;
		plug.Load(sAIFolders);
		result = plug.RemoveEventListener(BLOKS_EVENT_ID, TestEventHandler, NULL);

		if (result != csxs::event::kEventErrorCode_Success)
		{
			error = 1;
		}

		plug.Unload();
	}

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

	if (message->notifier == fRegisterEventNotifierHandle)
	{
		// Register for our transform event
		csxs::event::EventErrorCode result = csxs::event::kEventErrorCode_Success;
		SDKPlugPlug plug;
		plug.Load(sAIFolders);
		result = plug.AddEventListener(BLOKS_EVENT_ID, TestEventHandler, NULL);

		if (result != csxs::event::kEventErrorCode_Success)
		{
			error = 1;
		}

		plug.Unload();
	}
	else if (message->notifier == fRegisterSelectionChangedHandle)
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

	return error;
}
