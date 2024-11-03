#include "stdafx.h"
#include "Level.h"
#include "GameInstance.h"
#include "GameInstanceSubsystem.h"

void UGameInstance::Release()
{
	SAFE_DELETE(m_ActiveLevel);

	auto SubsystemIter = m_Subsystems.begin();
	while (SubsystemIter != m_Subsystems.end())
	{
		delete SubsystemIter->second;
		++SubsystemIter;
	}
}

UGameInstance::UGameInstance()
	:
	m_ActiveLevel{}
{

}

UGameInstance::~UGameInstance()
{
	this->Release();
}

void UGameInstance::Tick(float fDeltaTime)
{
	m_ActiveLevel->Tick(fDeltaTime);
}

void UGameInstance::LateTick(float fDeltaTime)
{
	m_ActiveLevel->LateTick(fDeltaTime);
}

void UGameInstance::BeginPlay()
{

}

void UGameInstance::Initialize()
{

}

ULevel* UGameInstance::GetActiveLevel() const
{
	return m_ActiveLevel;
}


