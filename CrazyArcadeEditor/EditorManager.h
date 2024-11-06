#pragma once
#include "KmEngine/GameInstanceSubsystem.h"
#include "ClickableUIComponent.h"

class AWallTile;
class AGroundTile;
class AGameUI;
class AActor;
class FTilemap;

class UEditorManager : public UGameInstanceSubsystem
{
	typedef UGameInstanceSubsystem Super;

public:
	void LoadTilemap();
	void SaveTilemap();
	void CreateNewTilemap();
	void ShowDebugMousePos(HDC hBackBuffer);
	void LoadGroundTilePalette();
	void LoadWallTilePalette();
	AGameUI* SpawnEditorUI(string strImagePath, FVector2D PositionVector, float fRenderPriority, UClickableUIComponent::EClickableUIType ClickableUIType, int nClickableValue);
	void SetSelectedTile(UClickableUIComponent::EClickableUIType ClickableUIType, int nTileIndex);
	void PutTile(int nlocation, bool bIsGroundTile, int nValue);

public:
	FVector2D GetRelativeMousePosition();

public:
	void BindEditorKeys();

public:
	void OnLeftClick();
	void OnRightClick();

public:
	void Tick(float fDeltaTime) override;

public:
	void Release();
	~UEditorManager();

private:
	FTilemap* m_Tilemap;
	AActor* m_SelectedTile;
	int m_nCurrentPaletteIndex;
};

