#include "stdafx.h"
#include "Engine.h"
#include "RenderManager.h"
#include "GameInstance.h"
#include "Actor.h"
#include "Level.h"
#include "RenderComponent.h"

void URenderManager::CleanLayerDC(HDC hDC, FVector2D Size)
{
	Rectangle(hDC, 0, 0, (int)Size.X, (int)Size.Y);
}

void URenderManager::CopyBitBltDC(HDC dest, HDC source, FVector2D ScreenSize)
{
	TransparentBlt(dest, 0, 0, (int)ScreenSize.X, (int)ScreenSize.Y, source, 0, 0, (int)ScreenSize.X, (int)ScreenSize.Y, RGB(255, 0, 255));
	// BitBlt(dest, 0, 0, (int)ScreenSize.X, (int)ScreenSize.Y, source, 0, 0, SRCCOPY);
}

void URenderManager::RenderComponents(const vector<URenderComponent*>& ComponentsToRender, const HDC hMemoryDCToRender, const FVector2D ScreenSize)
{
	for (const URenderComponent* ComponentToRender : ComponentsToRender)
	{
		const AActor* Owner = ComponentToRender->GetOwner();
		if (const UImage* Image = ComponentToRender->GetStaticImage())
		{
			FVector2D ImageSize = { (float)Image->m_BitmapInfo.bmWidth , (float)Image->m_BitmapInfo.bmHeight };
			FVector2D ImagePosition = Owner->GetPosition() - ImageSize / 2;
			ImagePosition += ComponentToRender->GetStaticImageOffset();

			URenderManager::TrasparentBitBlt(hMemoryDCToRender, Image->getDC(), ImagePosition, ImageSize);
		}
	}
}

void URenderManager::RenderShadowComponents(const vector<URenderComponent*>& ComponentsToRender, const HDC hMemoryDCToRender, const FVector2D ScreenSize)
{
	for (const URenderComponent* ComponentToRender : ComponentsToRender)
	{
		const AActor* Owner = ComponentToRender->GetOwner();
		if (const UImage* Image = ComponentToRender->GetShadowImage())
		{
			FVector2D ImageSize = { (float)Image->m_BitmapInfo.bmWidth , (float)Image->m_BitmapInfo.bmHeight };
			FVector2D ImagePosition = Owner->GetPosition() - ImageSize / 2;
			ImagePosition += ComponentToRender->GetShadowImageOffset();

			URenderManager::TrasparentBitBlt(hMemoryDCToRender, Image->getDC(), ImagePosition, ImageSize);
		}
	}
}

void URenderManager::TrasparentBitBlt(HDC hDest, HDC hSource, FVector2D ImagePosition, FVector2D ImageSize)
{
	TransparentBlt(
		hDest,
		(int)ImagePosition.X, (int)ImagePosition.Y,
		(int)ImageSize.X, (int)ImageSize.Y,
		hSource,
		0, 0,
		(int)ImageSize.X, (int)ImageSize.Y,
		RGB(255, 0, 255));
}

void URenderManager::SortRender(vector<URenderComponent*>& RenderComponents)
{
	auto lambda = [](URenderComponent* a, URenderComponent* b) { return a->GetRenderPriority() < b->GetRenderPriority(); };
	std::sort(RenderComponents.begin(), RenderComponents.end(), lambda);
}

void URenderManager::AddRender(URenderComponent* ComponentToAdd, vector<URenderComponent*>& RenderComponents)
{
	RenderComponents.push_back(ComponentToAdd);
}

void URenderManager::RemoveRender(URenderComponent* ComponentToRemove, vector<URenderComponent*>& RenderComponents)
{
	for (int i = 0; i < RenderComponents.size(); i++)
	{
		if (RenderComponents[i] != ComponentToRemove)
			continue;

		RenderComponents[i] = RenderComponents[RenderComponents.size() - 1];
		RenderComponents.pop_back();
		break;
	}
}

void URenderManager::AddCustomRenderEvent(std::function<void()> RenderEvent)
{
	m_CustomRenderEvents.push_back(RenderEvent);
}

void URenderManager::ClearCustomRenderEvents()
{
	m_CustomRenderEvents.clear();
}

HWND URenderManager::GetGameWindowHandle()
{
	return m_hGameWindow;
}

HDC URenderManager::GetGameWindowDCHandle()
{
	return m_hGameWindowDC;
}

HDC URenderManager::GetBackBufferHandle()
{
	return m_hBackBufferDC;
}

void URenderManager::SetWindowSize(FVector2D Size)
{
	m_WindowSize = Size;
	SetWindowPos(m_hGameWindow, 0, 0, 0, (int)Size.X, (int)Size.Y, SWP_NOMOVE);
}

LRESULT URenderManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_QUIT:
	case WM_CLOSE:
	case WM_DESTROY:
		GEngine->TerminateEngine();
		[[fallthrough]];

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void URenderManager::Tick()
{
	// 일반 윈도우 처리
	MSG msg{};
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// 백버퍼 청소
	Rectangle(m_hBackBufferDC, -1, -1, (int)m_WindowSize.X + 2, (int)m_WindowSize.Y + 2);

	UResourceManager* ResourceManager = GEngine->GetEngineSubsystem<UResourceManager>();
	UImage* Image = ResourceManager->GetImage("Resources\\Bazzi\\DownIdle.bmp");
	

	//BitBlt(m_hBackBufferDC, 0, 0, 66, 84, Image->getDC(), 0, 0, SRCCOPY);
	TransparentBlt(m_hBackBufferDC, 0, 0, 66, 84, Image->getDC(), 0, 0, 66, 84, RGB(255, 0, 255));

	// 새 렌더 코드
	// 1번째 레이어
	URenderManager::CleanLayerDC(m_LayerDC[0], m_WindowSize);
	URenderManager::SortRender(m_ComponentsToRenderFirst);
	URenderManager::RenderComponents(m_ComponentsToRenderFirst, m_hBackBufferDC, m_WindowSize);
	//URenderManager::CopyBitBltDC(m_hBackBufferDC, m_LayerDC[0], m_WindowSize);

	//// 2번째 레이어
	//HDC hTemporaryDC2 = CreateCompatibleDC(m_hGameWindowDC);
	//HBITMAP hTemporaryBitmap2 = CreateCompatibleBitmap(hTemporaryDC2, (int)m_WindowSize.X, (int)m_WindowSize.Y);
	//SelectObject(hTemporaryDC2, hTemporaryBitmap2);
	//URenderManager::InitializeTransparentDC(hTemporaryDC2, m_WindowSize);
	//URenderManager::SortRender(m_ComponentsToRenderSecond);
	//URenderManager::RenderShadowComponents(m_ComponentsToRenderSecond, hTemporaryDC2, m_WindowSize);
	//URenderManager::CopyBitBltDC(m_hBackBufferDC, hTemporaryDC2, m_WindowSize);
	//DeleteObject(hTemporaryBitmap2);
	//DeleteDC(hTemporaryDC2);

	//// 3번째 레이어
	//HDC hTemporaryDC3 = CreateCompatibleDC(m_hGameWindowDC);
	//HBITMAP hTemporaryBitmap3 = CreateCompatibleBitmap(hTemporaryDC3, (int)m_WindowSize.X, (int)m_WindowSize.Y);
	//SelectObject(hTemporaryDC3, hTemporaryBitmap3);
	//URenderManager::InitializeTransparentDC(hTemporaryDC3, m_WindowSize);
	//URenderManager::SortRender(m_ComponentsToRenderThird);
	//URenderManager::RenderComponents(m_ComponentsToRenderThird, hTemporaryDC3, m_WindowSize);
	//URenderManager::CopyBitBltDC(m_hBackBufferDC, hTemporaryDC3, m_WindowSize);
	//DeleteObject(hTemporaryBitmap3);
	//DeleteDC(hTemporaryDC3);

	//// 4번째 레이어
	//HDC hTemporaryDC4 = CreateCompatibleDC(m_hGameWindowDC);
	//HBITMAP hTemporaryBitmap4 = CreateCompatibleBitmap(hTemporaryDC4, (int)m_WindowSize.X, (int)m_WindowSize.Y);
	//SelectObject(hTemporaryDC4, hTemporaryBitmap4);
	//URenderManager::InitializeTransparentDC(hTemporaryDC4, m_WindowSize);
	//URenderManager::SortRender(m_ComponentsToRenderFourth);
	//URenderManager::RenderComponents(m_ComponentsToRenderFourth, hTemporaryDC4, m_WindowSize);
	//URenderManager::CopyBitBltDC(m_hBackBufferDC, hTemporaryDC4, m_WindowSize);
	//DeleteObject(hTemporaryBitmap4);
	//DeleteDC(hTemporaryDC4);


	// 커스텀 렌더링 이벤트
	for (int i = 0; i < m_CustomRenderEvents.size(); i++)
	{
		m_CustomRenderEvents[i]();
	}
	// Obsolete 기존 코드 끝

	// 백버퍼 bitblt
	bool a = BitBlt(m_hGameWindowDC,
		0, 0,
		(int)m_WindowSize.X, (int)m_WindowSize.Y,
		m_hBackBufferDC,
		0, 0,
		SRCCOPY);

}

void URenderManager::Initialize(const char* lpszTitle, FVector2D WindowSize)
{
	WNDCLASSEXA wcex{};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = URenderManager::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = nullptr;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = lpszTitle;
    wcex.hIconSm = nullptr;

	if (!RegisterClassExA(&wcex))
	{
		SHOW_ERROR("MakeWindow()의 RegisterClassExA()가 false를 리턴함");
	}

	m_hGameWindow = CreateWindowA(lpszTitle, lpszTitle, WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 0, CW_USEDEFAULT, 0, nullptr, nullptr, nullptr, nullptr);

	if (!m_hGameWindow)
	{
		SHOW_ERROR("MakeWindow()의 CreateWindowA()가 false를 리턴함");
	}

	m_hGameWindowDC = GetDC(m_hGameWindow);
	m_hBackBufferDC = CreateCompatibleDC(m_hGameWindowDC);
	HBITMAP hBackBufferBitmap = CreateCompatibleBitmap(m_hGameWindowDC, (int)WindowSize.X, (int)WindowSize.Y);
	SelectObject(m_hBackBufferDC, hBackBufferBitmap);

	m_hMagentaPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
	m_hMagentaBrush = CreateSolidBrush(RGB(255, 0, 255));
	for (size_t i = 0; i < 4; i++)
	{
		HDC LayerDC = CreateCompatibleDC(m_hBackBufferDC);
		HBITMAP hLayerBitmap = CreateCompatibleBitmap(m_hBackBufferDC, (int)m_WindowSize.X, (int)m_WindowSize.Y);
		SelectObject(LayerDC, hLayerBitmap);
		SelectObject(LayerDC, m_hMagentaPen);
		SelectObject(LayerDC, m_hMagentaBrush);
		m_LayerDC.push_back(LayerDC);
	}


	ShowWindow(m_hGameWindow, SW_SHOW);
	UpdateWindow(m_hGameWindow);

}

void URenderManager::Release()
{
	ReleaseDC(m_hGameWindow, m_hGameWindowDC);
	DeleteDC(m_hBackBufferDC);

	for (HDC hDC : m_LayerDC)
	{
		DeleteDC(hDC);
	}
}

URenderManager::URenderManager()
	:
	m_hGameWindow{},
	m_hBackBufferDC{},
	m_hGameWindowDC{},
	m_WindowSize{},
	m_CustomRenderEvents{}
{
}

URenderManager::~URenderManager()
{
	this->Release();
}
