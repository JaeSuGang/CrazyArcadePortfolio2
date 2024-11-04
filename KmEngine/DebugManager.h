#pragma once
#include "stdafx.h"
#include "EngineSubsystem.h"

class UDebugManager : public UEngineSubsystem
{
public:
	void ShowFPS(HDC hBackBuffer, int nIndex, float* fFPSVariable);
	void EnableFPSCounter();
	void Tick(float fDeltaTime);

public:
	void Initialize();
	UDebugManager();

public:
	int m_nDebugMessageCount;
};

