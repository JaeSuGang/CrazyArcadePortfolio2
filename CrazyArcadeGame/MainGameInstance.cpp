#include "stdafx.h"
#include "MainGameInstance.h"
#include "KmEngine/Level.h"
#include "KmEngine/Engine.h"
#include "KmEngine/ResourceManager.h"
#include "SpawnManager.h"
#include "MovementManager.h"
#include "GameLevelBase.h"
#include "AIManager.h"
#include "BombManager.h"
#include "LobbyLevel.h"

void UMainGameInstance::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);


}

void UMainGameInstance::LateTick(float fDeltaTime)
{
	Super::LateTick(fDeltaTime);
}

void UMainGameInstance::BeginPlay()
{
	Super::BeginPlay();

	USpawnManager* SpawnManager = CreateSubsystem<USpawnManager>();
	UMovementManager* MovementManager = CreateSubsystem<UMovementManager>();
	UBombManager* BombManager = CreateSubsystem<UBombManager>();
	UAIManager* AIManager = CreateSubsystem<UAIManager>();

	this->OpenLevel<ULobbyLevel>();
}

