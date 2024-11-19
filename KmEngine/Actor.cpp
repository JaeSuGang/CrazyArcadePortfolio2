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

	if (m_DebugMode)
		this->OnDebug();
}

void AActor::LateTick(float fDeltaTime)
{

}

void AActor::OnDebug()
{

}

void AActor::Destroy()
{
	auto FindIter = std::find(m_Level->m_ActorsToDestroy.begin(), m_Level->m_ActorsToDestroy.end(), this);
	if (FindIter != m_Level->m_ActorsToDestroy.end())
		return;

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

ULevel* AActor::GetLevel() const
{
	return m_Level;
}

UGameInstance* AActor::GetGameInstance() const
{
	return GEngine->GetGameInstance();
}

