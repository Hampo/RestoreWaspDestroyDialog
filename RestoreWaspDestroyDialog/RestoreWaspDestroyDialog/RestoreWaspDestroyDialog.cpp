#include "pch.h"

#include "HackFunctions.h"
#include "MinHook.h"
#include "Shar.h"
#include <stdlib.h>
#include <cstdint>

extern HMODULE dllHandle;

#ifdef _DEBUG
#define printf(x, ...) Hack_Printf(2, 0, x, __VA_ARGS__)
#define debug_printf(x, ...) Hack_Printf(2, 0, x, __VA_ARGS__)
#else
#define printf(x, ...) Hack_Printf(2, 0, x, __VA_ARGS__)
#define debug_printf(x, ...) 
#endif

class FakeFlyingActor
{
public:
	void __thiscall ReceiveEvent(int callback, void* stateProp);
	static void* originalReceiveEvent;
};
void* FakeFlyingActor::originalReceiveEvent = 0;

extern "C"  __declspec(dllexport)  unsigned int __cdecl HackEntryPoint(HackEvent, void*);

extern "C" unsigned int __cdecl HackEntryPoint(HackEvent event, void* data)
{
	switch (event)
	{
		case HackEvent::InstallHacks:
		{
			InitialiseHack();
			int sharVersion = IdentifySharVersion();
			debug_printf(L"RestoreWaspDestroyDialog: Entry point reached %d %p\n", event, data);
			debug_printf(L"RestoreWaspDestroyDialog: Shar Version %d\n", sharVersion);

			auto initializeStatus = MH_Initialize();
			if (initializeStatus != MH_OK)
			{
				printf(L"RestoreWaspDestroyDialog: Did not initialise MinHook. MH_Status: %d\n", initializeStatus);
				return 1;
			}

			void* flyingActorReceiveEvent = GetFlyingActorReceiveEvent_Ptr();
			FakeFlyingActor::originalReceiveEvent = 0;

			auto newFlyingActorReceiveEvent = &FakeFlyingActor::ReceiveEvent;
			void** newFlyingActorReceiveEvent_ptr = (void**)&newFlyingActorReceiveEvent;
			auto createHookStatus = MH_CreateHook(flyingActorReceiveEvent, *newFlyingActorReceiveEvent_ptr, &FakeFlyingActor::originalReceiveEvent);
			if (createHookStatus != MH_OK)
			{
				printf(L"RestoreWaspDestroyDialog: Did not create the FlyingActor::ReceiveEvent Hook. MH_Status: %d\n", createHookStatus);
				return 1;
			}

			auto enableHookStatus = MH_EnableHook(flyingActorReceiveEvent);
			if (enableHookStatus != MH_OK)
			{
				printf(L"RestoreWaspDestroyDialog: Did not activate the FlyingActor::ReceiveEvent Hook. MH_Status: %d\n", enableHookStatus);
				return 1;
			}

			debug_printf(L"RestoreWaspDestroyDialog: Hooked FlyingActor::ReceiveEvent %p to %p\n", FakeFlyingActor::originalReceiveEvent, *newFlyingActorReceiveEvent_ptr);

			break;
		}
	}
	return 0;
}

const int STATEPROP_CHANGE_STATE_EVENT = -1;
const unsigned int ACTOR_DESTROYED = 5;
const unsigned int EVENT_BREAK_CAMERA_OR_BOX = 212;
void __thiscall FakeFlyingActor::ReceiveEvent(int callback, void* stateProp)
{
	debug_printf(L"RestoreWaspDestroyDialog: Received event %d\n", callback);
	if (callback == STATEPROP_CHANGE_STATE_EVENT)
	{
		unsigned int newState = *((uint32_t*)((uint8_t*)stateProp + 32)); //CStateProp.m_CurrentState
		debug_printf(L"RestoreWaspDestroyDialog: New state %d\n", newState);
		if (newState == ACTOR_DESTROYED)
		{
			debug_printf(L"RestoreWaspDestroyDialog: Triggering EVENT_BREAK_CAMERA_OR_BOX event\n", newState);
			TriggerEvent(GetEventManager(), EVENT_BREAK_CAMERA_OR_BOX, 0);
		}
	}

	((void(__thiscall*)(void*, unsigned int, void*))FakeFlyingActor::originalReceiveEvent)(this, callback, stateProp);
}