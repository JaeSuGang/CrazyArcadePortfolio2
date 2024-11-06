#include "stdafx.h"
#include "EditorManager.h"
#include "KmEngine/Level.h"
#include "KmEngine/RenderComponent.h"
#include "CrazyArcadeGame/GameUI.h"
#include "ClickableUIComponent.h"

void UEditorManager::ShowDebugMousePos(HDC hBackBuffer)
{
	FVector2D MousePos = this->GetRelativeMousePosition();
	string strToShow = "X : " + std::to_string((int)MousePos.X);
	strToShow += ", Y : " +std::to_string((int)MousePos.Y);
	TextOutA(hBackBuffer, 5, 5 + 1 * 30, strToShow.data(), (int)strToShow.size());
}

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
				AActor* Tile = GetActiveLevel()->InitializeActorForPlay<AActor>();
				Tile->SetPosition(FVector2D(1010.0f + 70.0f * j, 140.0f + 80.0f * i));
				URenderComponent* RenderComponent = Tile->CreateDefaultSubobject<URenderComponent>();
				UClickableUIComponent* ClickableUIComponent = Tile->CreateDefaultSubobject<UClickableUIComponent>();
				ClickableUIComponent->SetClickableUIType(UClickableUIComponent::EClickableUIType::GroundTilePaint);
				ClickableUIComponent->SetValue(i * 3 + j + 1);
				RenderComponent->SetStaticImage(Image);
				RenderComponent->SetRenderPriority(1);
				RenderComponent->BeginPlay();
				ClickableUIComponent->BeginPlay();
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
				AActor* Tile = GetActiveLevel()->InitializeActorForPlay<AActor>();
				Tile->SetPosition(FVector2D(1010.0f + 70.0f * j, 400.0f + 80.0f * i));
				URenderComponent* RenderComponent = Tile->CreateDefaultSubobject<URenderComponent>();
				UClickableUIComponent* ClickableUIComponent = Tile->CreateDefaultSubobject<UClickableUIComponent>();
				ClickableUIComponent->SetClickableUIType(UClickableUIComponent::EClickableUIType::WallTilePaint);
				ClickableUIComponent->SetValue(i * 3 + j + 1);
				RenderComponent->SetStaticImage(Image);
				RenderComponent->SetRenderPriority(1);
				RenderComponent->BeginPlay();
				ClickableUIComponent->BeginPlay();
			}
			else
			{
				break;
			}

		}
	}
}

AGameUI* UEditorManager::SpawnEditorUI(string strImagePath, FVector2D PositionVector, float fRenderPriority)
{
	AGameUI* GameUI = GetActiveLevel()->InitializeActorForPlay<AGameUI>();
	URenderComponent* RenderComponent = GameUI->CreateDefaultSubobject<URenderComponent>();
	RenderComponent->SetStaticImage(strImagePath);
	RenderComponent->SetRenderPriority(fRenderPriority);
	RenderComponent->BeginPlay();
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
	// AStart 좀더 정밀한데 연산량이 높다.
	// JPS 빠른데 


	FVector2D CursorVector = GetRelativeMousePosition();

	if (CursorVector.X > 900)
	{
		for (AActor* Actor : GetActiveLevel()->m_Actors)
		{
			if (UClickableUIComponent* ClickableUIComponent = Actor->GetComponentByClass<UClickableUIComponent>())
			{
				FVector2D ActorVector = Actor->GetPosition();
				FVector2D RelativeVector = ActorVector - CursorVector;
				float fDistance = RelativeVector.GetLength();
				if (fDistance <= 30.0f)
				{
					switch (ClickableUIComponent->GetClickableUIType())
					{
					case UClickableUIComponent::EClickableUIType::GroundTilePaint:
					{
						if (m_SelectedTile)
							m_SelectedTile->Destroy();

						m_SelectedTile = GetActiveLevel()->InitializeActorForPlay<AActor>();
						URenderComponent* RenderComponent = m_SelectedTile->CreateDefaultSubobject<URenderComponent>();
						string strImagePath = "Resources\\Tiles\\GroundTiles\\";
						strImagePath += std::to_string(ClickableUIComponent->GetValue()) + ".bmp";
						RenderComponent->SetStaticImage(strImagePath);
						RenderComponent->BeginPlay();
						break;
					}

					case UClickableUIComponent::EClickableUIType::WallTilePaint:
					{
						if (m_SelectedTile)
							m_SelectedTile->Destroy();

						m_SelectedTile = GetActiveLevel()->InitializeActorForPlay<AActor>();
						URenderComponent* RenderComponent = m_SelectedTile->CreateDefaultSubobject<URenderComponent>();
						string strImagePath = "Resources\\Tiles\\WallTiles\\";
						strImagePath += std::to_string(ClickableUIComponent->GetValue()) + ".bmp";
						RenderComponent->SetStaticImage(strImagePath);
						RenderComponent->BeginPlay();
						break;
					}


					}
					break;
				}
			}
		}

		// Obsolete
		//for (int i = 0; i < 3; i++)
		//{
		//	for (int j = 0; j < 3; j++)
		//	{
		//		FVector2D GroundTilePaintLocation{ 1010.0f + 70.0f * j, 140.0f + 80.0f * i };
		//		FVector2D RelativeVector = GroundTilePaintLocation - CursorVector;
		//		float fDistance = RelativeVector.GetLength();
		//		if (fDistance <= 30.0f)
		//		{
		//			if (m_SelectedTile)
		//			{
		//				m_SelectedTile->Destroy();
		//			}
		//			m_SelectedTile = GetActiveLevel()->InitializeActorForPlay<AActor>();
		//			URenderComponent* RenderComponent = m_SelectedTile->CreateDefaultSubobject<URenderComponent>();
		//			string strImagePath = "Resources\\Tiles\\GroundTiles\\";
		//			strImagePath += std::to_string(i * 3 + j + 1) + ".bmp";
		//			RenderComponent->SetStaticImage(strImagePath);
		//			RenderComponent->BeginPlay();
		//		}
		//	}
		//}
		//for (int i = 0; i < 3; i++)
		//{
		//	for (int j = 0; j < 3; j++)
		//	{
		//		FVector2D WallTilePaintLocation{ 1010.0f + 70.0f * j, 420.0f + 80.0f * i };
		//		FVector2D RelativeVector = WallTilePaintLocation - CursorVector;
		//		float fDistance = RelativeVector.GetLength();
		//		if (fDistance <= 30.0f)
		//		{
		//			if (m_SelectedTile)
		//			{
		//				m_SelectedTile->Destroy();
		//			}
		//			m_SelectedTile = GetActiveLevel()->InitializeActorForPlay<AActor>();
		//			URenderComponent* RenderComponent = m_SelectedTile->CreateDefaultSubobject<URenderComponent>();
		//			string strImagePath = "Resources\\Tiles\\WallTiles\\";
		//			strImagePath += std::to_string(i * 3 + j + 1) + ".bmp";
		//			RenderComponent->SetStaticImage(strImagePath);
		//			RenderComponent->BeginPlay();
		//		}
		//	}
		//}
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
