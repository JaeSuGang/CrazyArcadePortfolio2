#include "stdafx.h"
#include "SoundManager.h"
#include "ResourceManager.h"
#include "Engine.h"

void USoundManager::Initialize()
{
	FMOD_RESULT Result = FMOD::System_Create(&m_FModSystem);

	if (Result != FMOD_RESULT::FMOD_OK)
	{
		SHOW_ERROR("FMOD System Initialize Failed");
	}

	m_FModSystem->init(32, FMOD_DEFAULT, nullptr);
}

void USoundManager::Play(string strKey)
{
	LOWER_STRING(strKey);

	UResourceManager* ResourceManager = GEngine->GetEngineSubsystem<UResourceManager>();


	auto SoundIterator = ResourceManager->m_Sounds.find(strKey);

	if (SoundIterator == ResourceManager->m_Sounds.end())
		SHOW_ERROR("존재하지 않는 사운드입니다");

	USound* Sound = SoundIterator->second;
	FMOD::Channel* SoundChannel{};
	m_FModSystem->playSound(Sound->m_hSoundHandle, nullptr, false, &SoundChannel);
}

void USoundManager::Tick(float fDeltaTime)
{
	m_FModSystem->update();
}
