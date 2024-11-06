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
	URenderManager* RenderManager = GEngine->GetEngineSubsystem<URenderManager>();
	UEditorManager* EditorManager = GetGameInstance()->GetGameInstanceSubsystem<UEditorManager>();

	std::function<void()> Event = std::bind(&UEditorManager::ShowDebugMousePos, EditorManager, RenderManager->GetBackBufferHandle());
	RenderManager->AddCustomRenderEvent(Event);

	EditorManager->BindEditorKeys();
	EditorManager->SpawnEditorUI("Resources\\UI\\EditorUI.bmp", FVector2D(600.0f, 450.0f), 0.0f);
	EditorManager->SpawnEditorUI("Resources\\UI\\SaveButton.bmp", FVector2D(1075.0f, 720.0f), 1.0f);
	EditorManager->SpawnEditorUI("Resources\\UI\\LoadButton.bmp", FVector2D(1075.0f, 790.0f), 1.0f);
	EditorManager->LoadGroundTilePalette();
	EditorManager->LoadWallTilePalette();
}
