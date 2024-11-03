#include "stdafx.h"
#include "TestGameInstance.h"
#include "TestGamemode.h"
#include "KmEngine/Level.h"
#include "KmEngine/Engine.h"
#include "KmEngine/ResourceManager.h"
#include "SpawnManager.h"
#include "TestLevel.h"

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

}

void UTestGameInstance::Initialize()
{
	Super::Initialize();

	USpawnManager* SpawnManager = CreateGameInstanceSubsystem<USpawnManager>();

	this->OpenLevel<UTestLevel>();
}
