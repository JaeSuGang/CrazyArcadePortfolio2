#include "stdafx.h"
#include "TimeManager.h"

float UTimeManager::ResetDeltaTime()
{
	LARGE_INTEGER CurrentCounter{};
	QueryPerformanceCounter(&CurrentCounter);

	LONGLONG dCounterDifference = CurrentCounter.QuadPart - m_LastPerformanceCounter.QuadPart;

	float fDeltaTime = (float)dCounterDifference / (float)m_PerformanceFrequency.QuadPart;

	m_LastPerformanceCounter = CurrentCounter;

	return fDeltaTime;
}

float UTimeManager::GetDeltaTime()
{
	LARGE_INTEGER CurrentCounter{};
	QueryPerformanceCounter(&CurrentCounter);

	LONGLONG dCounterDifference = CurrentCounter.QuadPart - m_LastPerformanceCounter.QuadPart;

	float fDeltaTime = (float)dCounterDifference / (float)m_PerformanceFrequency.QuadPart;

	return fDeltaTime;
}

void UTimeManager::Initialize()
{
	QueryPerformanceFrequency(&m_PerformanceFrequency);
	QueryPerformanceCounter(&m_LastPerformanceCounter);
}

UTimeManager::UTimeManager()
	:
	m_LastPerformanceCounter{},
	m_PerformanceFrequency{}
{
}
