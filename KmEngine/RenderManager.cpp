#include "stdafx.h"
#include "Engine.h"
#include "RenderManager.h"
#include "GameInstance.h"
#include "Actor.h"
#include "Level.h"
#include "RenderComponent.h"

void URenderManager::RemoveRender(URenderComponent* RenderComponent)
{
	for (int i = 0; i < m_ComponentsToRender.size(); i++)
	{
		if (m_ComponentsToRender[i] == RenderComponent)
		{
			m_ComponentsToRender[i] = m_ComponentsToRender[m_ComponentsToRender.size()-1];
			m_ComponentsToRender.pop_back();
			break;
		}
	}
}

void URenderManager::AddRender(URenderComponent* RenderComponent)
{
	m_ComponentsToRender.push_back(RenderComponent);
}

void URenderManager::SortRender()
{
	auto lambda = [](URenderComponent* a, URenderComponent* b) { return a->m_fRenderPriority < b->m_fRenderPriority; };
	std::sort(m_ComponentsToRender.begin(), m_ComponentsToRender.end(), lambda);
}

void URenderManager::ClearRender()
{
	m_ComponentsToRender.clear();
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

	this->SortRender();

	for (int i = 0; i < m_ComponentsToRender.size(); i++)
	{
		URenderComponent* RenderComponent = m_ComponentsToRender[i];
		AActor* Owner = RenderComponent->GetOwner();
		FVector2D ActorPos = Owner->GetPosition();
		if (UImage* StaticImage = RenderComponent->GetStaticImage())
		{
			if (UImage* ShadowImage = RenderComponent->GetShadowImage())
			{
				FVector2D ImageSize{ (float)ShadowImage->m_BitmapInfo.bmWidth , (float)ShadowImage->m_BitmapInfo.bmHeight };
				FVector2D ImagePositionVector = ActorPos - ImageSize / 2;
				ImagePositionVector += RenderComponent->GetShadowImageOffset();

				GdiTransparentBlt(m_hBackBufferDC,
					(int)ImagePositionVector.X,
					(int)ImagePositionVector.Y,
					(int)ImageSize.X,
					(int)ImageSize.Y,
					ShadowImage->getDC(),
					0,
					0,
					(int)ImageSize.X,
					(int)ImageSize.Y,
					RGB(255, 0, 255));
			}
			FVector2D ImageSize{ (float)StaticImage->m_BitmapInfo.bmWidth , (float)StaticImage->m_BitmapInfo.bmHeight };
			FVector2D ImagePositionVector = ActorPos - ImageSize / 2;
			ImagePositionVector += RenderComponent->GetStaticImageOffset();

			GdiTransparentBlt(m_hBackBufferDC,
				(int)ImagePositionVector.X,
				(int)ImagePositionVector.Y,
				(int)ImageSize.X,
				(int)ImageSize.Y,
				StaticImage->getDC(),
				0,
				0,
				(int)ImageSize.X,
				(int)ImageSize.Y,
				RGB(255, 0, 255));
		}

	}

	// 커스텀 렌더링 이벤트
	for (int i = 0; i < m_CustomRenderEvents.size(); i++)
	{
		m_CustomRenderEvents[i]();
	}

	// 백버퍼 bitblt
	bool a = BitBlt(m_hGameWindowDC,
		(int)(m_RectToRender.left),
		(int)(m_RectToRender.top),
		(int)(m_RectToRender.right - m_RectToRender.left),
		(int)(m_RectToRender.bottom - m_RectToRender.top),
		m_hBackBufferDC,
		(int)(m_RectToRender.left),
		(int)(m_RectToRender.top),
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


	ShowWindow(m_hGameWindow, SW_SHOW);
	UpdateWindow(m_hGameWindow);

	m_RectToRender = {0, 0, (long)WindowSize.X, (long)WindowSize.Y };
}

void URenderManager::Release()
{
	ReleaseDC(m_hGameWindow, m_hGameWindowDC);
	DeleteDC(m_hBackBufferDC);
}

URenderManager::URenderManager()
	:
	m_hGameWindow{},
	m_hBackBufferDC{},
	m_hGameWindowDC{},
	m_WindowSize{},
	m_CustomRenderEvents{},
	m_RectToRender{}
{
}

URenderManager::~URenderManager()
{
	this->Release();
}
