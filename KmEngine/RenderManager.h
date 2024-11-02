#pragma once
#include "EngineSubsystem.h"
#include "KmBase/Vector.h"

class URenderManager : public UEngineSubsystem
{
	friend class UEngine;

public:
	HWND GetGameWindowHandle();
	HDC GetGameWindowDCHandle();
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
	FVector2D m_WindowSize;
	HWND m_hGameWindow;
	HDC m_hGameWindowDC;
	HDC m_hBackBufferDC;
};

