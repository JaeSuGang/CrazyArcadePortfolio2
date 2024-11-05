#pragma once
#include "KmEngine/GameInstanceSubsystem.h"

class AWallTile;
class AGroundTile;
class AGameUI;

class UEditorManager : public UGameInstanceSubsystem
{
	typedef UGameInstanceSubsystem Super;

public:
	void LoadGroundTilePalette(int nIndex);
	void LoadWallTilePalette(int nIndex);
	AGameUI* SpawnEditorUI(string strImagePath, FVector2D PositionVector);
	AWallTile* SpawnWallTile();
	AGroundTile* SpawnGroundTile();

public:
	void Tick(float fDeltaTime) override;
};

