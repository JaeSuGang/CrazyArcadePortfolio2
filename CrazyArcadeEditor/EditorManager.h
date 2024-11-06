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
	void ShowDebugMousePos(HDC hBackBuffer);
	void LoadGroundTilePalette();
	void LoadWallTilePalette();
	AGameUI* SpawnEditorUI(string strImagePath, FVector2D PositionVector, float fRenderPriority);

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
	AActor* m_SelectedTile;

	int m_nCurrentPaletteIndex;
};

