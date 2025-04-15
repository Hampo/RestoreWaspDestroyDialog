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
	return Choose(0x41A5C0, 0x41A4D0, 0x41A5F0, 0x41A8E0);
}

void* GetActorDSGReceiveEvent_Ptr()
{
	return Choose(0x415400, 0x415680, 0x415290, 0x415AD0);
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

int64_t radMakeKey(const char* pToken, int64_t keyValue)
{
	if (pToken != NULL)
	{
		while (*pToken)
		{
			keyValue *= 65599;
			keyValue = (keyValue ^ (static_cast<int64_t>(*pToken)));

			pToken++;
		}

		return(keyValue);
	}

	return keyValue;
}