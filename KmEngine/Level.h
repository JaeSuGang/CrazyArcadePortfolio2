#pragma once
#include "Object.h"

class AActor;
class AGamemode;

class ULevel final : public UObject
{
	friend class UEngine;
	friend class UGameInstance;
	friend class UTestGameInstance;

public:
	ULevel();

private:
	void Tick(float fDeltaTime);
	void BeginPlay();

// 차후수정
public:
	AGamemode* m_Gamemode;
	unordered_set<AActor*> m_Actors;
};

