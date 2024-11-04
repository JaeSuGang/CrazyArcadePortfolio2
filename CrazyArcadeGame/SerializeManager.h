#pragma once
#include "KmEngine/GameInstanceSubsystem.h"

class FTileMapData
{
public:
	enum class EFloorTile : unsigned short
	{
		None
	};

	enum class EWallTile : unsigned short
	{
		None,
		SpawnPoint
	};
public:
	EFloorTile m_FloorTiles[15 * 13];
	EWallTile m_WallTiles[15 * 13];
};

class USerializeManager : public UGameInstanceSubsystem
{
	typedef UGameInstanceSubsystem Super;

public:


public:
	void Tick(float fDeltaTime) override;
};

