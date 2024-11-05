#include "stdafx.h"
#include "KeyManager.h"

bool UKeyManager::GetKeyUp(int VirtualKey)
{
	if (m_KeyStates[VirtualKey] == 0x0001)
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
	if (m_KeyStates[VirtualKey] == 0x8001)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UKeyManager::GetKeyTriggered(int VirtualKey)
{
	if (m_KeyStates[VirtualKey] == 0x8001 || m_KeyStates[VirtualKey] == 0x8000)
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
	this->RefreshKeyStateAndBroadcast();
	//this->BroadcastKeyEvent();
}

void UKeyManager::RefreshKeyStateAndBroadcast()
{
	for (int i = 0; i <= VK_F24; i++)
	{
		unsigned short CurrentState = static_cast<unsigned short>(GetAsyncKeyState(i));

		if (CurrentState != 0x0000 && m_KeyStates[i] == 0x0000)
		{
			for (int j = 0; j < m_KeyEvents.size(); j++)
			{
				FKeyEvent& KeyEvent = m_KeyEvents[j];
				if (KeyEvent.VirtualKey == i && KeyEvent.KeyState == EKeyState::KeyDown)
				{
					KeyEvent.Event();
				}
			}
		}

		if (m_KeyStates[i] != 0x0000 && CurrentState != 0x0000)
		{
			for (int j = 0; j < m_KeyEvents.size(); j++)
			{
				FKeyEvent& KeyEvent = m_KeyEvents[j];
				if (KeyEvent.VirtualKey == i && KeyEvent.KeyState == EKeyState::Triggered)
				{
					KeyEvent.Event();
				}
			}
		}

		if (m_KeyStates[i] != 0x0000 && CurrentState == 0x0000)
		{
			for (int j = 0; j < m_KeyEvents.size(); j++)
			{
				FKeyEvent& KeyEvent = m_KeyEvents[j];
				if (KeyEvent.VirtualKey == i && KeyEvent.KeyState == EKeyState::KeyUp)
				{
					KeyEvent.Event();
				}
			}
		}

		m_KeyStates[i] = CurrentState;
	}
}

//void UKeyManager::BroadcastKeyEvent()
//{
//	for (int i = 0; i < m_KeyEvents.size(); i++)
//	{
//		FKeyEvent& KeyEvent = m_KeyEvents[i];
//
//		switch (KeyEvent.KeyState)
//		{
//		case EKeyState::Triggered:
//			if (m_KeyStates[KeyEvent.VirtualKey] == 0x8000 || m_KeyStates[KeyEvent.VirtualKey] == 0x8001)
//			{
//				KeyEvent.Event();
//			}
//			break;
//
//		case EKeyState::KeyDown:
//			if (m_KeyStates[KeyEvent.VirtualKey] == 0x8001)
//			{
//				KeyEvent.Event();
//			}
//			break;
//
//		case EKeyState::KeyUp:
//			if (m_KeyStates[KeyEvent.VirtualKey] == 0x0001)
//			{
//				KeyEvent.Event();
//			}
//			break;
//
//		default:
//			break;
//		}
//	}
//}

void UKeyManager::Initialize()
{
	m_KeyEvents.reserve(200);

	m_KeyStates.reserve(VK_F24 + 1);
	for (int i = 0; i <= VK_F24; i++)
	{
		m_KeyStates.push_back(0);
	}
}

UKeyManager::UKeyManager()
	:
	m_KeyStates{},
	m_KeyEvents{}
{
}
