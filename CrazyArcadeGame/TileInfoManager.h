#pragma once
#include "KmEngine/GameInstanceSubsystem.h"

class AActor;

class FTilemapInfo
{
public:
	vector<AActor*> m_TileInfos[15 * 13];
};

class UTileInfoManager : public UGameInstanceSubsystem
{
	typedef UGameInstanceSubsystem Super;

public:
	void Tick(float fDeltaTime) override;
};

