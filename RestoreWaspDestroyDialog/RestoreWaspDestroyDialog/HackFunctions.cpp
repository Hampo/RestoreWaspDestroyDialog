#include "pch.h"
#include "HackFunctions.h"

static int* Hack_GameReleasePtr = 0;

void InitialiseHack()
{
	HMODULE hacks = GetModuleHandle(L"Hacks.dll");
	Hack_Printf = (Hack_Printf_t)GetProcAddress(hacks, MAKEINTRESOURCEA(3631));
	Hack_GetSetting = (Hack_GetSetting_t)GetProcAddress(hacks, MAKEINTRESOURCEA(2560));
	Hack_GameReleasePtr = (int*)GetProcAddress(hacks, MAKEINTRESOURCEA(3153));
}

// Bare function pointer because variable forwarding nonsense
Hack_Printf_t Hack_Printf = nullptr;
Hack_GetSetting_t Hack_GetSetting = nullptr;

// Get the game release
int Hack_GameRelease()
{
	return *Hack_GameReleasePtr;
}

int Hack_GetSettingI(wchar_t const* hackName, wchar_t const* settingName)
{
	void* setting = Hack_GetSetting(hackName, settingName);
	if (setting == 0)
		return 0;
	int* valuePtr = (int*)((char*)setting + 0x188);
	return *valuePtr;
}