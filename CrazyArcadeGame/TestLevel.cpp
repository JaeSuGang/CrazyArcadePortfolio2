#include "stdafx.h"
#include "TestLevel.h"
#include "Character.h"
#include "GameGUI1.h"
#include "KmEngine/GameInstance.h"
#include "KmEngine/Engine.h"
#include "SpawnManager.h"

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
	SpawnManager->SpawnPlayerController();
	SpawnManager->SpawnCharacter("Bazzi", FVector2D(300.0f, 300.0f));
}
