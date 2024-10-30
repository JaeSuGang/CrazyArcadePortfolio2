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

void UGameInstance::OpenLevel(const char* lpszLevelName)
{
	auto LevelIter = m_LoadedLevels.find(string(lpszLevelName));

	if (LevelIter == m_LoadedLevels.end())
	{
		SHOW_ERROR("�������� �ʴ� Key�� Level�� OpenLevel �߽��ϴ�");
	}

	ULevel* OpenedLevel = (*LevelIter).second;

	OpenedLevel->BeginPlay();

	m_ActiveLevel = OpenedLevel;
}

void UGameInstance::LoadLevel(const char* lpszLevelName, ULevel* Level)
{
	pair<string, ULevel*> PairToInsert{ string(lpszLevelName), Level };
	m_LoadedLevels.insert(PairToInsert);
}


