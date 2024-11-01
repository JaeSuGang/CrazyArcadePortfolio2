#include "stdafx.h"
#include "TestLevel.h"
#include "Character.h"
#include "TestGamemode.h"

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

	SpawnActor<ACharacter>();

}

void UTestLevel::Initialize()
{
	InitializeGamemodeForPlay<ATestGamemode>();

}
