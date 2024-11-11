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
	void Explode(int nTileIndex, int nRange);

public:
	void Tick(float fDeltaTime) override;

};

