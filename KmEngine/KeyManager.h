#pragma once
#include "stdafx.h"
#include "EngineSubsystem.h"

class UKeyManager : public UEngineSubsystem
{
	friend class UEngine;

public:
	bool GetKeyDown(int VirtualKey);
	bool GetKeyPress(int VirtualKey);
	void BindAction(int VirtualKey, std::function<void()> Action);
	void ClearBindAction();

private:
	void Tick(float fDeltaTime);
	void RefreshKeyState();

private:
	void Initialize();
	UKeyManager();

private:
	vector<SHORT> m_KeyStates;
};

