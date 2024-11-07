#pragma once
#include "EngineSubsystem.h"
#include "KmBase/Vector.h"
#include <thread>

class URenderComponent;

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

private:
	void Tick();
	void Initialize(const char* lpszTitle, FVector2D WindowSize);
	static LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	void Release();
	URenderManager();
	~URenderManager();
	
private:

public:
	static void InitializeTransparentDC(HDC hDC, FVector2D Size);
	static void CopyBitBltDC(HDC dest, HDC source, FVector2D ScreenSize);
	static void RenderComponents(const vector<URenderComponent*>& ComponentsToRender, const HDC hMemoryDCToRender, const FVector2D ScreenSize);
	static void RenderShadowComponents(const vector<URenderComponent*>& ComponentsToRender, const HDC hMemoryDCToRender, const FVector2D ScreenSize);
	static void TrasparentBitBlt(HDC hDest, HDC hSource, FVector2D ImagePosition, FVector2D ImageSize);
	static void SortRender(vector<URenderComponent*>& RenderComponents);
	static void AddRender(URenderComponent* ComponentToAdd, vector<URenderComponent*>& RenderComponents);
	static void RemoveRender(URenderComponent* ComponentToRemove, vector<URenderComponent*>& RenderComponents);

	void RenderF();
	void RenderS();
	void RenderT();
	void RenderFo();

	std::atomic<bool> IsRender[4];

	vector<URenderComponent*> m_ComponentsToRenderFirst;
	vector<URenderComponent*> m_ComponentsToRenderSecond;
	vector<URenderComponent*> m_ComponentsToRenderThird;
	vector<URenderComponent*> m_ComponentsToRenderFourth;

private:
	vector<std::function<void()>> m_CustomRenderEvents;
	FVector2D m_WindowSize;
	HWND m_hGameWindow;
	HDC m_hGameWindowDC;
	HDC m_hBackBufferDC;

	// std::thread Threads[4];


	HDC m_hLayer[4];
};

