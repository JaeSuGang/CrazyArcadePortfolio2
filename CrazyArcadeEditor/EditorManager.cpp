#include "stdafx.h"
#include "EditorManager.h"
#include "KmEngine/Level.h"
#include "KmEngine/RenderComponent.h"
#include "CrazyArcadeGame/GameUI.h"
#include "CrazyArcadeGame/Tilemap.h"
#include "ClickableUIComponent.h"

void UEditorManager::LoadTilemap()
{
	OPENFILENAME ofn;
	TCHAR szFile[260] = { 0 };

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = GEngine->GetEngineSubsystem<URenderManager>()->GetGameWindowHandle();
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "All\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileNameA(&ofn) == TRUE)
	{
		std::string Path = ofn.lpstrFile;

		m_Tilemap->Load(Path);
	}

	for (AActor* Actor : GetActiveLevel()->m_Actors)
	{
		UClickableUIComponent* ClickableUIComponent = Actor->GetComponentByClass<UClickableUIComponent>();
		if (!ClickableUIComponent)
		{
			Actor->Destroy();
		}
	}


	for (int i = 0; i < 15 * 13; i++)
	{
		PutSelectedTile(i, true, m_Tilemap->m_GroundTiles[i]);
		PutSelectedTile(i, false, m_Tilemap->m_WallTiles[i]);
	}
}

void UEditorManager::SaveTilemap()
{
	OPENFILENAME ofn;
	TCHAR szFile[260] = { 0 };

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = GEngine->GetEngineSubsystem<URenderManager>()->GetGameWindowHandle();
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "All\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetSaveFileNameA(&ofn) == TRUE)
	{
		std::string Path = ofn.lpstrFile;

		m_Tilemap->Save(Path);
	}
}

void UEditorManager::CreateNewTilemap()
{
	m_Tilemap = new FTilemap{};
}

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
				RenderComponent->SetRenderPriority(1.0f);
				Tile->BeginPlay();
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

AGameUI* UEditorManager::SpawnEditorUI(string strImagePath, FVector2D PositionVector, float fRenderPriority, UClickableUIComponent::EClickableUIType ClickableUIType, int nClickableValue)
{
	AGameUI* GameUI = GetActiveLevel()->InitializeActorForPlay<AGameUI>();
	URenderComponent* RenderComponent = GameUI->CreateDefaultSubobject<URenderComponent>();
	UClickableUIComponent* ClickableUIComponent = GameUI->CreateDefaultSubobject<UClickableUIComponent>();
	RenderComponent->SetStaticImage(strImagePath);
	RenderComponent->SetRenderPriority(fRenderPriority);
	ClickableUIComponent->SetClickableUIType(ClickableUIType);
	ClickableUIComponent->SetValue(nClickableValue);
	GameUI->SetPosition(PositionVector);
	GameUI->BeginPlay();
	return GameUI;
}

void UEditorManager::SetSelectedTile(UClickableUIComponent::EClickableUIType ClickableUIType, int nTileIndex)
{
	URenderComponent* RenderComponent{}; 
	UClickableUIComponent* ClickableUIComponent{};
	if (m_SelectedTile)
	{
		m_SelectedTile->Destroy();
	}

	m_SelectedTile = GetActiveLevel()->InitializeActorForPlay<AActor>();
	RenderComponent = m_SelectedTile->CreateDefaultSubobject<URenderComponent>();
	ClickableUIComponent = m_SelectedTile->CreateDefaultSubobject<UClickableUIComponent>();

	if (ClickableUIType == UClickableUIComponent::EClickableUIType::WallTilePaint)
	{
		string strImagePath = "Resources\\Tiles\\WallTiles\\";
		strImagePath += std::to_string(nTileIndex) + ".bmp";
		RenderComponent->SetStaticImage(strImagePath);
		ClickableUIComponent->SetClickableUIType(UClickableUIComponent::EClickableUIType::WallTilePaint);
	}
	else if (ClickableUIType == UClickableUIComponent::EClickableUIType::GroundTilePaint)
	{
		string strImagePath = "Resources\\Tiles\\GroundTiles\\";
		strImagePath += std::to_string(nTileIndex) + ".bmp";
		RenderComponent->SetStaticImage(strImagePath);
		ClickableUIComponent->SetClickableUIType(UClickableUIComponent::EClickableUIType::GroundTilePaint);
	}
	RenderComponent->SetRenderPriority(1.0f);
	ClickableUIComponent->SetValue(nTileIndex);
	m_SelectedTile->BeginPlay();
}

void UEditorManager::PutSelectedTile(int nlocation, bool bIsGroundTile, int nValue)
{
	int nXIndex = nlocation % 15;
	int nYIndex = nlocation / 15;
	FVector2D LocationVector{ (float)(60 + 60 * nXIndex), (float)(90 + 60 * nYIndex) };
	AActor* TileActor = GetActiveLevel()->InitializeActorForPlay<AActor>();
	URenderComponent* PositionedTileRenderComponent = TileActor->CreateDefaultSubobject<URenderComponent>();
	TileActor->SetPosition(LocationVector);
	UResourceManager* ResourceManager = GEngine->GetEngineSubsystem<UResourceManager>();
	if (bIsGroundTile)
	{
		UImage* Image = ResourceManager->GetImage("Resources\\Tiles\\GroundTiles\\" + std::to_string(nValue) + ".bmp");
		PositionedTileRenderComponent->SetRenderPriority(0.0f);
		PositionedTileRenderComponent->SetStaticImage(Image);
	}
	else
	{
		UImage* Image = ResourceManager->GetImage("Resources\\Tiles\\WallTiles\\" + std::to_string(nValue) + ".bmp");
		PositionedTileRenderComponent->SetRenderPriority(nYIndex + 10);
		PositionedTileRenderComponent->SetStaticImage(Image);
	}

	TileActor->BeginPlay();
}

void UEditorManager::PutSelectedTile(int nlocation)
{
	int nXIndex = nlocation % 15;
	int nYIndex = nlocation / 15;
	FVector2D LocationVector{(float)(60 + 60 * nXIndex), (float)(90 + 60 * nYIndex)};
	AActor* TileActor = GetActiveLevel()->InitializeActorForPlay<AActor>();
	URenderComponent* PositionedTileRenderComponent = TileActor->CreateDefaultSubobject<URenderComponent>();
	PositionedTileRenderComponent->SetRenderPriority(1.0f);
	TileActor->BeginPlay();
	TileActor->SetPosition(LocationVector);

	URenderComponent* SelectedTileRenderComponent = m_SelectedTile->GetComponentByClass<URenderComponent>();
	UImage* ImageToUse = SelectedTileRenderComponent->GetStaticImage();
	PositionedTileRenderComponent->SetStaticImage(ImageToUse);
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
				if (fDistance <= 35.0f)
				{
					switch (ClickableUIComponent->GetClickableUIType())
					{
					case UClickableUIComponent::EClickableUIType::GroundTilePaint:
					{
						this->SetSelectedTile(UClickableUIComponent::EClickableUIType::GroundTilePaint, ClickableUIComponent->GetValue());
						break;
					}

					case UClickableUIComponent::EClickableUIType::WallTilePaint:
					{
						this->SetSelectedTile(UClickableUIComponent::EClickableUIType::WallTilePaint, ClickableUIComponent->GetValue());
						break;
					}
					case UClickableUIComponent::EClickableUIType::SaveAndLoad:
					{
						int nValue = ClickableUIComponent->GetValue();
						if (nValue == 0)
						{
							this->SaveTilemap();
						}
						else if (nValue == 1)
						{
							this->LoadTilemap();
						}
						break;
					}
					}
					break;
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
			if (m_SelectedTile)
			{
				UClickableUIComponent* ClickableUIComponent = m_SelectedTile->GetComponentByClass<UClickableUIComponent>();
				switch (ClickableUIComponent->GetClickableUIType())
				{
				case UClickableUIComponent::EClickableUIType::GroundTilePaint:
					if (m_Tilemap->m_GroundTiles[nYIndex * 15 + nXIndex] == 0)
					{
						m_Tilemap->m_GroundTiles[nYIndex * 15 + nXIndex] = ClickableUIComponent->GetValue();
						this->PutSelectedTile(nYIndex * 15 + nXIndex);
					}
					break;

				case UClickableUIComponent::EClickableUIType::WallTilePaint:
					if (m_Tilemap->m_WallTiles[nYIndex * 15 + nXIndex] == 0)
					{
						m_Tilemap->m_WallTiles[nYIndex * 15 + nXIndex] = ClickableUIComponent->GetValue();
						this->PutSelectedTile(nYIndex * 15 + nXIndex);
					}
					break;

				}

			}
		}
	}

}

void UEditorManager::OnRightClick()
{
	if (m_SelectedTile)
	{
		m_SelectedTile->Destroy();
		m_SelectedTile = nullptr;
	}
	else
	{
		FVector2D CursorVector = this->GetRelativeMousePosition();
		if (CursorVector.X < 900.0f)
		{
			int nXIndex = (CursorVector.X - 30) / 60;
			int nYIndex = (CursorVector.Y - 60) / 60;

			if (nXIndex >= 0 && nXIndex < 15 && nYIndex >= 0 && nYIndex < 13)
			{
				m_Tilemap->m_GroundTiles[nYIndex * 15 + nXIndex] = 0;
				m_Tilemap->m_WallTiles[nYIndex * 15 + nXIndex] = 0;
			}

			for (AActor* Actor : GetActiveLevel()->m_Actors)
			{
				UClickableUIComponent* ClickableUIComponent = Actor->GetComponentByClass<UClickableUIComponent>();
				if (!ClickableUIComponent)
				{
					FVector2D ActorVector = Actor->GetPosition();
					FVector2D RelativeVector = ActorVector - CursorVector;
					float fDistance = RelativeVector.GetLength();
					if (fDistance <= 35.0f)
					{
						Actor->Destroy();
						break;
					}
				}
			}
		}
	}
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

void UEditorManager::Release()
{
	SAFE_DELETE(m_Tilemap);
}

UEditorManager::~UEditorManager()
{
	this->Release();
}
