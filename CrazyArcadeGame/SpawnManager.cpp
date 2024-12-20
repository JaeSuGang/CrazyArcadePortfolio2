#include "stdafx.h"
#include "Character.h"
#include "KmEngine/Level.h"
#include "KmEngine/PlayerController.h"
#include "CharacterAIController.h"
#include "KmEngine/RenderComponent.h"
#include "KmEngine/RandomManager.h"
#include "MainGameInstance.h"
#include "GameUI.h"
#include "SpawnManager.h"
#include "MovementManager.h"
#include "BombManager.h"
#include "Tilemap.h"
#include "Bomb.h"
#include "Block.h"
#include "Explosion.h"
#include "PowerUpItem.h"
#include "AIManager.h"
#include "GameLevelBase.h"


ACharacterAIController* USpawnManager::SpawnRandomAICharacter(ACharacter* Spawner)
{
	return this->SpawnRandomAICharacter(Spawner->GetPosition());
}

ACharacterAIController* USpawnManager::SpawnRandomAICharacter(FVector2D SpawnPos)
{
	URandomManager* RandomManager = GEngine->GetEngineSubsystem<URandomManager>();
	int nRandomNumber = RandomManager->GenerateRandomNumber((int)UMainGameInstance::ECharacterType::Bazzi, (int)UMainGameInstance::ECharacterType::End);

	UMainGameInstance::ECharacterType RandomCharacterType = (UMainGameInstance::ECharacterType)nRandomNumber;

	ACharacter* SpawningCharacter{};
	switch (RandomCharacterType)
	{
	case UMainGameInstance::ECharacterType::Bazzi:
	{
		SpawningCharacter = SpawnBazzi(SpawnPos);
		SpawningCharacter->SetDebugPen(CreatePen(PS_SOLID, 3, RGB(0, 255, 0)));
		break;
	}
	case UMainGameInstance::ECharacterType::Dao:
	{
		SpawningCharacter = SpawnDao(SpawnPos);
		SpawningCharacter->SetDebugPen(CreatePen(PS_SOLID, 3, RGB(255, 127, 0)));
		break;
	}
	case UMainGameInstance::ECharacterType::Cappi:
	{
		SpawningCharacter = SpawnCappi(SpawnPos);
		SpawningCharacter->SetDebugPen(CreatePen(PS_SOLID, 3, RGB(15, 180, 252)));
		break;
	}
	case UMainGameInstance::ECharacterType::Marid:
	{
		SpawningCharacter = SpawnMarid(SpawnPos);
		SpawningCharacter->SetDebugPen(CreatePen(PS_SOLID, 3, RGB(255, 212, 0)));
		break;
	}
	}

	ACharacterAIController* SpawnedAIController{};
	SpawnedAIController = this->SpawnCharacterAIController();
	SpawnedAIController->Possess(SpawningCharacter);

	return SpawnedAIController;
}

ABlock* USpawnManager::GenerateVoidWallTile(FVector2D Pos)
{
	ABlock* TileActor = GetActiveLevel()->InitializeActorForPlay<ABlock>();
	TileActor->SetPosition(Pos);
	TileActor->BeginPlay();

	return TileActor;
}

void USpawnManager::GenerateWallTile(FVector2D Pos, int nTileValue, int nGroundTileValue)
{
	if (nTileValue == 0)
		return;

	UResourceManager* ResourceManager = GEngine->GetEngineSubsystem<UResourceManager>();
	FVector2D LocationVector{ Pos };
	ABlock* TileActor = GetActiveLevel()->InitializeActorForPlay<ABlock>();
	URenderComponent* PositionedTileRenderComponent = TileActor->CreateDefaultSubobject<URenderComponent>();

	// 벽 특성 설정
	switch (nTileValue)
	{
	case 0:
		break;

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
	PositionedTileRenderComponent->SetRenderPriority(VectorToRenderPriority(Pos));
	PositionedTileRenderComponent->SetRenderType(URenderComponent::ERenderType::ShadowObject);
	PositionedTileRenderComponent->SetStaticImage("Resources\\Tiles\\WallTiles\\" + std::to_string(nTileValue) + ".bmp");



	TileActor->BeginPlay();
}

void USpawnManager::GenerateWallTile(int nTileLocationIndex, int nTileValue, int nGroundTileValue)
{
	this->GenerateWallTile(TileIndexToVector(nTileLocationIndex), nTileValue, nGroundTileValue);
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

	for (int i = -1; i < 16; i++)
	{
		for (int j = -1; j < 14; j++)
		{
			if (i < 0 || i > 14 || j < 0 || j > 12)
			{
				FVector2D Pos = { 60.0f + (i * TILE_WIDTH), 90.0f + (j * TILE_HEIGHT) };
				this->GenerateVoidWallTile(Pos);
			}
		}
	}


	//// 
	//ABlock* UpBoundary = GetActiveLevel()->InitializeActorForPlay<ABlock>();
	//UpBoundary->m_CollisionSize = FVector2D(900.0f, 60.0f);
	//UpBoundary->SetPosition(FVector2D(480.0f, 30.0f));
	//UpBoundary->BeginPlay();

	//// 
	//ABlock* DownBoundary = GetActiveLevel()->InitializeActorForPlay<ABlock>();
	//DownBoundary->m_CollisionSize = FVector2D(900.0f, 60.0f);
	//DownBoundary->SetPosition(FVector2D(480.0f, 870.0f));
	//DownBoundary->BeginPlay();

	//// 
	//ABlock* LeftBoundary = GetActiveLevel()->InitializeActorForPlay<ABlock>();
	//LeftBoundary->m_CollisionSize = FVector2D(60.0f, 780.0f);
	//LeftBoundary->SetPosition(FVector2D(0.0f, 450.0f));
	//LeftBoundary->BeginPlay();

	//// 
	//ABlock* RightBoundary = GetActiveLevel()->InitializeActorForPlay<ABlock>();
	//RightBoundary->m_CollisionSize = FVector2D(60.0f, 780.0f);
	//RightBoundary->SetPosition(FVector2D(960.0f, 450.0f));
	//RightBoundary->BeginPlay();
}

AGameUI* USpawnManager::SpawnTopMostGameUI(string strImagePath, FVector2D PositionVector)
{
	AGameUI* GameUI = GetActiveLevel()->InitializeActorForPlay<AGameUI>();
	URenderComponent* RenderComponent = GameUI->CreateDefaultSubobject<URenderComponent>();
	RenderComponent->SetStaticImage(strImagePath);
	RenderComponent->SetRenderType(URenderComponent::ERenderType::NonShadowObject);
	RenderComponent->SetRenderPriority(1000);
	RenderComponent->BeginPlay();
	GameUI->SetPosition(PositionVector);
	return GameUI;
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

AGameUI* USpawnManager::SpawnGameUI(string strImagePath, FVector2D PositionVector, float fRenderPriority)
{
	AGameUI* GameUI = SpawnGameUI(strImagePath, PositionVector);
	GameUI->GetComponentByClass<URenderComponent>()->SetRenderPriority(fRenderPriority);
	return GameUI;
}

ACharacter* USpawnManager::SpawnBazzi(FVector2D PositionVector)
{
	string strCharacterName = "Bazzi";
	ACharacter* SpawnedCharacter = GetActiveLevel()->InitializeActorForPlay<ACharacter>();
	if (UGameLevelBase* CastedGameLevelBase = dynamic_cast<UGameLevelBase*>(GetActiveLevel()))
		CastedGameLevelBase->AddToCharacters(SpawnedCharacter);
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

	UBombManager* BombManager = GetGameInstance()->GetSubsystem<UBombManager>();
	BombManager->AddCharacter(SpawnedCharacter);

	SpawnedCharacter->BeginPlay();
	return SpawnedCharacter;
}

ACharacter* USpawnManager::SpawnDao(FVector2D PositionVector)
{
	string strCharacterName = "Dao";
	ACharacter* SpawnedCharacter = GetActiveLevel()->InitializeActorForPlay<ACharacter>();
	if (UGameLevelBase* CastedGameLevelBase = dynamic_cast<UGameLevelBase*>(GetActiveLevel()))
		CastedGameLevelBase->AddToCharacters(SpawnedCharacter);
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
	RenderComponent->CreateAnimation("Death", "Resources\\" + strCharacterName + "\\Death", 5, 0.1f, false);

	SpawnedCharacter->BeginPlay();
	return SpawnedCharacter;
}   

ACharacter* USpawnManager::SpawnCappi(FVector2D PositionVector)
{
	string strCharacterName = "Cappi";
	ACharacter* SpawnedCharacter = GetActiveLevel()->InitializeActorForPlay<ACharacter>();
	if (UGameLevelBase* CastedGameLevelBase = dynamic_cast<UGameLevelBase*>(GetActiveLevel()))
		CastedGameLevelBase->AddToCharacters(SpawnedCharacter);
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
	if (UGameLevelBase* CastedGameLevelBase = dynamic_cast<UGameLevelBase*>(GetActiveLevel()))
		CastedGameLevelBase->AddToCharacters(SpawnedCharacter);
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
	RenderComponent->CreateAnimation("Death", "Resources\\" + strCharacterName + "\\Death", 5, 0.1f, false);

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
	URenderComponent* RenderComponent = PlayerController->CreateDefaultSubobject<URenderComponent>();
	RenderComponent->SetStaticImage("Resources\\UI\\small_arrow.bmp");
	RenderComponent->SetStaticImageOffset(FVector2D(0.0f, -60.0f));
	RenderComponent->SetRenderPriority(1000.0f);
	RenderComponent->SetRenderType(URenderComponent::ERenderType::NonShadowObject);
	PlayerController->BeginPlay();
	return PlayerController;
}

ACharacterAIController* USpawnManager::SpawnCharacterAIController()
{
	ACharacterAIController* AIController = GetActiveLevel()->InitializeActorForPlay<ACharacterAIController>();
	AIController->BeginPlay();
	return AIController;
}

void USpawnManager::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);


}
