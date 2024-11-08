#include "stdafx.h"
#include "Character.h"
#include "KmEngine/Level.h"
#include "KmEngine/PlayerController.h"
#include "CharacterAIController.h"
#include "KmEngine/RenderComponent.h"
#include "GameUI.h"
#include "MovableComponent.h"
#include "WallComponent.h"
#include "SpawnManager.h"
#include "Tilemap.h"


void USpawnManager::GenerateWallTile(int nTileIndex, int nValue, int nGroundTileIndex)
{
	int nXIndex = nTileIndex % 15;
	int nYIndex = nTileIndex / 15;

	UResourceManager* ResourceManager = GEngine->GetEngineSubsystem<UResourceManager>();
	FVector2D LocationVector{ (float)(60 + 60 * nXIndex), (float)(90 + 60 * nYIndex) };
	AActor* TileActor = GetActiveLevel()->InitializeActorForPlay<AActor>();
	URenderComponent* PositionedTileRenderComponent = TileActor->CreateDefaultSubobject<URenderComponent>();
	UWallComponent* PositionedTileWallComponent = TileActor->CreateDefaultSubobject<UWallComponent>();
	PositionedTileWallComponent->SetCollisionSize(FVector2D(30.0f, 30.0f));
	switch (nValue)
	{
	case 1:
	case 2:
	case 3:
	case 7:
		PositionedTileWallComponent->RegisterAtMovementManager(true);
		break;

	default:
		PositionedTileWallComponent->RegisterAtMovementManager(false);
		break;

	}

	TileActor->SetPosition(LocationVector);
	PositionedTileRenderComponent->SetRenderPriority(nYIndex + 10.0f);
	PositionedTileRenderComponent->SetRenderType(URenderComponent::ERenderType::ShadowObject);
	PositionedTileRenderComponent->SetStaticImage("Resources\\Tiles\\WallTiles\\" + std::to_string(nValue) + ".bmp");

	switch (nValue)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		switch (nGroundTileIndex)
		{
		case 1:
		case 2:
			PositionedTileRenderComponent->SetShadowImage("Resources\\Shadows\\WallGreenShadow.bmp");
			PositionedTileRenderComponent->SetShadowImageOffset(FVector2D(-2.0f, 2.0f));
			break;

		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			PositionedTileRenderComponent->SetShadowImage("Resources\\Shadows\\WallGrayShadow.bmp");
			PositionedTileRenderComponent->SetShadowImageOffset(FVector2D(-3.0f, 2.0f));
			break;
		}
		break;
	}

	switch (nValue)
	{
	case 1:
	case 2:
	case 3:
		PositionedTileRenderComponent->SetStaticImageOffset(FVector2D(0.0f, -3.0f));
		break;

	case 4:
	case 5:
	case 6:
	case 7:
		PositionedTileRenderComponent->SetStaticImageOffset(FVector2D(0.0f, -11.0f));
		break;

	case 8:
		PositionedTileRenderComponent->SetStaticImageOffset(FVector2D(0.0f, -20.0f));
		break;

	default:
		PositionedTileRenderComponent->SetStaticImageOffset(FVector2D::Zero);
		break;
	}

	TileActor->BeginPlay();
}

void USpawnManager::GenerateGroundTile(int nTileIndex, int nValue)
{
	int nXIndex = nTileIndex % 15;
	int nYIndex = nTileIndex / 15;

	UResourceManager* ResourceManager = GEngine->GetEngineSubsystem<UResourceManager>();
	FVector2D LocationVector{ (float)(60 + 60 * nXIndex), (float)(90 + 60 * nYIndex) };
	AActor* TileActor = GetActiveLevel()->InitializeActorForPlay<AActor>();
	URenderComponent* PositionedTileRenderComponent = TileActor->CreateDefaultSubobject<URenderComponent>();

	TileActor->SetPosition(LocationVector);
	UImage* Image = ResourceManager->GetImage("Resources\\Tiles\\GroundTiles\\" + std::to_string(nValue) + ".bmp");
	PositionedTileRenderComponent->SetRenderType(URenderComponent::ERenderType::FloorTile);
	PositionedTileRenderComponent->SetRenderPriority(0.0f);
	PositionedTileRenderComponent->SetStaticImage(Image);
	PositionedTileRenderComponent->SetStaticImageOffset(FVector2D::Zero);
	TileActor->BeginPlay();
}

void USpawnManager::GenerateTilemap(FTilemap* TilemapStruct)
{
	for (int i = 0; i < 15 * 13; i++)
	{
		this->GenerateGroundTile(i, TilemapStruct->m_GroundTiles[i]);
		this->GenerateWallTile(i, TilemapStruct->m_WallTiles[i], TilemapStruct->m_GroundTiles[i]);
	}
}

AGameUI* USpawnManager::SpawnGameUI(string strImagePath, FVector2D PositionVector)
{
	AGameUI* GameUI = GetActiveLevel()->InitializeActorForPlay<AGameUI>();
	URenderComponent* RenderComponent = GameUI->CreateDefaultSubobject<URenderComponent>();
	RenderComponent->SetStaticImage(strImagePath);
	RenderComponent->SetRenderType(URenderComponent::ERenderType::UI);
	RenderComponent->SetRenderPriority(0);
	RenderComponent->BeginPlay();
	GameUI->SetPosition(PositionVector);
	return GameUI;
}

ACharacter* USpawnManager::SpawnBazzi(FVector2D PositionVector)
{
	string strCharacterName = "Bazzi";
	ACharacter* SpawnedCharacter = GetActiveLevel()->InitializeActorForPlay<ACharacter>();
	SpawnedCharacter->SetCharacterName(strCharacterName);
	URenderComponent* RenderComponent = SpawnedCharacter->CreateDefaultSubobject<URenderComponent>();
	RenderComponent->SetStaticImageOffset(FVector2D(0.0f, -12.0f));
	RenderComponent->SetStaticImage("Resources\\" + strCharacterName + "\\" + "DownIdle.bmp");
	RenderComponent->SetShadowImageOffset(FVector2D(0.0f, 25.0f));
	RenderComponent->SetShadowImage("Resources\\Shadows\\CharacterShadow.bmp");
	RenderComponent->SetRenderPriority(1);
	RenderComponent->SetRenderType(URenderComponent::ERenderType::ShadowObject);
	RenderComponent->CreateAnimation(strCharacterName + "DownWalk", "Resources\\" + strCharacterName + "\\DownWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(strCharacterName + "LeftWalk", "Resources\\" + strCharacterName + "\\LeftWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(strCharacterName + "RightWalk", "Resources\\" + strCharacterName + "\\RightWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(strCharacterName + "UpWalk", "Resources\\" + strCharacterName + "\\UpWalk", 4, 0.1f, true);
	RenderComponent->BeginPlay();
	UMovableComponent* MovableComponent = SpawnedCharacter->CreateDefaultSubobject<UMovableComponent>();
	MovableComponent->RegisterMovableAtMovementManager();
	MovableComponent->SetMaxSpeed(300.0f);
	MovableComponent->SetCollisionSize(FVector2D(25.0f, 25.0f));

	SpawnedCharacter->SetPosition(PositionVector);
	SpawnedCharacter->BeginPlay();
	return SpawnedCharacter;
}

ACharacter* USpawnManager::SpawnDao(FVector2D PositionVector)
{
	string strCharacterName = "Dao";
	ACharacter* SpawnedCharacter = GetActiveLevel()->InitializeActorForPlay<ACharacter>();
	SpawnedCharacter->SetCharacterName(strCharacterName);
	URenderComponent* RenderComponent = SpawnedCharacter->CreateDefaultSubobject<URenderComponent>();
	RenderComponent->SetStaticImageOffset(FVector2D(0.0f, -12.0f));
	RenderComponent->SetStaticImage("Resources\\" + strCharacterName + "\\" + "DownIdle.bmp");
	RenderComponent->SetShadowImageOffset(FVector2D(0.0f, 25.0f));
	RenderComponent->SetShadowImage("Resources\\Shadows\\CharacterShadow.bmp");
	RenderComponent->SetRenderPriority(1);
	RenderComponent->SetRenderType(URenderComponent::ERenderType::ShadowObject);
	RenderComponent->CreateAnimation(strCharacterName + "DownWalk", "Resources\\" + strCharacterName + "\\DownWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(strCharacterName + "LeftWalk", "Resources\\" + strCharacterName + "\\LeftWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(strCharacterName + "RightWalk", "Resources\\" + strCharacterName + "\\RightWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(strCharacterName + "UpWalk", "Resources\\" + strCharacterName + "\\UpWalk", 4, 0.1f, true);
	RenderComponent->BeginPlay();
	UMovableComponent* MovableComponent = SpawnedCharacter->CreateDefaultSubobject<UMovableComponent>();
	MovableComponent->RegisterMovableAtMovementManager();
	MovableComponent->SetMaxSpeed(300.0f);
	MovableComponent->SetCollisionSize(FVector2D(30.0f, 30.0f));

	SpawnedCharacter->SetPosition(PositionVector);
	SpawnedCharacter->BeginPlay();
	return SpawnedCharacter;
}

ACharacter* USpawnManager::SpawnCappi(FVector2D PositionVector)
{
	string strCharacterName = "Cappi";
	ACharacter* SpawnedCharacter = GetActiveLevel()->InitializeActorForPlay<ACharacter>();
	SpawnedCharacter->SetCharacterName(strCharacterName);
	URenderComponent* RenderComponent = SpawnedCharacter->CreateDefaultSubobject<URenderComponent>();
	RenderComponent->SetStaticImageOffset(FVector2D(0.0f, -12.0f));
	RenderComponent->SetStaticImage("Resources\\" + strCharacterName + "\\" + "DownIdle.bmp");
	RenderComponent->SetShadowImageOffset(FVector2D(0.0f, 25.0f));
	RenderComponent->SetShadowImage("Resources\\Shadows\\CharacterShadow.bmp");
	RenderComponent->SetRenderPriority(1);
	RenderComponent->SetRenderType(URenderComponent::ERenderType::ShadowObject);
	RenderComponent->CreateAnimation(strCharacterName + "DownWalk", "Resources\\" + strCharacterName + "\\DownWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(strCharacterName + "LeftWalk", "Resources\\" + strCharacterName + "\\LeftWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(strCharacterName + "RightWalk", "Resources\\" + strCharacterName + "\\RightWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(strCharacterName + "UpWalk", "Resources\\" + strCharacterName + "\\UpWalk", 4, 0.1f, true);
	RenderComponent->BeginPlay();
	UMovableComponent* MovableComponent = SpawnedCharacter->CreateDefaultSubobject<UMovableComponent>();
	MovableComponent->RegisterMovableAtMovementManager();
	MovableComponent->SetMaxSpeed(300.0f);
	MovableComponent->SetCollisionSize(FVector2D(30.0f, 30.0f));

	SpawnedCharacter->SetPosition(PositionVector);
	SpawnedCharacter->BeginPlay();
	return SpawnedCharacter;
}

ACharacter* USpawnManager::SpawnMarid(FVector2D PositionVector)
{
	string strCharacterName = "Marid";
	ACharacter* SpawnedCharacter = GetActiveLevel()->InitializeActorForPlay<ACharacter>();
	SpawnedCharacter->SetCharacterName(strCharacterName);
	URenderComponent* RenderComponent = SpawnedCharacter->CreateDefaultSubobject<URenderComponent>();
	RenderComponent->SetStaticImageOffset(FVector2D(0.0f, -12.0f));
	RenderComponent->SetStaticImage("Resources\\" + strCharacterName + "\\" + "DownIdle.bmp");
	RenderComponent->SetShadowImageOffset(FVector2D(0.0f, 25.0f));
	RenderComponent->SetShadowImage("Resources\\Shadows\\CharacterShadow.bmp");
	RenderComponent->SetRenderPriority(1);
	RenderComponent->SetRenderType(URenderComponent::ERenderType::ShadowObject);
	RenderComponent->CreateAnimation(strCharacterName + "DownWalk", "Resources\\" + strCharacterName + "\\DownWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(strCharacterName + "LeftWalk", "Resources\\" + strCharacterName + "\\LeftWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(strCharacterName + "RightWalk", "Resources\\" + strCharacterName + "\\RightWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(strCharacterName + "UpWalk", "Resources\\" + strCharacterName + "\\UpWalk", 4, 0.1f, true);
	RenderComponent->BeginPlay();
	UMovableComponent* MovableComponent = SpawnedCharacter->CreateDefaultSubobject<UMovableComponent>();
	MovableComponent->RegisterMovableAtMovementManager();
	MovableComponent->SetMaxSpeed(300.0f);
	MovableComponent->SetCollisionSize(FVector2D(30.0f, 30.0f));

	SpawnedCharacter->SetPosition(PositionVector);
	SpawnedCharacter->BeginPlay();
	return SpawnedCharacter;
}

AActor* USpawnManager::SpawnBomb(FVector2D PositionVector)
{
	AActor* Bomb = GetActiveLevel()->InitializeActorForPlay<AActor>();
	Bomb->SetPosition(PositionVector);
	URenderComponent* RenderComponent = Bomb->CreateDefaultSubobject<URenderComponent>();
	RenderComponent->SetStaticImageOffset(FVector2D(0.0f, 0.0f));
	RenderComponent->SetStaticImage("Resources\\Dao\\UpWalk_3.bmp");
	RenderComponent->SetShadowImageOffset(FVector2D(0.0f, 0.0f));
	RenderComponent->SetShadowImage("Resources\\Shadows\\CharacterShadow.bmp");
	RenderComponent->SetRenderPriority(VectorToRenderPriority(PositionVector));
	RenderComponent->SetRenderType(URenderComponent::ERenderType::ShadowObject);

	Bomb->BeginPlay();
	return Bomb;
}

APlayerController* USpawnManager::SpawnPlayerController()
{
	APlayerController* PlayerController = GetActiveLevel()->InitializeActorForPlay<APlayerController>();
	PlayerController->BeginPlay();
	return PlayerController;
}

AAIController* USpawnManager::SpawnCharacterAIController()
{
	ACharacterAIController* AIController = GetActiveLevel()->InitializeActorForPlay<ACharacterAIController>();
	AIController->BeginPlay();
	return AIController;
}

void USpawnManager::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);


}
