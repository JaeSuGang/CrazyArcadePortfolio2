#include "stdafx.h"
#include "TestLevel.h"
#include "TestPlayer.h"
#include "TestGamemode.h"

void UTestLevel::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);


}

void UTestLevel::BeginPlay()
{
	Super::BeginPlay();

	SpawnActor<ATestPlayer>();

}

void UTestLevel::Initialize()
{
	InitializeGamemodeForPlay<ATestGamemode>();

}
