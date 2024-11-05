#pragma once
#include "KmEngine/GameInstanceSubsystem.h"
#include "CrazyArcadeGame/TilemapData.h"

class AWallTile;
class AGroundTile;
class AGameUI;
class AActor;

class UEditorManager : public UGameInstanceSubsystem
{
	typedef UGameInstanceSubsystem Super;

public:
	void LoadGroundTilePalette();
	void LoadWallTilePalette();
	AGameUI* SpawnEditorUI(string strImagePath, FVector2D PositionVector);
	AWallTile* SpawnWallTile();
	AGroundTile* SpawnGroundTile();

public:
	FVector2D GetRelativeMousePosition();

public:
	void BindEditorKeys();

public:
	void OnLeftClick();
	void OnRightClick();

public:
	void Tick(float fDeltaTime) override;

private:
	FTilemapData m_CurrentTilemapData;
	AActor* m_SelectedTile;

	int m_nCurrentPaletteIndex;
};

