#pragma once
#include "KmEngine/GameInstanceSubsystem.h"

class UBombManager : public UGameInstanceSubsystem
{
	typedef UGameInstanceSubsystem Super;

public:
	void TryPutBomb(FVector2D BombPosition);
	void PutBomb(int nTileIndex);

public:
	void Tick(float fDeltaTime) override;

};

