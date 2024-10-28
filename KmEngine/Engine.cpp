#include "stdafx.h"
#include "Engine.h"
#include "KeyManager.h"

UKeyManager* UEngine::GetKeyManager()
{
	auto iter = m_Managers.find("UKeyManager");

	if (iter == m_Managers.end())
	{
		MSG_ASSERT("GetKeyManager()를 호출하기 전에 CreateKeyManager()를 호출하세요");
	}

	return 
}
