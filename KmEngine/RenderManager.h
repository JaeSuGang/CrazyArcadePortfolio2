#pragma once
#include "EngineSubsystem.h"
#include "KmBase/Vector.h"

class URenderComponent;

class URenderManager : public UEngineSubsystem
{
	friend class UEngine;

public:
	void RemoveRender(URenderComponent* RenderComponent);
	void AddRender(URenderComponent* RenderComponent);
	void ClearRender();
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
	void SortRender();

private:
	// key값에 따라 정렬, 렌더링 우선순위
	vector<URenderComponent*> m_ComponentsToRender;
	vector<std::function<void()>> m_CustomRenderEvents;
	FVector2D m_WindowSize;
	RECT m_RectToRender;
	HWND m_hGameWindow;
	HDC m_hGameWindowDC;
	HDC m_hBackBufferDC;
};

