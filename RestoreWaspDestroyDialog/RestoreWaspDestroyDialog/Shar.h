#pragma once
#include <cstdint>
int IdentifySharVersion();

void* GetFlyingActorReceiveEvent_Ptr();
void* GetActorDSGReceiveEvent_Ptr();

void* GetEventManager();
void TriggerEvent(void* pEventManager, unsigned int uiEvent, void* pParam = 0);

int64_t radMakeKey(const char* pToken, int64_t keyValue = 0);