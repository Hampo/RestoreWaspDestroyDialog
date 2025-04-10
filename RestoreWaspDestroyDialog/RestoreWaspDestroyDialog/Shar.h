#pragma once
int IdentifySharVersion();

void* GetMissionStageStart_Ptr();
void* GetMissionInitialize_Ptr();
void* GetFlyingActorReceiveEvent_Ptr();

unsigned int GetCheats();
void SetCheats(unsigned int enabledCheats);

typedef void(_cdecl* SCRIPTCOMMANDPROC)(unsigned int uiCount, const char** prgpszArguments);
void* GetScriptManager();
bool AddScriptCommand(const char* pszName, const char* pszDescription, unsigned int uiMinimumArgumentCount, void* pScriptManager, SCRIPTCOMMANDPROC pCallback, unsigned int uiMaximumArgumentCount);

void* GetEventManager();
void TriggerEvent(void* pEventManager, unsigned int uiEvent, void* pUnknown);

void* GetCharacterSheetManager();

struct MissionScriptLoader
{
	unsigned char m_Offset[0x14];
	void* Mission;
	void* Stage;
};
MissionScriptLoader* GetMissionScriptLoader();