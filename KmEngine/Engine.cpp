#include "stdafx.h"
#include "Engine.h"
#include "KeyManager.h"

UKeyManager* UEngine::GetKeyManager()
{
	auto iter = m_Managers.find("UKeyManager");

	if (iter == m_Managers.end())
	{
		MSG_ASSERT("GetKeyManager()�� ȣ���ϱ� ���� CreateKeyManager()�� ȣ���ϼ���");
	}

	return 
}
