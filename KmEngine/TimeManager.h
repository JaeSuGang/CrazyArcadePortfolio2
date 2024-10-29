#pragma once
#include "EngineSubsystem.h"

class UTimeManager : public UEngineSubsystem
{
	friend class UEngine;

public:
	float ResetDeltaTime();
	float GetDeltaTime();

private:
	void Initialize();
	UTimeManager();

private:
	LARGE_INTEGER m_LastPerformanceCounter;
	LARGE_INTEGER m_PerformanceFrequency;
};

