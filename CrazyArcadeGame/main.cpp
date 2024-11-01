#include "stdafx.h"
#include <crtdbg.h>

#include "KmEngine/Engine.h"
#include "CrazyArcadeGame/TestGameInstance.h"
#include "LevelDeserializer.h"

#pragma comment (lib, "KmBase.lib")
#pragma comment (lib, "KmEngine.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(305);

	URenderManager* RenderManager = GEngine->CreateRenderManager("CrazyArcade");
	HWND hGameWindow = GEngine->GetEngineSubsystem<URenderManager>()->GetGameWindowHandle();
	HDC hGameWindowDC = GEngine->GetEngineSubsystem<URenderManager>()->GetGameWindowDCHandle();

	GEngine->CreateTimeManager();
	GEngine->CreateKeyManager();
	GEngine->CreatePhysicsManager();
	UResourceManager* ResourceManager = GEngine->CreateResourceManager(hGameWindow);
	ResourceManager->LoadFolder("..\\");
	GEngine->CreateDebugManager(hGameWindowDC);

	GEngine->GetEngineSubsystem<URenderManager>()->SetWindowSize(FVector2D(800.0f, 600.0f));
	GEngine->SetTargetFPS(240.0f);

	// Editor 구현해서 CLevelDeserializer의 Deserialize함수를 path인자로 받도록 오버로딩
	GEngine->OpenGameInstance<UTestGameInstance>();

	GEngine->RunForever();

	delete GEngine;

	_CrtDumpMemoryLeaks();
}