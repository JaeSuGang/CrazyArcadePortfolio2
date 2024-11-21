#include "stdafx.h"
#include "TestGameInstance.h"
#include "KmEngine/Level.h"
#include "KmEngine/Engine.h"
#include "KmEngine/ResourceManager.h"
#include "SpawnManager.h"
#include "MovementManager.h"
#include "GameLevelBase.h"
#include "AIManager.h"
#include "BombManager.h"

void UTestGameInstance::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);


}

void UTestGameInstance::LateTick(float fDeltaTime)
{
	Super::LateTick(fDeltaTime);
}

void UTestGameInstance::BeginPlay()
{
	Super::BeginPlay();

	USpawnManager* SpawnManager = CreateSubsystem<USpawnManager>();
	UMovementManager* MovementManager = CreateSubsystem<UMovementManager>();
	UBombManager* BombManager = CreateSubsystem<UBombManager>();
	UAIManager* AIManager = CreateSubsystem<UAIManager>();

	this->OpenLevel<UGameLevelBase>();
}

