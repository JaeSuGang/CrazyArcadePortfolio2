#include "stdafx.h"
#include "WallComponent.h"
#include "MovementManager.h"

void UWallComponent::RegisterAtMovementManager()
{
	UMovementManager* MovementManager = GetGameInstanceSubsystem<UMovementManager>();
	MovementManager->AddWall(this);
}

void UWallComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWallComponent::TickComponent(float fDeltaTime)
{
	Super::TickComponent(fDeltaTime);
}
