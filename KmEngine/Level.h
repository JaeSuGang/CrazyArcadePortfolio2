#pragma once
#include "Object.h"

class AActor;
class AGamemode;

class ULevel final : public UObject
{
	friend class UGameInstance;

private:
	void Tick(float fDeltaTime);
	void BeginPlay();

private:
	AGamemode* m_Gamemode;
	unordered_set<AActor*> m_Actors;
};

