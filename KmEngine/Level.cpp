#include "stdafx.h"
#include "Level.h"
#include "Actor.h"
#include "Gamemode.h"

ULevel::ULevel()
	:
	m_Actors{},
	m_Gamemode{}
{
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
