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

void AActor::Release()
{
	auto ComponentIter = m_OwnedComponents.begin();
	while (ComponentIter != m_OwnedComponents.end())
	{
		SAFE_DELETE((ComponentIter->second));
		++ComponentIter;
	}
}

AActor::~AActor()
{
	this->Release();
}

FVector2D AActor::GetPositionVector2D() const
{
	return m_Position;
}

void AActor::Initialize()
{

}
