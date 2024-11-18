#include "stdafx.h"
#include "Engine.h"
#include "DebugManager.h"
#include "RenderManager.h"
#include "TimeManager.h"

void UDebugManager::ShowCursorPos(HDC hBackBuffer, HWND hWindow, int nIndex)
{
	POINT CursorPos;
	GetCursorPos(&CursorPos);
	ScreenToClient(hWindow, &CursorPos);
	string strToShow = "Mouse : " + std::to_string((int)CursorPos.x) + ", " + std::to_string((int)CursorPos.y);
	TextOutA(hBackBuffer, 5, 5 + nIndex * 30, strToShow.data(), (int)strToShow.size());
}

void UDebugManager::ShowFPS(HDC hBackBuffer, int nIndex, float* fFPSVariable)
{
	string strToShow = "FPS : " + std::to_string((int)*fFPSVariable);
	TextOutA(hBackBuffer, 5, 5 + nIndex * 30, strToShow.data(), (int)strToShow.size());
}

void UDebugManager::EnableDebugMode()
{
	URenderManager* RenderManager = GEngine->GetEngineSubsystem<URenderManager>();
	UTimeManager* TimeManager = GEngine->GetEngineSubsystem<UTimeManager>();

	std::function<void()> Event = std::bind(&UDebugManager::ShowFPS, this, RenderManager->GetBackBufferHandle(), m_nDebugMessageCount, &TimeManager->m_fCurrentFPS);
	m_nDebugMessageCount++;
	std::function<void()> Event2 = std::bind(&UDebugManager::ShowCursorPos, this, RenderManager->GetBackBufferHandle(), RenderManager->GetGameWindowHandle(), m_nDebugMessageCount);
	m_nDebugMessageCount++;

	RenderManager->AddCustomRenderEvent(Event);
	RenderManager->AddCustomRenderEvent(Event2);
}

void UDebugManager::Tick(float fDeltaTime)
{

}

void UDebugManager::Initialize()
{
	EnableDebugMode();
}

UDebugManager::UDebugManager()
	:
	m_nDebugMessageCount{}
{
}
