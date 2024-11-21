#include "stdafx.h"
#include "FSM.h"

UFSMComponent::UFSMComponent()
	:
	m_CurrentState{}
{
}

UFSMComponent::~UFSMComponent()
{
	for (std::pair<string, UBaseState*> Pair : m_States)
	{
		SAFE_DELETE(Pair.second);
	}
}

void UFSMComponent::BeginPlay()
{
}

void UFSMComponent::TickComponent(float fDeltaTime)
{
	m_CurrentState->OnStateUpdate(fDeltaTime);
}

void UBaseState::OnStateEnter()
{
}

void UBaseState::OnStateUpdate(float fDeltaTime)
{
}

void UBaseState::OnStateExit()
{
}

void UBaseState::SetOwner(AActor* Actor)
{
	m_Owner = Actor;
}
