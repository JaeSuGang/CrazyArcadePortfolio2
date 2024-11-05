#include "stdafx.h"
#include "EditorManager.h"
#include "KmEngine/Level.h"
#include "KmEngine/RenderComponent.h"
#include "CrazyArcadeGame/GameUI.h"
#include "CrazyArcadeGame/GroundTile.h"
#include "CrazyArcadeGame/WallTile.h"

void UEditorManager::LoadGroundTilePalette()
{
	UResourceManager* ResourceManager = GEngine->GetEngineSubsystem<UResourceManager>();

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			string strImagePath = "Resources\\Tiles\\GroundTiles\\" + std::to_string(m_nCurrentPaletteIndex * 9 + i * 3 + j);
			strImagePath += ".bmp";
			if (UImage* Image = ResourceManager->GetImage(strImagePath))
			{
				AGroundTile* Tile = GetActiveLevel()->InitializeActorForPlay<AGroundTile>();
				Tile->SetPosition(FVector2D(1010.0f + 70.0f * j, 140.0f + 80.0f * i));
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

void UEditorManager::LoadWallTilePalette()
{
	UResourceManager* ResourceManager = GEngine->GetEngineSubsystem<UResourceManager>();

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			string strImagePath = "Resources\\Tiles\\WallTiles\\" + std::to_string(m_nCurrentPaletteIndex * 9 + i * 3 + j);
			strImagePath += ".bmp";
			if (UImage* Image = ResourceManager->GetImage(strImagePath))
			{
				AWallTile* Tile = GetActiveLevel()->InitializeActorForPlay<AWallTile>();
				Tile->SetPosition(FVector2D(1010.0f + 70.0f * j, 420.0f + 80.0f * i));
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

AGameUI* UEditorManager::SpawnEditorUI(string strImagePath, FVector2D PositionVector)
{
	AGameUI* GameUI = GetActiveLevel()->InitializeActorForPlay<AGameUI>();
	URenderComponent* RenderComponent = GameUI->CreateDefaultSubobject<URenderComponent>();
	RenderComponent->SetStaticImage(strImagePath);
	RenderComponent->SetRenderPriority(0);
	GameUI->SetPosition(PositionVector);
	return GameUI;
}

void UEditorManager::BindEditorKeys()
{
	UKeyManager* km = GEngine->GetEngineSubsystem<UKeyManager>();
	km->BindKey(VK_LBUTTON, UKeyManager::EKeyState::KeyDown, std::bind(&UEditorManager::OnLeftClick, this));
}

void UEditorManager::OnLeftClick()
{
	URenderManager* RenderManager = GEngine->GetEngineSubsystem<URenderManager>();
	HWND hWnd = RenderManager->GetGameWindowHandle();

	POINT CursorPos;
	GetCursorPos(&CursorPos);
	ScreenToClient(hWnd, &CursorPos);

	FVector2D CursorVector{(float)CursorPos.x, (float)CursorPos.y};

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			FVector2D TilePaintLocation{ 1010.0f + 70.0f * j, 140.0f + 80.0f * i };
			FVector2D RelativeVector = TilePaintLocation - CursorVector;
			float fDistance = RelativeVector.GetLength();
			if (fDistance <= 20.0f)
			{
				int a = 9;
			}
		}
	}
}

void UEditorManager::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);


}
