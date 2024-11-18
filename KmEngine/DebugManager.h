#pragma once
#include "stdafx.h"
#include "EngineSubsystem.h"

class UDebugManager : public UEngineSubsystem
{
public:
	void ShowCursorPos(HDC hBackBuffer, HWND hWindow, int nIndex);
	void ShowFPS(HDC hBackBuffer, int nIndex, float* fFPSVariable);
	void EnableDebugMode();
	void Tick(float fDeltaTime);

public:
	void Initialize();
	UDebugManager();

public:
	int m_nDebugMessageCount;
};

