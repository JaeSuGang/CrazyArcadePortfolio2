#include "stdafx.h"
#include "SoundManager.h"


void USoundManager::Initialize()
{
	FMOD_RESULT Result = FMOD::System_Create(&m_FModSystem);

	if (Result != FMOD_RESULT::FMOD_OK)
	{
		SHOW_ERROR("FMOD System Initialize Failed");
	}
}
