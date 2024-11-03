#include "stdafx.h"
#include "Level.h"
#include "Actor.h"


void ULevel::Release()
{
	auto ActorIter = m_Actors.begin();
	while (ActorIter != m_Actors.end())
	{
		if (*ActorIter)
		{
			delete* ActorIter;
		}
		++ActorIter;
	}
}

ULevel::ULevel()
	:
	m_GameInstance{},
	m_Actors{},
	m_PlayerController{}
{
}

ULevel::~ULevel()
{
	this->Release();
}

APlayerController* ULevel::GetPlayerController() const
{
	return m_PlayerController;
}

UGameInstance* ULevel::GetGameInstance() const
{
	return m_GameInstance;
}

void ULevel::Tick(float fDeltaTime)
{
	auto ActorIter = m_Actors.begin();

	while (ActorIter != m_Actors.end())
	{
		(*ActorIter)->Tick(fDeltaTime);

		++ActorIter;
	}
}

void ULevel::LateTick(float fDeltaTime)
{
	auto ActorIter = m_Actors.begin();

	while (ActorIter != m_Actors.end())
	{
		(*ActorIter)->LateTick(fDeltaTime);

		++ActorIter;
	}
}

void ULevel::BeginPlay()
{
	//auto ActorIter = m_Actors.begin();

	//while (ActorIter != m_Actors.end())
	//{
	//	(*ActorIter)->BeginPlay();

	//	++ActorIter;
	//}
}
