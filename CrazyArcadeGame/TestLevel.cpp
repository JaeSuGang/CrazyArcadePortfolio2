#include "stdafx.h"
#include "TestLevel.h"
#include "TestPlayer.h"

void UTestLevel::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);


}

void UTestLevel::BeginPlay()
{
	Super::BeginPlay();

	SpawnActor<ATestPlayer>();
}
