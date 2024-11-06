#pragma once
#include "KmEngine/Level.h"

class FTilemap;

class UGameLevelBase : public ULevel
{
	typedef ULevel Super;

public:
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
	void BeginPlay() override;

public:
	void Release();
	~UGameLevelBase();

private:
	FTilemap* m_Tilemap;
};

