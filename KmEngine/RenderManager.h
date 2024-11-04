#pragma once
#include "EngineSubsystem.h"
#include "KmBase/Vector.h"

class URenderManager : public UEngineSubsystem
{
	friend class UEngine;

public:
	void AddCustomRenderEvent(std::function<void()> RenderEvent);
	void ClearCustomRenderEvents();
	HWND GetGameWindowHandle();
	HDC GetGameWindowDCHandle();
	HDC GetBackBufferHandle();
	void SetWindowSize(FVector2D Size);
	static LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	void Tick();
	void Initialize(const char* lpszTitle, FVector2D WindowSize);

public:
	void Release();
	URenderManager();
	~URenderManager();

private:
	vector<std::function<void()>> m_CustomRenderEvents;
	FVector2D m_WindowSize;
	HWND m_hGameWindow;
	HDC m_hGameWindowDC;
	HDC m_hBackBufferDC;
};

