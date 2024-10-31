#include "stdafx.h"
#include "Engine.h"
#include "RenderManager.h"
#include "GameInstance.h"
#include "Actor.h"
#include "Level.h"
#include "RenderComponent.h"

HWND URenderManager::GetGameWindowHandle()
{
	return m_hGameWindow;
}

void URenderManager::SetWindowSize(FVector2D Size)
{
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
	// �Ϲ� ������ ó��
	MSG msg{};
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// ���� bitblt
	ULevel* ActiveLevel = GEngine->GetGameInstance()->GetActiveLevel();
	auto ActorIter = ActiveLevel->m_Actors.begin();
	while (ActorIter != ActiveLevel->m_Actors.end())
	{
		AActor* Actor = *ActorIter;
		FVector2D ActorPos = Actor->GetPositionVector2D();
		URenderComponent* RenderComponent = Actor->GetComponentByClass<URenderComponent>();
		if (UImage* StaticImage = RenderComponent->GetStaticImage())
		{
			int nWidth = StaticImage->m_BitmapInfo.bmWidth;
			int nHeight = StaticImage->m_BitmapInfo.bmHeight;

			GdiTransparentBlt(m_hBackBufferDC, ActorPos.X, ActorPos.Y,
				nWidth, nHeight, StaticImage->getDC(), 0, 0, nWidth, nHeight, RGB(255, 0, 255));
		}

		++ActorIter;
	}

	// ����� bitblt
	
}

void URenderManager::Initialize(const char* lpszTitle)
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
		SHOW_ERROR("MakeWindow()�� RegisterClassExA()�� false�� ������");
	}

	m_hGameWindow = CreateWindowA(lpszTitle, lpszTitle, WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 0, CW_USEDEFAULT, 0, nullptr, nullptr, nullptr, nullptr);

	if (!m_hGameWindow)
	{
		SHOW_ERROR("MakeWindow()�� CreateWindowA()�� false�� ������");
	}

	ShowWindow(m_hGameWindow, SW_SHOW);
	UpdateWindow(m_hGameWindow);
}

URenderManager::URenderManager()
	:
	m_hGameWindow{},
	m_hBackBufferDC{},
	m_hGameWindowDC{}
{
}
