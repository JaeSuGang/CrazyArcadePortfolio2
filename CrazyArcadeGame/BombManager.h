#pragma once
#include "stdafx.h"
#include "KmEngine/GameInstanceSubsystem.h"

class AActor;

class UBombManager : public UGameInstanceSubsystem
{
	typedef UGameInstanceSubsystem Super;

public:
	bool TryPutBomb(int nTileIndex, AActor* Spawner);
	void ForcePutBomb(int nTileIndex, AActor* Spawner);

public:
	void Tick(float fDeltaTime) override;

public:
	unordered_set<AActor*> m_Bombs;
};

