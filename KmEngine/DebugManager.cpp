#include "stdafx.h"
#include "Engine.h"
#include "DebugManager.h"
#include "RenderManager.h"
#include "TimeManager.h"

void UDebugManager::ShowFPS(HDC hBackBuffer, int nIndex, float* fFPSVariable)
{
	string strToShow = "FPS : " + std::to_string((int)*fFPSVariable);
	TextOutA(hBackBuffer, 5, 5 + nIndex * 30, strToShow.data(), (int)strToShow.size());
}

void UDebugManager::EnableFPSCounter()
{
	URenderManager* RenderManager = GEngine->GetEngineSubsystem<URenderManager>();
	UTimeManager* TimeManager = GEngine->GetEngineSubsystem<UTimeManager>();

	std::function<void()> Event = std::bind(&UDebugManager::ShowFPS, this, RenderManager->GetBackBufferHandle(), m_nDebugMessageCount, &TimeManager->m_fCurrentFPS);
	RenderManager->AddCustomRenderEvent(Event);
	m_nDebugMessageCount++;
}

void UDebugManager::Tick(float fDeltaTime)
{

}

void UDebugManager::Initialize()
{
	EnableFPSCounter();
}

UDebugManager::UDebugManager()
	:
	m_nDebugMessageCount{}
{
}
