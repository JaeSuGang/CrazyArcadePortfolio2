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

public:
	static void RenderComponents(const vector<URenderComponent*>& ComponentsToRender, const HDC hMemoryDCToRender, const FVector2D ScreenSize);
	static void TrasparentBitBlt(HDC hDest, HDC hSource, FVector2D ImagePosition, FVector2D ImageSize);
	static void SortRender(vector<URenderComponent*>& RenderComponents);
	static void AddRender(vector<URenderComponent*>& RenderComponents, URenderComponent* ComponentToAdd);
	static void RemoveRender(vector<URenderComponent*>& RenderComponents, URenderComponent* ComponentToRemove);

	vector<URenderComponent*> m_ComponentsToRenderFirst;
	vector<URenderComponent*> m_ComponentsToRenderSecond;
	vector<URenderComponent*> m_ComponentsToRenderThird;
	vector<URenderComponent*> m_ComponentsToRenderFourth;

private:
	vector<URenderComponent*> m_ComponentsToRender;
	vector<std::function<void()>> m_CustomRenderEvents;
	FVector2D m_WindowSize;
	RECT m_RectToRender;
	FVector2D m_CameraPosition;
	FVector2D m_CameraRange;
	HWND m_hGameWindow;
	HDC m_hGameWindowDC;
	HDC m_hBackBufferDC;
};

