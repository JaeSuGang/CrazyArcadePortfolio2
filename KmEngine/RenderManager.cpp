#include "stdafx.h"
#include "Engine.h"
#include "RenderManager.h"
#include "GameInstance.h"
#include "Actor.h"
#include "Level.h"

HWND URenderManager::GetGameWindowHandle()
{
	return m_hWnd;
}

void URenderManager::SetWindowSize(FVector2D Size)
{
	SetWindowPos(m_hWnd, 0, 0, 0, (int)Size.X, (int)Size.Y, SWP_NOMOVE);
}

LRESULT URenderManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_QUIT:
	case WM_CLOSE:
	case WM_DESTROY:
		GEngine->TerminateEngine();

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void URenderManager::Tick()
{
	MSG msg{};

	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	ULevel* ActiveLevel = GEngine->GetGameInstance()->GetActiveLevel();
	auto ActorIter = ActiveLevel->m_Actors.begin();
	while (ActorIter != ActiveLevel->m_Actors.end())
	{
		FVector2D Position2D = (*ActorIter)->GetPositionVector2D();
		// 할것 렌더링 실제로 하기

		++ActorIter;
	}
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
		SHOW_ERROR("MakeWindow()의 RegisterClassExA()가 false를 리턴함");
	}

	m_hWnd = CreateWindowA(lpszTitle, lpszTitle, WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 0, CW_USEDEFAULT, 0, nullptr, nullptr, nullptr, nullptr);

	if (!m_hWnd)
	{
		SHOW_ERROR("MakeWindow()의 CreateWindowA()가 false를 리턴함");
	}

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
}

URenderManager::URenderManager()
	:
	m_hWnd{}
{
}
