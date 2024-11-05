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
			string strImagePath = "Resources\\Tiles\\GroundTiles\\" + std::to_string(m_nCurrentPaletteIndex * 9 + i * 3 + j + 1);
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
			string strImagePath = "Resources\\Tiles\\WallTiles\\" + std::to_string(m_nCurrentPaletteIndex * 9 + i * 3 + j + 1);
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

FVector2D UEditorManager::GetRelativeMousePosition()
{
	URenderManager* RenderManager = GEngine->GetEngineSubsystem<URenderManager>();
	HWND hWnd = RenderManager->GetGameWindowHandle();

	POINT CursorPos;
	GetCursorPos(&CursorPos);
	ScreenToClient(hWnd, &CursorPos);

	FVector2D CursorVector{ (float)CursorPos.x, (float)CursorPos.y };

	return CursorVector;
}

void UEditorManager::BindEditorKeys()
{
	UKeyManager* km = GEngine->GetEngineSubsystem<UKeyManager>();
	km->BindKey(VK_LBUTTON, UKeyManager::EKeyState::KeyDown, std::bind(&UEditorManager::OnLeftClick, this));
	km->BindKey(VK_RBUTTON, UKeyManager::EKeyState::KeyDown, std::bind(&UEditorManager::OnRightClick, this));
}

void UEditorManager::OnLeftClick()
{

	FVector2D CursorVector = GetRelativeMousePosition();

	if (CursorVector.X > 900)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				FVector2D GroundTilePaintLocation{ 1010.0f + 70.0f * j, 140.0f + 80.0f * i };
				FVector2D RelativeVector = GroundTilePaintLocation - CursorVector;
				float fDistance = RelativeVector.GetLength();
				if (fDistance <= 30.0f)
				{
					if (m_SelectedTile)
					{
						m_SelectedTile->Destroy();
					}
					m_SelectedTile = GetActiveLevel()->InitializeActorForPlay<AGroundTile>();
					URenderComponent* RenderComponent = m_SelectedTile->CreateDefaultSubobject<URenderComponent>();
					string strImagePath = "Resources\\Tiles\\GroundTiles\\";
					strImagePath += std::to_string(i * 3 + j + 1) + ".bmp";
					RenderComponent->SetStaticImage(strImagePath);
				}
			}
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				FVector2D WallTilePaintLocation{ 1010.0f + 70.0f * j, 420.0f + 80.0f * i };
				FVector2D RelativeVector = WallTilePaintLocation - CursorVector;
				float fDistance = RelativeVector.GetLength();
				if (fDistance <= 30.0f)
				{
					if (m_SelectedTile)
					{
						m_SelectedTile->Destroy();
					}
					m_SelectedTile = GetActiveLevel()->InitializeActorForPlay<AWallTile>();
					URenderComponent* RenderComponent = m_SelectedTile->CreateDefaultSubobject<URenderComponent>();
					string strImagePath = "Resources\\Tiles\\WallTiles\\";
					strImagePath += std::to_string(i * 3 + j + 1) + ".bmp";
					RenderComponent->SetStaticImage(strImagePath);
				}
			}
		}
	}

	if (CursorVector.X < 900)
	{
		int nXIndex = (CursorVector.X - 30) / 60;
		int nYIndex = (CursorVector.Y - 60) / 60;

		if (nXIndex >= 0 && nXIndex < 15 && nYIndex >= 0 && nYIndex < 13)
		{

		}
	}

}

void UEditorManager::OnRightClick()
{
	if (m_SelectedTile)
	{
		m_SelectedTile->Destroy();
	}
	m_SelectedTile = nullptr;
}

void UEditorManager::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	if (m_SelectedTile)
	{
		FVector2D MouseVector = GetRelativeMousePosition();
		m_SelectedTile->SetPosition(MouseVector);
	}
}
