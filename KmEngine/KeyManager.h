#pragma once
#include "stdafx.h"
#include "EngineSubsystem.h"

class UKeyManager : public UEngineSubsystem
{
	friend class UEngine;

public:
	enum class EKeyState : unsigned short
	{
		None = 0x0000,
		KeyUp = 0x0001,
		KeyDown = 0x8000,
		KeyPress = 0x8001,
	};

	struct FKeyEvent
	{
		int VirtualKey;
		EKeyState KeyState;
		std::function<void()> Event;
	};

public:
	bool GetKeyUp(int VirtualKey);
	bool GetKeyDown(int VirtualKey);
	bool GetKeyPress(int VirtualKey);
	void BindKey(int VirtualKey, EKeyState KeyState, std::function<void()> Action);
	void ClearBindKey();

private:
	void Tick(float fDeltaTime);
	void RefreshKeyState();
	void BroadcastKeyEvent();

private:
	void Initialize();
	UKeyManager();

private:
	vector<FKeyEvent> m_KeyEvents;
	vector<EKeyState> m_KeyStates;
};

