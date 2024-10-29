#include "stdafx.h"
#include "KeyManager.h"

bool UKeyManager::GetKeyUp(int VirtualKey)
{
	if (m_KeyStates[VirtualKey] == EKeyState::KeyUp)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UKeyManager::GetKeyDown(int VirtualKey)
{
	if (m_KeyStates[VirtualKey] == EKeyState::KeyDown)
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
	if (m_KeyStates[VirtualKey] == EKeyState::KeyPress)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void UKeyManager::BindKey(int VirtualKey, EKeyState KeyState, std::function<void()> Event)
{
	FKeyEvent KeyEvent{ VirtualKey, KeyState, Event};
	m_KeyEvents.push_back(KeyEvent);
}

void UKeyManager::ClearBindKey()
{
	m_KeyEvents.clear();
}

void UKeyManager::Tick(float fDeltaTime)
{
	this->RefreshKeyState();
	this->BroadcastKeyEvent();
}

void UKeyManager::RefreshKeyState()
{
	for (int i = 0; i <= VK_F24; i++)
	{
		m_KeyStates[i] = static_cast<EKeyState>(GetAsyncKeyState(i));
	}
}

void UKeyManager::BroadcastKeyEvent()
{
	for (int i = 0; i < m_KeyEvents.size(); i++)
	{
		FKeyEvent& KeyEvent = m_KeyEvents[i];
		if (m_KeyStates[KeyEvent.VirtualKey] == KeyEvent.KeyState)
		{
			KeyEvent.Event();
		}
	}
}

void UKeyManager::Initialize()
{
	m_KeyEvents.reserve(200);

	m_KeyStates.reserve(VK_F24 + 1);
	for (int i = 0; i <= VK_F24; i++)
	{
		m_KeyStates.push_back(EKeyState::None);
	}
}

UKeyManager::UKeyManager()
	:
	m_KeyStates{},
	m_KeyEvents{}
{
}
