#include "stdafx.h"
#include "Level.h"
#include "Actor.h"
#include "Gamemode.h"

void ULevel::Release()
{
	SAFE_DELETE(m_Gamemode);

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
	m_Actors{},
	m_Gamemode{}
{
}

ULevel::~ULevel()
{
	this->Release();
}

void ULevel::Tick(float fDeltaTime)
{
	m_Gamemode->Tick(fDeltaTime);

	auto ActorIter = m_Actors.begin();

	while (ActorIter != m_Actors.end())
	{
		(*ActorIter)->Tick(fDeltaTime);

		++ActorIter;
	}
}

void ULevel::BeginPlay()
{
	m_Gamemode->BeginPlay();

	auto ActorIter = m_Actors.begin();

	while (ActorIter != m_Actors.end())
	{
		(*ActorIter)->BeginPlay();

		++ActorIter;
	}
}
