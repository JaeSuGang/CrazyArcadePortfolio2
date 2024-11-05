#pragma once
#include "KmEngine/GameInstanceSubsystem.h"

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
	void BindEditorKeys();

public:
	void OnLeftClick();

public:
	void Tick(float fDeltaTime) override;

private:
	AActor* m_SelectedTile;
	int m_nCurrentPaletteIndex;
};

