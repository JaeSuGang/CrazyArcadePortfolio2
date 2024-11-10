#pragma once
#include "KmEngine/GameInstanceSubsystem.h"

class UBombManager : public UGameInstanceSubsystem
{
	typedef UGameInstanceSubsystem Super;

public:
	bool TryPutBomb(int nTileIndex);
	void ForcePutBomb(int nTileIndex);

public:
	void Tick(float fDeltaTime) override;

public:
	unordered_set<AActor*> m_Bombs;
};

