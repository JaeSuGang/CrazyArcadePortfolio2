#include "stdafx.h"
#include "Actor.h"

void AActor::Tick(float fDeltaTime)
{
	auto ComponentIter = m_OwnedComponents.begin();

	while (ComponentIter != m_OwnedComponents.end())
	{
		UActorComponent* Component = (*ComponentIter).second;

		Component->TickComponent(fDeltaTime);

		++ComponentIter;
	}
}

void AActor::BeginPlay()
{
	auto ComponentIter = m_OwnedComponents.begin();

	while (ComponentIter != m_OwnedComponents.end())
	{
		UActorComponent* Component = (*ComponentIter).second;

		Component->BeginPlay();

		++ComponentIter;
	}
}

FVector2D AActor::GetPositionVector2D() const
{
	return m_Position;
}

void AActor::Initialize()
{

}
