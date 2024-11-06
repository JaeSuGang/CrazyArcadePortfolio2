#include "stdafx.h"
#include "Actor.h"
#include "Level.h"

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

void AActor::LateTick(float fDeltaTime)
{

}

void AActor::Destroy()
{
	m_Level->m_ActorsToDestroy.push_back(this);
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

AActor::AActor()
	:
	m_OwnedComponents{},
	m_Position{},
	m_Level{}
{
}

AActor::~AActor()
{
	this->Release();
}

void AActor::SetPosition(FVector2D NewPosition)
{
	m_Position = NewPosition;
}

void AActor::AddPosition(FVector2D PositionToAdd)
{
	m_Position += PositionToAdd;
}

FVector2D AActor::GetPosition() const
{
	return m_Position;
}

