#pragma once
#include "stdafx.h"
#include "EngineSubsystem.h"

class UDebugManager : public UEngineSubsystem
{
public:
	void Tick(float fDeltaTime);
	void AddDebugText(string strText);

public:
	void Initialize(HDC hWindowDC);
	UDebugManager();

public:
	vector<string> m_DebugText;
	HDC m_hWindowDC;
};

