#pragma once
#include "EngineSubsystem.h"
#include "KmBase/Vector.h"

class URenderManager : public UEngineSubsystem
{
	friend class UEngine;

public:
	HWND GetGameWindowHandle();
	void SetWindowSize(FVector2D Size);
	static LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	void Tick();
	void Initialize(const char* lpszTitle);

private:
	URenderManager();

private:
	HWND m_hGameWindow;
	HDC m_hGameWindowDC;
	HDC m_hBackBufferDC;
};

