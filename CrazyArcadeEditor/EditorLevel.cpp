#include "stdafx.h"
#include "EditorLevel.h"
#include "KmEngine/RenderComponent.h"
#include "CrazyArcadeGame/GameUI.h"
#include "EditorManager.h"


void UEditorLevel::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);
}

void UEditorLevel::LateTick(float fDeltaTime)
{
	Super::LateTick(fDeltaTime);
}

void UEditorLevel::BeginPlay()
{
	UEditorManager* EditorManager = GetGameInstance()->GetGameInstanceSubsystem<UEditorManager>();
	EditorManager->BindEditorKeys();
	EditorManager->SpawnEditorUI("Resources\\UI\\EditorUI.bmp", FVector2D(600.0f, 450.0f));
	EditorManager->LoadGroundTilePalette();
	EditorManager->LoadWallTilePalette();
}
