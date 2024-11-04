#include "stdafx.h"
#include "TestLevel.h"
#include "Character.h"
#include "KmEngine/Engine.h"
#include "KmEngine/GameInstance.h"
#include "KmEngine/PlayerController.h"
#include "GameUI.h"
#include "SpawnManager.h"
#include "MovementManager.h"
#include "CharacterAIController.h"

void UTestLevel::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);


}

void UTestLevel::LateTick(float fDeltaTime)
{
	Super::LateTick(fDeltaTime);
}

void UTestLevel::BeginPlay()
{
	Super::BeginPlay();

	USpawnManager* SpawnManager = GetGameInstance()->GetGameInstanceSubsystem<USpawnManager>();
	UMovementManager* MovementManager = GetGameInstance()->GetGameInstanceSubsystem<UMovementManager>();
	APlayerController* PlayerController = SpawnManager->SpawnPlayerController();

	MovementManager->SetMapRange(RECT{30, 60, 930, 840});

	AGameUI* InGameUI = SpawnManager->SpawnGameUI("Resources\\UI\\GameUI3.bmp", FVector2D(600.0f, 450.0f));

	ACharacter* MainCharacter = SpawnManager->SpawnBazzi(FVector2D(300.0f, 300.0f));
	PlayerController->Possess(MainCharacter);

	ACharacter* Dao = SpawnManager->SpawnDao(FVector2D(700.0f, 120.0f));
	SpawnManager->SpawnCharacterAIController()->Possess(Dao);
	ACharacter* Marid = SpawnManager->SpawnMarid(FVector2D(100.0f, 600.0f));
	SpawnManager->SpawnCharacterAIController()->Possess(Marid);
	ACharacter* Cappi = SpawnManager->SpawnCappi(FVector2D(790.0f, 720.0f));
	SpawnManager->SpawnCharacterAIController()->Possess(Cappi);
}

void UTestLevel::Release()
{
	UKeyManager* KeyManager = GEngine->GetEngineSubsystem<UKeyManager>();
	KeyManager->ClearBindKey();
	UMovementManager* MovementManager = GetGameInstance()->GetGameInstanceSubsystem<UMovementManager>();
	MovementManager->Reset();
}

UTestLevel::~UTestLevel()
{
	this->Release();
}
