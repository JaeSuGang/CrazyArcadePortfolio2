#include "stdafx.h"
#include <crtdbg.h>

#include "KmEngine/Engine.h"
#include "CrazyArcadeGame/TestGameInstance.h"

#pragma comment (lib, "KmBase.lib")
#pragma comment (lib, "KmEngine.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(305);

	FVector2D WindowSize{ 1215.0f, 935.0f };

	URenderManager* RenderManager = GEngine->CreateRenderManager("CrazyArcade", WindowSize);
	HWND hGameWindow = GEngine->GetEngineSubsystem<URenderManager>()->GetGameWindowHandle();
	HDC hGameWindowDC = GEngine->GetEngineSubsystem<URenderManager>()->GetGameWindowDCHandle();

	GEngine->CreateTimeManager();
	GEngine->CreateKeyManager();
	GEngine->CreatePhysicsManager();
	UResourceManager* ResourceManager = GEngine->CreateResourceManager(hGameWindow);
	ResourceManager->LoadAll();
	GEngine->CreateDebugManager(hGameWindowDC);

	GEngine->GetEngineSubsystem<URenderManager>()->SetWindowSize(WindowSize);
	GEngine->SetTargetFPS(500000.0f);

	// Editor 구현해서 CLevelDeserializer의 Deserialize함수를 path인자로 받도록 오버로딩
	GEngine->OpenGameInstance<UTestGameInstance>();

	GEngine->RunForever();

	delete GEngine;

	_CrtDumpMemoryLeaks();
}