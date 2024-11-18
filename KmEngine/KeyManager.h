#pragma once
#include "stdafx.h"
#include "EngineSubsystem.h"

class UKeyManager : public UEngineSubsystem
{
	friend class UEngine;

public:
	enum class EKeyState : unsigned short
	{
		None,
		Triggered,
		KeyDown,
		KeyUp
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
	bool GetKeyTriggered(int VirtualKey);
	void BindKey(int VirtualKey, EKeyState KeyState, std::function<void()> Action);
	void ClearBindKey();

private:
	void Tick(float fDeltaTime);
	void RefreshKeyStateAndBroadcast();

private:
	void Initialize();
	UKeyManager();

private:
	vector<FKeyEvent> m_KeyEvents;
	vector<unsigned short> m_KeyStates;
};

