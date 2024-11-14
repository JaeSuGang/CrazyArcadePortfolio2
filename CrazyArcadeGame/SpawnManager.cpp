#include "stdafx.h"
#include "Character.h"
#include "KmEngine/Level.h"
#include "KmEngine/PlayerController.h"
#include "CharacterAIController.h"
#include "KmEngine/RenderComponent.h"
#include "GameUI.h"
#include "SpawnManager.h"
#include "MovementManager.h"
#include "BombManager.h"
#include "Tilemap.h"
#include "Bomb.h"
#include "Block.h"
#include "Explosion.h"
#include "PowerUpItem.h"


void USpawnManager::GenerateWallTile(int nTileLocationIndex, int nTileValue, int nGroundTileValue)
{
	if (nTileValue == 0)
		return;

	int nXIndex = nTileLocationIndex % 15;
	int nYIndex = nTileLocationIndex / 15;

	UResourceManager* ResourceManager = GEngine->GetEngineSubsystem<UResourceManager>();
	FVector2D LocationVector{ 60.0f + 60.0f * nXIndex, 90.0f + 60.0f * nYIndex };
	ABlock* TileActor = GetActiveLevel()->InitializeActorForPlay<ABlock>();
	URenderComponent* PositionedTileRenderComponent = TileActor->CreateDefaultSubobject<URenderComponent>();

	// 벽 특성 설정
	switch (nTileValue)
	{
	case 1:
	case 2:
		TileActor->SetBreakable(true);
		PositionedTileRenderComponent->SetStaticImageOffset(FVector2D(0.0f, -3.0f));
		break;
	case 3:
		TileActor->SetPushable(true);
		TileActor->SetBreakable(true);
		PositionedTileRenderComponent->SetStaticImageOffset(FVector2D(0.0f, -3.0f));
		break;
	case 4:
	case 5:
	case 6:
		PositionedTileRenderComponent->SetStaticImageOffset(FVector2D(0.0f, -11.0f));
		break;
	case 7:
		TileActor->SetBreakable(true);
		TileActor->SetPassable(true);
		TileActor->SetHidable(true);
		PositionedTileRenderComponent->SetStaticImageOffset(FVector2D(0.0f, -11.0f));
		break;
	case 8:
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
	FVector2D LocationVector{ (float)(60.0f + 60 * nXIndex), (float)(90.0f + 60 * nYIndex) };
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
	ABlock* UpBoundary = GetActiveLevel()->InitializeActorForPlay<ABlock>();
	UpBoundary->m_CollisionSize = FVector2D(900.0f, 60.0f);
	UpBoundary->SetPosition(FVector2D(480.0f, 30.0f));
	UpBoundary->BeginPlay();

	// 
	ABlock* DownBoundary = GetActiveLevel()->InitializeActorForPlay<ABlock>();
	DownBoundary->m_CollisionSize = FVector2D(900.0f, 60.0f);
	DownBoundary->SetPosition(FVector2D(480.0f, 870.0f));
	DownBoundary->BeginPlay();

	// 
	ABlock* LeftBoundary = GetActiveLevel()->InitializeActorForPlay<ABlock>();
	LeftBoundary->m_CollisionSize = FVector2D(60.0f, 780.0f);
	LeftBoundary->SetPosition(FVector2D(0.0f, 450.0f));
	LeftBoundary->BeginPlay();

	// 
	ABlock* RightBoundary = GetActiveLevel()->InitializeActorForPlay<ABlock>();
	RightBoundary->m_CollisionSize = FVector2D(60.0f, 780.0f);
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
	SpawnedCharacter->SetPosition(PositionVector);
	SpawnedCharacter->SetCharacterName(strCharacterName);
	SpawnedCharacter->SetBombLeft(1);
	SpawnedCharacter->SetBombRange(1);
	SpawnedCharacter->SetSpeed(240.0f);
	SpawnedCharacter->SetMaxSpeed(400.0f);
	URenderComponent* RenderComponent = SpawnedCharacter->CreateDefaultSubobject<URenderComponent>();
	RenderComponent->SetStaticImageOffset(FVector2D(0.0f, -12.0f));
	RenderComponent->SetStaticImage("Resources\\" + strCharacterName + "\\" + "DownIdle.bmp");
	RenderComponent->SetShadowImageOffset(FVector2D(0.0f, 25.0f));
	RenderComponent->SetShadowImage("Resources\\Shadows\\CharacterShadow.bmp");
	RenderComponent->SetRenderPriority(VectorToRenderPriority(SpawnedCharacter->GetPosition()));
	RenderComponent->SetRenderType(URenderComponent::ERenderType::ShadowObject);
	RenderComponent->CreateAnimation("DownWalk", "Resources\\" + strCharacterName + "\\DownWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("LeftWalk", "Resources\\" + strCharacterName + "\\LeftWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("RightWalk", "Resources\\" + strCharacterName + "\\RightWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("UpWalk", "Resources\\" + strCharacterName + "\\UpWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("BubbleLoop", "Resources\\" + strCharacterName + "\\BubbleLoop", 2, 0.25f, true);
	RenderComponent->CreateAnimation("BubbleFade", "Resources\\" + strCharacterName + "\\BubbleFade", 2, 0.5f, false);
	RenderComponent->CreateAnimation("Death", "Resources\\" + strCharacterName + "\\Death", 5, 0.1f, false);

	UBombManager* BombManager = GetGameInstance()->GetGameInstanceSubsystem<UBombManager>();
	BombManager->AddCharacter(SpawnedCharacter);

	SpawnedCharacter->BeginPlay();
	return SpawnedCharacter;
}

ACharacter* USpawnManager::SpawnDao(FVector2D PositionVector)
{
	string strCharacterName = "Dao";
	ACharacter* SpawnedCharacter = GetActiveLevel()->InitializeActorForPlay<ACharacter>();
	SpawnedCharacter->SetCharacterName(strCharacterName);
	SpawnedCharacter->SetPosition(PositionVector);
	SpawnedCharacter->SetBombLeft(2);
	SpawnedCharacter->SetBombRange(1);
	SpawnedCharacter->SetSpeed(200.0f);
	SpawnedCharacter->SetMaxSpeed(400.0f);
	URenderComponent* RenderComponent = SpawnedCharacter->CreateDefaultSubobject<URenderComponent>();
	RenderComponent->SetStaticImageOffset(FVector2D(0.0f, -12.0f));
	RenderComponent->SetStaticImage("Resources\\" + strCharacterName + "\\" + "DownIdle.bmp");
	RenderComponent->SetShadowImageOffset(FVector2D(0.0f, 25.0f));
	RenderComponent->SetShadowImage("Resources\\Shadows\\CharacterShadow.bmp");
	RenderComponent->SetRenderPriority(VectorToRenderPriority(SpawnedCharacter->GetPosition()));
	RenderComponent->SetRenderType(URenderComponent::ERenderType::ShadowObject);
	RenderComponent->CreateAnimation("DownWalk", "Resources\\" + strCharacterName + "\\DownWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("LeftWalk", "Resources\\" + strCharacterName + "\\LeftWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("RightWalk", "Resources\\" + strCharacterName + "\\RightWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("UpWalk", "Resources\\" + strCharacterName + "\\UpWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("BubbleLoop", "Resources\\" + strCharacterName + "\\BubbleLoop", 2, 0.25f, true);
	RenderComponent->CreateAnimation("BubbleFade", "Resources\\" + strCharacterName + "\\BubbleFade", 2, 0.5f, false);

	SpawnedCharacter->BeginPlay();
	return SpawnedCharacter;
}

ACharacter* USpawnManager::SpawnCappi(FVector2D PositionVector)
{
	string strCharacterName = "Cappi";
	ACharacter* SpawnedCharacter = GetActiveLevel()->InitializeActorForPlay<ACharacter>();
	SpawnedCharacter->SetCharacterName(strCharacterName);
	SpawnedCharacter->SetPosition(PositionVector);
	SpawnedCharacter->SetBombLeft(1);
	SpawnedCharacter->SetBombRange(2);
	SpawnedCharacter->SetSpeed(200.0f);
	SpawnedCharacter->SetMaxSpeed(400.0f);
	URenderComponent* RenderComponent = SpawnedCharacter->CreateDefaultSubobject<URenderComponent>();
	RenderComponent->SetStaticImageOffset(FVector2D(0.0f, -12.0f));
	RenderComponent->SetStaticImage("Resources\\" + strCharacterName + "\\" + "DownIdle.bmp");
	RenderComponent->SetShadowImageOffset(FVector2D(0.0f, 25.0f));
	RenderComponent->SetShadowImage("Resources\\Shadows\\CharacterShadow.bmp");
	RenderComponent->SetRenderPriority(VectorToRenderPriority(SpawnedCharacter->GetPosition()));
	RenderComponent->SetRenderType(URenderComponent::ERenderType::ShadowObject);
	RenderComponent->CreateAnimation("DownWalk", "Resources\\" + strCharacterName + "\\DownWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("LeftWalk", "Resources\\" + strCharacterName + "\\LeftWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("RightWalk", "Resources\\" + strCharacterName + "\\RightWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("UpWalk", "Resources\\" + strCharacterName + "\\UpWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("BubbleLoop", "Resources\\" + strCharacterName + "\\BubbleLoop", 2, 0.25f, true);
	RenderComponent->CreateAnimation("BubbleFade", "Resources\\" + strCharacterName + "\\BubbleFade", 2, 0.5f, false);
	RenderComponent->CreateAnimation("Death", "Resources\\" + strCharacterName + "\\Death", 5, 0.1f, false);

	SpawnedCharacter->BeginPlay();
	return SpawnedCharacter;
}

ACharacter* USpawnManager::SpawnMarid(FVector2D PositionVector)
{
	string strCharacterName = "Marid";
	ACharacter* SpawnedCharacter = GetActiveLevel()->InitializeActorForPlay<ACharacter>();
	SpawnedCharacter->SetCharacterName(strCharacterName);
	SpawnedCharacter->SetPosition(PositionVector);
	SpawnedCharacter->SetBombLeft(2);
	SpawnedCharacter->SetBombRange(1);
	SpawnedCharacter->SetSpeed(200.0f);
	SpawnedCharacter->SetMaxSpeed(400.0f);
	URenderComponent* RenderComponent = SpawnedCharacter->CreateDefaultSubobject<URenderComponent>();
	RenderComponent->SetStaticImageOffset(FVector2D(0.0f, -12.0f));
	RenderComponent->SetStaticImage("Resources\\" + strCharacterName + "\\" + "DownIdle.bmp");
	RenderComponent->SetShadowImageOffset(FVector2D(0.0f, 25.0f));
	RenderComponent->SetShadowImage("Resources\\Shadows\\CharacterShadow.bmp");
	RenderComponent->SetRenderPriority(VectorToRenderPriority(SpawnedCharacter->GetPosition()));
	RenderComponent->SetRenderType(URenderComponent::ERenderType::ShadowObject);
	RenderComponent->CreateAnimation("DownWalk", "Resources\\" + strCharacterName + "\\DownWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("LeftWalk", "Resources\\" + strCharacterName + "\\LeftWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("RightWalk", "Resources\\" + strCharacterName + "\\RightWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("UpWalk", "Resources\\" + strCharacterName + "\\UpWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("BubbleLoop", "Resources\\" + strCharacterName + "\\BubbleLoop", 2, 0.25f, true);
	RenderComponent->CreateAnimation("BubbleFade", "Resources\\" + strCharacterName + "\\BubbleFade", 2, 0.5f, false);

	SpawnedCharacter->BeginPlay();
	return SpawnedCharacter;
}

APowerUpItem* USpawnManager::SpawnRandomItem(FVector2D PositionVector)
{
	int nRandomInt = rand();
	int nItemTypeCount = static_cast<int>(EItemCode::End);
	nRandomInt %= nItemTypeCount;

	return SpawnItem(PositionVector, static_cast<EItemCode>(nRandomInt));
}

APowerUpItem* USpawnManager::SpawnItem(FVector2D PositionVector, EItemCode ItemCode)
{
	APowerUpItem* SpawnedItem = GetActiveLevel()->InitializeActorForPlay<APowerUpItem>();
	SpawnedItem->SetPosition(PositionVector);
	SpawnedItem->SetItemCode(ItemCode);

	URenderComponent* RenderComponent = SpawnedItem->CreateDefaultSubobject<URenderComponent>();
	RenderComponent->SetRenderPriority(VectorToRenderPriority(PositionVector));
	RenderComponent->SetStaticImageOffset(FVector2D(0.0f, -30.0f));
	RenderComponent->SetRenderType(URenderComponent::ERenderType::ShadowObject);
	RenderComponent->SetShadowImage("Resources\\Shadows\\SmallShadow.bmp");
	RenderComponent->SetShadowImageOffset(FVector2D(0.0f, 5.0f));

	switch (ItemCode)
	{
	case EItemCode::BombCount:
		RenderComponent->SetStaticImage("Resources\\PowerUps\\Count.bmp");
		RenderComponent->CreateAnimation("Shine", "Resources\\PowerUps\\Count", 2, 0.25f, true);
		break;
	case EItemCode::BombRange:
		RenderComponent->SetStaticImage("Resources\\PowerUps\\Range.bmp");
		RenderComponent->CreateAnimation("Shine", "Resources\\PowerUps\\Range", 2, 0.25f, true);
		break;
	case EItemCode::Speed:
		RenderComponent->SetStaticImage("Resources\\PowerUps\\Speed.bmp");
		RenderComponent->CreateAnimation("Shine", "Resources\\PowerUps\\Speed", 2, 0.25f, true);
		break;
	}

	SpawnedItem->BeginPlay();
	return SpawnedItem;
}

ABomb* USpawnManager::SpawnBomb(FVector2D PositionVector, ACharacter* Spawner)
{
	ABomb* BombActor = GetActiveLevel()->InitializeActorForPlay<ABomb>();
	BombActor->SetPosition(PositionVector);
	BombActor->SetSpawner(Spawner);
	BombActor->SetTimer(3.0f);
	BombActor->SetBombRange(Spawner->GetBombRange());

	URenderComponent* RenderComponent = BombActor->CreateDefaultSubobject<URenderComponent>();
	RenderComponent->SetStaticImage("Resources\\Bomb\\bomb_0.bmp");
	RenderComponent->SetShadowImage("Resources\\Shadows\\CharacterShadow.bmp");
	RenderComponent->SetStaticImageOffset(FVector2D(0.0f, 0.0f));
	RenderComponent->SetShadowImageOffset(FVector2D(0.0f, 25.0f));
	RenderComponent->SetRenderPriority(VectorToRenderPriority(PositionVector));
	RenderComponent->SetRenderType(URenderComponent::ERenderType::ShadowObject);
	RenderComponent->CreateAnimation("Bomb\\bomb", "Resources\\Bomb\\bomb", 4, 0.2f, true);


	BombActor->BeginPlay();
	return BombActor;
}

AExplosion* USpawnManager::SpawnExplosion(FVector2D PositionVector, int nDirection, bool bIsEnd)
{
	return this->SpawnExplosion(PositionVector, nDirection, 0.0f, bIsEnd);
}

AExplosion* USpawnManager::SpawnExplosion(FVector2D PositionVector, int nDirection, float fDelayTimer, bool bIsEnd)
{
	AExplosion* ExplosionActor = GetActiveLevel()->InitializeActorForPlay<AExplosion>();
	ExplosionActor->SetPosition(PositionVector);
	ExplosionActor->SetTimer(0.4f);
	URenderComponent* RenderComponent = ExplosionActor->CreateDefaultSubobject<URenderComponent>();
	RenderComponent->SetRenderPriority(VectorToRenderPriority(PositionVector));
	RenderComponent->SetRenderType(URenderComponent::ERenderType::NonShadowObject);

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
