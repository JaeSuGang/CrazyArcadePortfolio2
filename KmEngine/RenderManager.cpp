#include "stdafx.h"
#include "Engine.h"
#include "RenderManager.h"
#include "GameInstance.h"
#include "Actor.h"
#include "Level.h"
#include "RenderComponent.h"

void URenderManager::InitializeTransparentDC(HDC hDC, FVector2D Size)
{
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

	Rectangle(hDC, 0, 0, (int)Size.X, (int)Size.Y);
	SelectObject(hDC, hOldBrush);
	SelectObject(hDC, hOldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);
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

void URenderManager::RenderF()
{
	for (const URenderComponent* ComponentToRender : m_ComponentsToRenderFirst)
	{
		const AActor* Owner = ComponentToRender->GetOwner();
		if (const UImage* Image = ComponentToRender->GetStaticImage())
		{
			FVector2D ImageSize = { (float)Image->m_BitmapInfo.bmWidth , (float)Image->m_BitmapInfo.bmHeight };
			FVector2D ImagePosition = Owner->GetPosition() - ImageSize / 2;
			ImagePosition += ComponentToRender->GetStaticImageOffset();

			TransparentBlt(m_hLayer[0], ImagePosition.X, ImagePosition.Y, ImageSize.X, ImageSize.Y,
				Image->getDC(), 0, 0, ImageSize.X, ImageSize.Y, RGB(255, 0, 255));
		}
	}

	IsRender[0] = true;
}

void URenderManager::RenderS()
{

	for (const URenderComponent* ComponentToRender : m_ComponentsToRenderSecond)
	{
		const AActor* Owner = ComponentToRender->GetOwner();
		if (const UImage* Image = ComponentToRender->GetShadowImage())
		{
			FVector2D ImageSize = { (float)Image->m_BitmapInfo.bmWidth , (float)Image->m_BitmapInfo.bmHeight };
			FVector2D ImagePosition = Owner->GetPosition() - ImageSize / 2;
			ImagePosition += ComponentToRender->GetStaticImageOffset();

			TransparentBlt(m_hLayer[1], ImagePosition.X, ImagePosition.Y, ImageSize.X, ImageSize.Y,
				Image->getDC(), 0, 0, ImageSize.X, ImageSize.Y, RGB(255, 0, 255));
		}
	}

	IsRender[1] = true;
}

void URenderManager::RenderT()
{
	for (const URenderComponent* ComponentToRender : m_ComponentsToRenderThird)
	{
		const AActor* Owner = ComponentToRender->GetOwner();
		if (const UImage* Image = ComponentToRender->GetStaticImage())
		{
			FVector2D ImageSize = { (float)Image->m_BitmapInfo.bmWidth , (float)Image->m_BitmapInfo.bmHeight };
			FVector2D ImagePosition = Owner->GetPosition() - ImageSize / 2;
			ImagePosition += ComponentToRender->GetStaticImageOffset();

			TransparentBlt(m_hLayer[2], ImagePosition.X, ImagePosition.Y, ImageSize.X, ImageSize.Y,
				Image->getDC(), 0, 0, ImageSize.X, ImageSize.Y, RGB(255, 0, 255));
		}
	}

	IsRender[2] = true;

}

void URenderManager::RenderFo()
{


	for (const URenderComponent* ComponentToRender : m_ComponentsToRenderFourth)
	{
		const AActor* Owner = ComponentToRender->GetOwner();
		if (const UImage* Image = ComponentToRender->GetStaticImage())
		{
			FVector2D ImageSize = { (float)Image->m_BitmapInfo.bmWidth , (float)Image->m_BitmapInfo.bmHeight };
			FVector2D ImagePosition = Owner->GetPosition() - ImageSize / 2;
			ImagePosition += ComponentToRender->GetStaticImageOffset();

			// 쓰레드에 과연 안전한 함수인가.
			// TransparentBlt
			TransparentBlt(m_hLayer[3], ImagePosition.X, ImagePosition.Y, ImageSize.X, ImageSize.Y,
				Image->getDC(), 0, 0, ImageSize.X, ImageSize.Y, RGB(255, 0, 255));
		}
	}

	IsRender[3] = true;
}

void ThreadFunction(std::function<void()> _Test)
{
	_Test();
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

	// 새 렌더 코드

	UResourceManager* ResourceManager = GEngine->GetEngineSubsystem<UResourceManager>();
	HDC hImage = ResourceManager->GetImageDC("Resources\\MagentaBack.bmp");

	// 투명값 초기화
	for (size_t i = 0; i < 4; i++)
	{
		BitBlt(m_hLayer[i], 0, 0, (int)m_WindowSize.X, (int)m_WindowSize.Y, hImage, 0, 0, SRCCOPY);
	}


	//for (URenderComponent* ComponentToRender : m_ComponentsToRenderFirst)
	//{
	//	AActor* Actor = ComponentToRender->GetOwner();
	//	FVector2D ActorPos = Actor->GetPosition() ;
	//	if (UImage* Image = ComponentToRender->GetStaticImage())
	//	{
	//		TransparentBlt(m_hLayer[0], ActorPos.X, )
	//	}
	//}


	IsRender[0] = false;
	IsRender[1] = false;
	IsRender[2] = false;
	IsRender[3] = false;

	// 쓰레드를 만드는 것도 비용이기 
	std::thread Thread0 = std::thread(std::bind(&URenderManager::RenderF, this));
	std::thread Thread1 = std::thread(std::bind(&URenderManager::RenderS, this));
	std::thread Thread2 = std::thread(std::bind(&URenderManager::RenderT, this));
	std::thread Thread3 = std::thread(std::bind(&URenderManager::RenderFo, this));

	// while (true == IsRender[0] && true == IsRender[1] && true == IsRender[1]);

	// 쓰레드는 한개 쓸꺼면 더 안좋다.
	


	for (size_t i = 0; i < 4; i++)
	{
		TransparentBlt(m_hBackBufferDC,
			0, 0,
			(int)m_WindowSize.X, (int)m_WindowSize.Y,
			m_hLayer[i],
			0, 0,
			(int)m_WindowSize.X, (int)m_WindowSize.Y,
			RGB(255, 0, 255));
	}





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


	ShowWindow(m_hGameWindow, SW_SHOW);
	UpdateWindow(m_hGameWindow);

	

	for (size_t i = 0; i < 4; i++)
	{
		HDC NewDC = CreateCompatibleDC(m_hGameWindowDC);
		HBITMAP hBackBufferBitmap = CreateCompatibleBitmap(m_hGameWindowDC, (int)WindowSize.X, (int)WindowSize.Y);
		SelectObject(NewDC, hBackBufferBitmap);
		m_hLayer[i] = NewDC;
	}

	

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
	m_CustomRenderEvents{}
{
}

URenderManager::~URenderManager()
{
	this->Release();
}
