#include "stdafx.h"
#include "MovableComponent.h"
#include "MovementManager.h"

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

float UMovableComponent::GetRadius() const
{
	return m_fCollisionRadius;
}

void UMovableComponent::SetRadius(float fRadius)
{
	m_fCollisionRadius = fRadius;
}

FVector2D UMovableComponent::GetVelocity()
{
	return m_Velocity;
}

void UMovableComponent::RegisterAtMovementManager()
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
	m_fCollisionRadius{},
	m_Velocity{},
	m_MaxSpeed{}
{
}
