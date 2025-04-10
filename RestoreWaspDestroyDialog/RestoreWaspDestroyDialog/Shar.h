#pragma once
int IdentifySharVersion();

void* GetFlyingActorReceiveEvent_Ptr();
void* GetActorDSGReceiveEvent_Ptr();

void* GetEventManager();
void TriggerEvent(void* pEventManager, unsigned int uiEvent, void* pUnknown);