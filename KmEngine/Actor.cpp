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

void AActor::Initialize()
{

}
