#include "stdafx.h"
#include "ActorComponent.h"


AActor* UActorComponent::GetOwner() const
{
	return m_Owner;
}

void UActorComponent::BeginPlay()
{

}

void UActorComponent::TickComponent(float fDeltaTime)
{
}

UActorComponent::UActorComponent()
	:
	m_Owner{}
{

}
