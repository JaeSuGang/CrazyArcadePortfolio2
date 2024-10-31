#include "stdafx.h"
#include "Level.h"
#include "GameInstance.h"

void UGameInstance::Release()
{

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

void UGameInstance::BeginPlay()
{
	m_ActiveLevel->BeginPlay();
}

void UGameInstance::Initialize()
{

}

ULevel* UGameInstance::GetActiveLevel() const
{
	return m_ActiveLevel;
}


