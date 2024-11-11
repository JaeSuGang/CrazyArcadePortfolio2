#include "stdafx.h"
#include "Character.h"
#include "KmEngine/Level.h"
#include "KmEngine/PlayerController.h"
#include "CharacterAIController.h"
#include "KmEngine/RenderComponent.h"
#include "GameUI.h"
#include "SpawnManager.h"
#include "Tilemap.h"
#include "InGameObjectComponent.h"


void USpawnManager::GenerateWallTile(int nTileLocationIndex, int nTileValue, int nGroundTileValue)
{
	int nXIndex = nTileLocationIndex % 15;
	int nYIndex = nTileLocationIndex / 15;

	UResourceManager* ResourceManager = GEngine->GetEngineSubsystem<UResourceManager>();
	FVector2D LocationVector{ 60.0f + 60.0f * nXIndex, 90.0f + 60.0f * nYIndex };
	AActor* TileActor = GetActiveLevel()->InitializeActorForPlay<AActor>();
	URenderComponent* PositionedTileRenderComponent = TileActor->CreateDefaultSubobject<URenderComponent>();
	UInGameObjectComponent* InGameObjectComponent = TileActor->CreateDefaultSubobject<UInGameObjectComponent>();

	// 벽 이미지
	switch (nTileValue)
	{
	case 1:
	case 2:
		InGameObjectComponent->m_InGameObjectProperty = FInGameObjectProperty::ExplodableWall;
		PositionedTileRenderComponent->SetStaticImageOffset(FVector2D(0.0f, -3.0f));
		break;
	case 3:
		InGameObjectComponent->m_InGameObjectProperty = FInGameObjectProperty::MovableWall;
		PositionedTileRenderComponent->SetStaticImageOffset(FVector2D(0.0f, -3.0f));
		break;
	case 4:
	case 5:
	case 6:
		InGameObjectComponent->m_InGameObjectProperty = FInGameObjectProperty::NonExplodableWall;
		PositionedTileRenderComponent->SetStaticImageOffset(FVector2D(0.0f, -11.0f));
		break;
	case 7:
		InGameObjectComponent->m_InGameObjectProperty = FInGameObjectProperty::HidableWall;
		PositionedTileRenderComponent->SetStaticImageOffset(FVector2D(0.0f, -11.0f));
		break;
	case 8:
		InGameObjectComponent->m_InGameObjectProperty = FInGameObjectProperty::NonExplodableWall;
		PositionedTileRenderComponent->SetStaticImageOffset(FVector2D(0.0f, -20.0f));
		break;
	default:
		break;

	}

	// 그림자 이미지
	switch (nTileValue)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		switch (nGroundTileValue)
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

	default:
		break;
	}

	TileActor->SetPosition(LocationVector);
	PositionedTileRenderComponent->SetRenderPriority(nYIndex + 10.0f);
	PositionedTileRenderComponent->SetRenderType(URenderComponent::ERenderType::ShadowObject);
	PositionedTileRenderComponent->SetStaticImage("Resources\\Tiles\\WallTiles\\" + std::to_string(nTileValue) + ".bmp");



	TileActor->BeginPlay();
}

void USpawnManager::GenerateGroundTile(int nTileLocationIndex, int nTileValue)
{
	int nXIndex = nTileLocationIndex % 15;
	int nYIndex = nTileLocationIndex / 15;

	UResourceManager* ResourceManager = GEngine->GetEngineSubsystem<UResourceManager>();
	FVector2D LocationVector{ (float)(59.5f + 60 * nXIndex), (float)(89.5f + 60 * nYIndex) };
	AActor* TileActor = GetActiveLevel()->InitializeActorForPlay<AActor>();
	URenderComponent* PositionedTileRenderComponent = TileActor->CreateDefaultSubobject<URenderComponent>();

	TileActor->SetPosition(LocationVector);
	UImage* Image = ResourceManager->GetImage("Resources\\Tiles\\GroundTiles\\" + std::to_string(nTileValue) + ".bmp");
	PositionedTileRenderComponent->SetRenderType(URenderComponent::ERenderType::FloorTile);
	PositionedTileRenderComponent->SetRenderPriority(0.0f);
	PositionedTileRenderComponent->SetStaticImage(Image);
	PositionedTileRenderComponent->SetStaticImageOffset(FVector2D::Zero);
	TileActor->BeginPlay();
}

void USpawnManager::GenerateTilemap(FTilemap* TilemapStruct)
{
	m_Tilemap = TilemapStruct;

	for (int i = 0; i < 15 * 13; i++)
	{
		this->GenerateGroundTile(i, m_Tilemap->m_GroundTiles[i]);
		this->GenerateWallTile(i, m_Tilemap->m_WallTiles[i], m_Tilemap->m_GroundTiles[i]);
	}

	// 
	AActor* UpBoundary = GetActiveLevel()->InitializeActorForPlay<AActor>();
	UInGameObjectComponent* InGameObjectComponent1 = UpBoundary->CreateDefaultSubobject<UInGameObjectComponent>();
	InGameObjectComponent1->m_InGameObjectProperty = FInGameObjectProperty::NonExplodableWall;
	InGameObjectComponent1->m_InGameObjectProperty.m_CollisionSize = FVector2D(900.0f, 60.0f);
	UpBoundary->SetPosition(FVector2D(480.0f, 30.0f));
	UpBoundary->BeginPlay();

	// 
	AActor* DownBoundary = GetActiveLevel()->InitializeActorForPlay<AActor>();
	UInGameObjectComponent* InGameObjectComponent2 = DownBoundary->CreateDefaultSubobject<UInGameObjectComponent>();
	InGameObjectComponent2->m_InGameObjectProperty = FInGameObjectProperty::NonExplodableWall;
	InGameObjectComponent2->m_InGameObjectProperty.m_CollisionSize = FVector2D(900.0f, 60.0f);
	DownBoundary->SetPosition(FVector2D(480.0f, 870.0f));
	DownBoundary->BeginPlay();

	// 
	AActor* LeftBoundary = GetActiveLevel()->InitializeActorForPlay<AActor>();
	UInGameObjectComponent* InGameObjectComponent3 = LeftBoundary->CreateDefaultSubobject<UInGameObjectComponent>();
	InGameObjectComponent3->m_InGameObjectProperty = FInGameObjectProperty::NonExplodableWall;
	InGameObjectComponent3->m_InGameObjectProperty.m_CollisionSize = FVector2D(60.0f, 780.0f);
	LeftBoundary->SetPosition(FVector2D(0.0f, 450.0f));
	LeftBoundary->BeginPlay();

	// 
	AActor* RightBoundary = GetActiveLevel()->InitializeActorForPlay<AActor>();
	UInGameObjectComponent* InGameObjectComponent4 = RightBoundary->CreateDefaultSubobject<UInGameObjectComponent>();
	InGameObjectComponent4->m_InGameObjectProperty = FInGameObjectProperty::NonExplodableWall;
	InGameObjectComponent4->m_InGameObjectProperty.m_CollisionSize = FVector2D(60.0f, 780.0f);
	RightBoundary->SetPosition(FVector2D(960.0f, 450.0f));
	RightBoundary->BeginPlay();
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
	RenderComponent->CreateAnimation("DownWalk", "Resources\\" + strCharacterName + "\\DownWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("LeftWalk", "Resources\\" + strCharacterName + "\\LeftWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("RightWalk", "Resources\\" + strCharacterName + "\\RightWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("UpWalk", "Resources\\" + strCharacterName + "\\UpWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("BubbleLoop", "Resources\\" + strCharacterName + "\\BubbleLoop", 2, 0.5f, true);
	RenderComponent->CreateAnimation("BubbleFade", "Resources\\" + strCharacterName + "\\BubbleFade", 2, 0.5f, false);
	UInGameObjectComponent* InGameObjectComponent = SpawnedCharacter->CreateDefaultSubobject<UInGameObjectComponent>();
	InGameObjectComponent->m_InGameObjectProperty = FInGameObjectProperty::Character;
	SpawnedCharacter->SetBombCount(1);

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
	RenderComponent->CreateAnimation("DownWalk", "Resources\\" + strCharacterName + "\\DownWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("LeftWalk", "Resources\\" + strCharacterName + "\\LeftWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("RightWalk", "Resources\\" + strCharacterName + "\\RightWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("UpWalk", "Resources\\" + strCharacterName + "\\UpWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("BubbleLoop", "Resources\\" + strCharacterName + "\\BubbleLoop", 2, 0.5f, true);
	RenderComponent->CreateAnimation("BubbleFade", "Resources\\" + strCharacterName + "\\BubbleFade", 2, 0.5f, false);
	UInGameObjectComponent* InGameObjectComponent = SpawnedCharacter->CreateDefaultSubobject<UInGameObjectComponent>();
	InGameObjectComponent->m_InGameObjectProperty = FInGameObjectProperty::Character;

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
	RenderComponent->CreateAnimation("DownWalk", "Resources\\" + strCharacterName + "\\DownWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("LeftWalk", "Resources\\" + strCharacterName + "\\LeftWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("RightWalk", "Resources\\" + strCharacterName + "\\RightWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("UpWalk", "Resources\\" + strCharacterName + "\\UpWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("BubbleLoop", "Resources\\" + strCharacterName + "\\BubbleLoop", 2, 0.5f, true);
	RenderComponent->CreateAnimation("BubbleFade", "Resources\\" + strCharacterName + "\\BubbleFade", 2, 0.5f, false);
	UInGameObjectComponent* InGameObjectComponent = SpawnedCharacter->CreateDefaultSubobject<UInGameObjectComponent>();
	InGameObjectComponent->m_InGameObjectProperty = FInGameObjectProperty::Character;

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
	RenderComponent->CreateAnimation("DownWalk", "Resources\\" + strCharacterName + "\\DownWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("LeftWalk", "Resources\\" + strCharacterName + "\\LeftWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("RightWalk", "Resources\\" + strCharacterName + "\\RightWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("UpWalk", "Resources\\" + strCharacterName + "\\UpWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("BubbleLoop", "Resources\\" + strCharacterName + "\\BubbleLoop", 2, 0.5f, true);
	RenderComponent->CreateAnimation("BubbleFade", "Resources\\" + strCharacterName + "\\BubbleFade", 2, 0.5f, false);
	UInGameObjectComponent* InGameObjectComponent = SpawnedCharacter->CreateDefaultSubobject<UInGameObjectComponent>();
	InGameObjectComponent->m_InGameObjectProperty = FInGameObjectProperty::Character;

	SpawnedCharacter->SetPosition(PositionVector);
	SpawnedCharacter->BeginPlay();
	return SpawnedCharacter;
}

AActor* USpawnManager::SpawnBomb(FVector2D PositionVector, AActor* Spawner)
{
	AActor* BombActor = GetActiveLevel()->InitializeActorForPlay<AActor>();
	BombActor->SetPosition(PositionVector);
	URenderComponent* RenderComponent = BombActor->CreateDefaultSubobject<URenderComponent>();
	RenderComponent->SetStaticImageOffset(FVector2D(0.0f, 0.0f));
	RenderComponent->SetStaticImage("Resources\\Bomb\\bomb_0.bmp");
	RenderComponent->SetShadowImageOffset(FVector2D(0.0f, 25.0f));
	RenderComponent->SetShadowImage("Resources\\Shadows\\CharacterShadow.bmp");
	RenderComponent->SetRenderPriority(VectorToRenderPriority(PositionVector));
	RenderComponent->SetRenderType(URenderComponent::ERenderType::ShadowObject);
	RenderComponent->CreateAnimation("Bomb\\bomb", "Resources\\Bomb\\bomb", 4, 0.2f, true);
	UInGameObjectComponent* BombInGameObjectComponent = BombActor->CreateDefaultSubobject<UInGameObjectComponent>();
	UInGameObjectComponent* SpawnerInGameObjectComponent = Spawner->GetComponentByClass<UInGameObjectComponent>();
	BombInGameObjectComponent->m_InGameObjectProperty = FInGameObjectProperty::Bomb;
	BombInGameObjectComponent->m_InGameObjectProperty.m_Spawner = Spawner;
	BombInGameObjectComponent->m_InGameObjectProperty.m_nBombRange = SpawnerInGameObjectComponent->m_InGameObjectProperty.m_nBombRange;

	BombActor->BeginPlay();
	return BombActor;
}

AActor* USpawnManager::SpawnExplosion(FVector2D PositionVector, int nDirection, bool bIsEnd)
{
	return this->SpawnExplosion(PositionVector, nDirection, 0.0f, bIsEnd);
}

AActor* USpawnManager::SpawnExplosion(FVector2D PositionVector, int nDirection, float fDelayTimer, bool bIsEnd)
{
	AActor* ExplosionActor = GetActiveLevel()->InitializeActorForPlay<AActor>();
	ExplosionActor->SetPosition(PositionVector);
	URenderComponent* RenderComponent = ExplosionActor->CreateDefaultSubobject<URenderComponent>();
	UInGameObjectComponent* InGameObjectComponent = ExplosionActor->CreateDefaultSubobject<UInGameObjectComponent>();
	RenderComponent->SetRenderPriority(VectorToRenderPriority(PositionVector));
	RenderComponent->SetRenderType(URenderComponent::ERenderType::NonShadowObject);
	InGameObjectComponent->m_InGameObjectProperty = FInGameObjectProperty::Explosion;

	switch (nDirection)
	{
	case 0:
		RenderComponent->CreateAnimation("ExplosionEndLoop", "Resources\\BombExplosion\\BombExplosionCenter", 4, 0.025f, true);
		RenderComponent->CreateAnimation("ExplosionLoop", "Resources\\BombExplosion\\BombExplosionCenter", 4, 0.025f, true);
		RenderComponent->CreateAnimation("ExplosionFade", "Resources\\BombExplosion\\BombExplosionCenter", 4, 0.010f, true);
		break;
	case 1:
		RenderComponent->CreateAnimation("ExplosionLoop", "Resources\\BombExplosion\\BombExplosionUpLoop", 2, 0.025f, fDelayTimer, true);
		RenderComponent->CreateAnimation("ExplosionEndLoop", "Resources\\BombExplosion\\BombExplosionUpEndLoop", 2, 0.025f, fDelayTimer, true);
		RenderComponent->CreateAnimation("ExplosionFade", "Resources\\BombExplosion\\BombExplosionUpFade", 10, 0.010f, false);
		break;
	case 2:
		RenderComponent->CreateAnimation("ExplosionLoop", "Resources\\BombExplosion\\BombExplosionRightLoop", 2, 0.025f, fDelayTimer, true);
		RenderComponent->CreateAnimation("ExplosionEndLoop", "Resources\\BombExplosion\\BombExplosionRightEndLoop", 2, 0.025f, fDelayTimer, true);
		RenderComponent->CreateAnimation("ExplosionFade", "Resources\\BombExplosion\\BombExplosionRightFade", 10, 0.010f, false);
		break;
	case 3:
		RenderComponent->CreateAnimation("ExplosionLoop", "Resources\\BombExplosion\\BombExplosionDownLoop", 2, 0.025f, fDelayTimer, true);
		RenderComponent->CreateAnimation("ExplosionEndLoop", "Resources\\BombExplosion\\BombExplosionDownEndLoop", 2, 0.025f, fDelayTimer, true);
		RenderComponent->CreateAnimation("ExplosionFade", "Resources\\BombExplosion\\BombExplosionDownFade", 10, 0.010f, false);
		break;
	case 4:
		RenderComponent->CreateAnimation("ExplosionLoop", "Resources\\BombExplosion\\BombExplosionLeftLoop", 2, 0.025f, fDelayTimer, true);
		RenderComponent->CreateAnimation("ExplosionEndLoop", "Resources\\BombExplosion\\BombExplosionLeftEndLoop", 2, 0.025f, fDelayTimer, true);
		RenderComponent->CreateAnimation("ExplosionFade", "Resources\\BombExplosion\\BombExplosionLeftFade", 10, 0.010f, false);
		break;
	
	}

	ExplosionActor->BeginPlay();
	return nullptr;
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
