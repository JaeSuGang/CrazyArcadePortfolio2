#include "stdafx.h"
#include "WallComponent.h"
#include "MovementManager.h"

FVector2D UWallComponent::GetCollisionSize() const
{
	return m_CollisionSize;
}

void UWallComponent::SetCollisionSize(FVector2D Size)
{
	m_CollisionSize = Size;
}

void UWallComponent::RegisterAtMovementManager(bool CanBeFliedOver)
{
	m_bCanBeFliedOver = CanBeFliedOver;
	UMovementManager* MovementManager = GetGameInstanceSubsystem<UMovementManager>();
	MovementManager->AddWall(this);
}

bool UWallComponent::GetCanBeFliedOver() const
{
	return m_bCanBeFliedOver;
}

void UWallComponent::SetCanBeFliedOver(bool bValue)
{
	m_bCanBeFliedOver = bValue;
}

void UWallComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWallComponent::TickComponent(float fDeltaTime)
{
	Super::TickComponent(fDeltaTime);
}
