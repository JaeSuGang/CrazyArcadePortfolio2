#include "stdafx.h"
#include "KeyManager.h"

bool UKeyManager::GetKeyDown(int VirtualKey)
{
	if (m_KeyStates[VirtualKey] == 0x8000)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UKeyManager::GetKeyPress(int VirtualKey)
{
	if (m_KeyStates[VirtualKey] == 0x8001)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void UKeyManager::BindAction(int VirtualKey, std::function<void()> Action)
{

}

void UKeyManager::Tick(float fDeltaTime)
{
	this->RefreshKeyState();


}

void UKeyManager::RefreshKeyState()
{
	for (int i = 0; i <= VK_F24; i++)
	{
		m_KeyStates[i] = GetAsyncKeyState(i);
	}
}

void UKeyManager::Initialize()
{
	m_KeyStates.reserve(VK_F24 + 1);
	for (int i = 0; i <= VK_F24; i++)
	{
		m_KeyStates.push_back(0);
	}
}

UKeyManager::UKeyManager()
	:
	m_KeyStates{}
{
}
