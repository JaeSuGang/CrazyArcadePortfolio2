#include "stdafx.h"
#include "Level.h"
#include "GameInstance.h"

void UGameInstance::Release()
{
	auto iter = m_LoadedLevels.begin();
	while (iter != m_LoadedLevels.end())
	{
		SAFE_DELETE(iter->second);
		++iter;
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

void UGameInstance::BeginPlay()
{
	m_ActiveLevel->BeginPlay();
}

void UGameInstance::Initialize()
{

}

void UGameInstance::OpenLevel(const char* lpszLevelName)
{
	auto LevelIter = m_LoadedLevels.find(string(lpszLevelName));

	if (LevelIter == m_LoadedLevels.end())
	{
		SHOW_ERROR("존재하지 않는 Key의 Level을 OpenLevel 했습니다");
	}

	ULevel* OpenedLevel = (*LevelIter).second;

	OpenedLevel->BeginPlay();

	m_ActiveLevel = OpenedLevel;
}

ULevel* UGameInstance::GetActiveLevel() const
{
	return m_ActiveLevel;
}

void UGameInstance::LoadLevel(const char* lpszLevelName, ULevel* Level)
{
	pair<string, ULevel*> PairToInsert{ string(lpszLevelName), Level };
	m_LoadedLevels.insert(PairToInsert);
}


