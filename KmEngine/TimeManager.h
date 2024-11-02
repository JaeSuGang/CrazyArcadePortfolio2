#pragma once
#include "EngineSubsystem.h"

class UTimeManager : public UEngineSubsystem
{
	friend class UEngine;

public:
	void AssignDeltaTime();
	void ResetStartCounter();
	void SetLastCounter();
	float GetDeltaTime() const;

private:
	void Initialize();
	UTimeManager();

private:
	LARGE_INTEGER m_StartPerformanceCounter;
	LARGE_INTEGER m_LastPerformanceCounter;
	LARGE_INTEGER m_PerformanceFrequency;
	float m_fDeltaTime;
};

