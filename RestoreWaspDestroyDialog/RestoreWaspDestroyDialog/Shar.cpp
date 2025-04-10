#include "pch.h"

#include "HackFunctions.h"
#include "Shar.h"

static int SharVersion = 0;

inline static void* Choose(unsigned int originalEnglish, unsigned int international, unsigned int bestSellerSeries, unsigned int demo)
{
	void* releases[] = { (void*)originalEnglish, (void*)international, (void*)bestSellerSeries, (void*)demo };
	return releases[SharVersion];
}

int IdentifySharVersion()
{
	SharVersion = Hack_GameRelease();
	return SharVersion;
}

void* GetFlyingActorReceiveEvent_Ptr()
{
	return Choose(0x41A5C0, 0x41A840, 0x41A450, 0x41AC90);
}

void* GetEventManager()
{
	return *(void**)Choose(0x6C9018, 0x6C8FD8, 0x6C9010, 0x6C8FD8);
}

void TriggerEvent(void* pEventManager, unsigned int uiEvent, void* pParam)
{
	void* pFunc = Choose(0x432AD0, 0x432D50, 0x432960, 0x4331A0);
	_asm
	{
		push pParam
		push uiEvent
		mov edx, pEventManager
		call pFunc
	}
}
