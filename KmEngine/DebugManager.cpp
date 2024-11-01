#include "stdafx.h"
#include "DebugManager.h"

void UDebugManager::Tick(float fDeltaTime)
{
	AddDebugText("FPS : " + std::to_string((int)(1/fDeltaTime)));

	for (int i = 0; i < m_DebugText.size(); i++)
	{
		TextOutA(m_hWindowDC, 0, i * 30, m_DebugText[i].data(), m_DebugText[i].length());
	}

	m_DebugText.clear();
}

void UDebugManager::AddDebugText(string strText)
{
	m_DebugText.push_back(strText);
}

void UDebugManager::Initialize(HDC hWindowDC)
{
	m_DebugText.reserve(100);
	m_hWindowDC = hWindowDC;
}

UDebugManager::UDebugManager()
	:
	m_DebugText{},
	m_hWindowDC{}
{
}
