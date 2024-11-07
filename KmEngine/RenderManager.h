#pragma once
#include "EngineSubsystem.h"
#include "KmBase/Vector.h"

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
	void RenderProcess1();
	void RenderProcess2(std::thread& PutRenderProcess1);
	void RenderProcess3();
	void RenderProcess4(std::thread& PutRenderProcess3);

public:
	static void CleanLayerDC(HDC hDC, FVector2D Size);
	static void CopyBitBltDC(HDC dest, HDC source, FVector2D ScreenSize);
	static void RenderComponents(const vector<URenderComponent*>& ComponentsToRender, const HDC hMemoryDCToRender, const FVector2D ScreenSize);
	static void RenderShadowComponents(const vector<URenderComponent*>& ComponentsToRender, const HDC hMemoryDCToRender, const FVector2D ScreenSize);
	static void TrasparentBitBlt(HDC hDest, HDC hSource, FVector2D ImagePosition, FVector2D ImageSize);
	static void SortRender(vector<URenderComponent*>& RenderComponents);
	static void AddRender(URenderComponent* ComponentToAdd, vector<URenderComponent*>& RenderComponents);
	static void RemoveRender(URenderComponent* ComponentToRemove, vector<URenderComponent*>& RenderComponents);

	vector<URenderComponent*> m_ComponentsToRenderFirst;
	vector<URenderComponent*> m_ComponentsToRenderSecond;
	vector<URenderComponent*> m_ComponentsToRenderThird;
	vector<URenderComponent*> m_ComponentsToRenderFourth;

private:
	HPEN m_hMagentaPen;
	HBRUSH m_hMagentaBrush;
	vector<HDC> m_LayerDC;
	bool m_bAlreadyGeneratedFloorTiles;

	vector<std::function<void()>> m_CustomRenderEvents;
	FVector2D m_WindowSize;
	HWND m_hGameWindow;
	HDC m_hGameWindowDC;
	HDC m_hBackBufferDC;
};

