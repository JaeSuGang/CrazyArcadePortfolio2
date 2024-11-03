#include "stdafx.h"
#include "TestLevel.h"
#include "Character.h"
#include "KmEngine/Engine.h"
#include "KmEngine/GameInstance.h"
#include "KmEngine/PlayerController.h"
#include "GameUI.h"
#include "SpawnManager.h"
#include "MovementManager.h"

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

	AGameUI* InGameUI = SpawnManager->SpawnGameUI("Resources\\GUI\\GameUI2.bmp", FVector2D(600.0f, 446.0f));

	APlayerController* PlayerController = SpawnManager->SpawnPlayerController();

	ACharacter* MainCharacter = SpawnManager->SpawnCharacter("Bazzi", FVector2D(300.0f, 300.0f));
	PlayerController->Possess(MainCharacter);
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
