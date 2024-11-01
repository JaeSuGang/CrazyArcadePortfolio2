#include "stdafx.h"
#include "PhysicsComponent.h"

void UPhysicsComponent::AddVelocity(FVector2D AddedVelocity)
{
	m_Velocity += AddedVelocity;
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

void UPhysicsComponent::Initialize()
{
	Super::Initialize();


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
	m_bHasCollision{},
	m_Velocity{},
	m_fMaxSpeed{}
{

}
