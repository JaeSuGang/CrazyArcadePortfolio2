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

	USpawnManager* SpawnManager = CreateGameInstanceSubsystem<USpawnManager>();
	UMovementManager* MovementManager = CreateGameInstanceSubsystem<UMovementManager>();
	UBombManager* BombManager = CreateGameInstanceSubsystem<UBombManager>();
	UAIManager* AIManager = CreateGameInstanceSubsystem<UAIManager>();

	this->OpenLevel<ULobbyLevel>();
}

