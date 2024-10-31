#include "stdafx.h"
#include "TestGameInstance.h"
#include "TestGamemode.h"
#include "Level.h"
#include "Engine.h"
#include "ResourceManager.h"

void UTestGameInstance::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);


}

void UTestGameInstance::BeginPlay()
{
	Super::BeginPlay();

}

void UTestGameInstance::Initialize()
{
	Super::Initialize();

	GEngine->GetEngineSubsystem<UResourceManager>()->LoadFile("resources\\bazzi.BMP");
}
