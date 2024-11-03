#include "stdafx.h"
#include "TestLevel.h"
#include "Character.h"
#include "GameGUI1.h"
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


}

void UTestLevel::Initialize()
{
	InitializeGamemodeForPlay<ATestGamemode>();

}
