#include "stdafx.h"
#include "MovableComponent.h"
#include "MovementManager.h"

FVector2D UMovableComponent::GetCollisionSize() const
{
	return m_CollisionSize;
}

void UMovableComponent::SetCollisionSize(FVector2D Size)
{
	m_CollisionSize = Size;
}

void UMovableComponent::AddVelocity(FVector2D Velocity)
{
	m_Velocity += Velocity;
}

void UMovableComponent::SetVelocity(FVector2D Velocity)
{
	m_Velocity = Velocity;
}

void UMovableComponent::SetMaxSpeed(float MaxSpeed)
{
	m_MaxSpeed = MaxSpeed;
}

float UMovableComponent::GetMaxSpeed()
{
	return m_MaxSpeed;
}

FVector2D UMovableComponent::GetVelocity()
{
	return m_Velocity;
}

void UMovableComponent::RegisterMovableAtMovementManager()
{
	UMovementManager* MovementManager = GetGameInstanceSubsystem<UMovementManager>();
	MovementManager->AddMovable(this);
}

void UMovableComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMovableComponent::TickComponent(float fDeltaTime)
{
	Super::TickComponent(fDeltaTime);
}

UMovableComponent::UMovableComponent()
	:
	m_Velocity{},
	m_MaxSpeed{},
	m_bFlying{},
	m_CollisionSize{}
{
}
