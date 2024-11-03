#include "stdafx.h"
#include "PhysicsComponent.h"

void UPhysicsComponent::SetColliderRadius(float Radius)
{
	m_Collider.Radius = Radius;
}

void UPhysicsComponent::SetColliderShape(FCollider::EShape Shape)
{
	m_Collider.Shape = Shape;
}

void UPhysicsComponent::EnableCollision()
{
	m_Collider.Enabled = true;
}

void UPhysicsComponent::DisableCollision()
{
	m_Collider.Enabled = false;
}

void UPhysicsComponent::AddVelocity(FVector2D AddedVelocity)
{
	m_Velocity += AddedVelocity;
}

void UPhysicsComponent::SetVelocity(FVector2D Velocity)
{
	m_Velocity = Velocity;
}

FVector2D UPhysicsComponent::GetVelocity()
{
	return m_Velocity;
}

float UPhysicsComponent::GetMaxSpeed() const
{
	return m_fMaxSpeed;
}

void UPhysicsComponent::SetMaxSpeed(float fValue)
{
	m_fMaxSpeed = fValue;
}

void UPhysicsComponent::BeginPlay()
{
	Super::BeginPlay();


}

void UPhysicsComponent::TickComponent(float fDeltaTime)
{
	Super::TickComponent(fDeltaTime);


}

UPhysicsComponent::UPhysicsComponent()
	:
	m_Collider{},
	m_Velocity{},
	m_fMaxSpeed{}
{
	m_Collider.Enabled = false;
}
