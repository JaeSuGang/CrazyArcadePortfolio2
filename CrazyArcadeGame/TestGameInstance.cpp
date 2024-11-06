#include "stdafx.h"
#include "TestGameInstance.h"
#include "KmEngine/Level.h"
#include "KmEngine/Engine.h"
#include "KmEngine/ResourceManager.h"
#include "SpawnManager.h"
#include "MovementManager.h"
#include "GameLevelBase.h"
#include "AIManager.h"

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

	USpawnManager* SpawnManager = CreateGameInstanceSubsystem<USpawnManager>();
	UMovementManager* MovementManager = CreateGameInstanceSubsystem<UMovementManager>();
	UAIManager* AIManager = CreateGameInstanceSubsystem<UAIManager>();
#ifdef _DEBUG 
	MovementManager->EnableDebugRender();

#endif 

	this->OpenLevel<UGameLevelBase>();
}

