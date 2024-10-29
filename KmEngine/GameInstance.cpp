#include "stdafx.h"
#include "Level.h"
#include "GameInstance.h"

void UGameInstance::Release()
{
	SAFE_DELETE(m_ActiveLevel);
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
