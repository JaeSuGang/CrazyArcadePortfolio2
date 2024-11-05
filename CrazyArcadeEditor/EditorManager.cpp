#include "stdafx.h"
#include "EditorManager.h"
#include "KmEngine/Level.h"
#include "KmEngine/RenderComponent.h"
#include "CrazyArcadeGame/GameUI.h"
#include "CrazyArcadeGame/GroundTile.h"
#include "CrazyArcadeGame/WallTile.h"

void UEditorManager::LoadGroundTilePalette(int nIndex)
{
	UResourceManager* ResourceManager = GEngine->GetEngineSubsystem<UResourceManager>();

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			string strImagePath = "Resources\\Tiles\\GroundTiles\\" + std::to_string(nIndex * 15 + i * 3 + j);
			strImagePath += ".bmp";
			if (UImage* Image = ResourceManager->GetImage(strImagePath))
			{
				AGroundTile* Tile = GetActiveLevel()->InitializeActorForPlay<AGroundTile>();
				Tile->SetPosition(FVector2D(1010.0f + 70.0f * j, 140.0f + 70.0f * i));
				URenderComponent* RenderComponent = Tile->CreateDefaultSubobject<URenderComponent>();
				RenderComponent->SetStaticImage(Image);
				RenderComponent->SetRenderPriority(1);
			}
			else
			{
				break;
			}

		}
	}
}

void UEditorManager::LoadWallTilePalette(int nIndex)
{
}

AGameUI* UEditorManager::SpawnEditorUI(string strImagePath, FVector2D PositionVector)
{
	AGameUI* GameUI = GetActiveLevel()->InitializeActorForPlay<AGameUI>();
	URenderComponent* RenderComponent = GameUI->CreateDefaultSubobject<URenderComponent>();
	RenderComponent->SetStaticImage(strImagePath);
	RenderComponent->SetRenderPriority(0);
	GameUI->SetPosition(PositionVector);
	return GameUI;
}

void UEditorManager::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);


}
