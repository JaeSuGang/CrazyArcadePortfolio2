#include "stdafx.h"
#include "GameLevelBase.h"
#include "Character.h"
#include "KmEngine/Engine.h"
#include "KmEngine/GameInstance.h"
#include "KmEngine/PlayerController.h"
#include "KmEngine/SoundManager.h"
#include "GameUI.h"
#include "SpawnManager.h"
#include "BombManager.h"
#include "MovementManager.h"
#include "CharacterAIController.h"
#include "Tilemap.h"




void UGameLevelBase::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);


}

void UGameLevelBase::LateTick(float fDeltaTime)
{
	Super::LateTick(fDeltaTime);
}

void UGameLevelBase::BeginPlay()
{
	Super::BeginPlay();

	USpawnManager* SpawnManager = GetGameInstance()->GetGameInstanceSubsystem<USpawnManager>();
	UMovementManager* MovementManager = GetGameInstance()->GetGameInstanceSubsystem<UMovementManager>();
	APlayerController* PlayerController = SpawnManager->SpawnPlayerController();

	// UI 积己
	AGameUI* InGameUI = SpawnManager->SpawnGameUI("Resources\\UI\\InGameUI.bmp", FVector2D(600.0f, 450.0f));

	// 鸥老甘 积己
	m_Tilemap = new FTilemap{};
	m_Tilemap->Load("Resources\\TilemapData\\stage1.tilemap");
	SpawnManager->GenerateTilemap(m_Tilemap);

	// 皋牢 敲饭捞绢 积己
	ACharacter* MainCharacter = SpawnManager->SpawnBazzi(FVector2D(420.0f, 330.0f));
	PlayerController->Possess(MainCharacter);

	// AI 嚎 积己
	ACharacter* Dao = SpawnManager->SpawnDao(FVector2D(900.0f, 810.0f));
	SpawnManager->SpawnCharacterAIController()->Possess(Dao);
	ACharacter* Marid = SpawnManager->SpawnMarid(FVector2D(60.0f, 150.0f));
	SpawnManager->SpawnCharacterAIController()->Possess(Marid);
	ACharacter* Cappi = SpawnManager->SpawnCappi(FVector2D(840.0f, 150.0f));
	SpawnManager->SpawnCharacterAIController()->Possess(Cappi);

	// 家府 犁积
	USoundManager* SoundManager = GEngine->GetEngineSubsystem<USoundManager>();
	SoundManager->Play("Resources\\Sound\\Login.wav");
}

void UGameLevelBase::Release()
{
	UKeyManager* KeyManager = GEngine->GetEngineSubsystem<UKeyManager>();
	KeyManager->ClearBindKey();
	UMovementManager* MovementManager = GetGameInstance()->GetGameInstanceSubsystem<UMovementManager>();
	MovementManager->Reset();
	SAFE_DELETE(m_Tilemap);
}

UGameLevelBase::~UGameLevelBase()
{
	this->Release();
}
