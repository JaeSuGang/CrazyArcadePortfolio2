#include "stdafx.h"
#include "TimeManager.h"

void UTimeManager::AssignDeltaTime()
{
	LONGLONG dCounterDifference = m_LastPerformanceCounter.QuadPart - m_StartPerformanceCounter.QuadPart;

	m_fDeltaTime = (float)dCounterDifference / (float)m_PerformanceFrequency.QuadPart;
	m_fCurrentFPS = 1 / m_fDeltaTime;
}

void UTimeManager::SetLastCounter()
{
	QueryPerformanceCounter(&m_LastPerformanceCounter);
}

void UTimeManager::ResetStartCounter()
{
	QueryPerformanceCounter(&m_StartPerformanceCounter);
}

float UTimeManager::GetDeltaTime() const
{
	return m_fDeltaTime;
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
