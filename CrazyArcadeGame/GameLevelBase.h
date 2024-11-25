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

public:
	ACCESSORS_ALL(float, ElapsedTime);
	ACCESSORS_ALL(bool, bIsGameStarted);

protected:
	vector<FVector2D> SpawnLocations;
	FTilemap* m_Tilemap;
	bool bIsGameStarted;
	float ElapsedTime;
};

