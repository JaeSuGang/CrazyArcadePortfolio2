#include "stdafx.h"
#include <crtdbg.h>

#include "KmEngine/Engine.h"
#include "KmEngine/GameInstance.h"

#pragma comment (lib, "KmBase.lib")
#pragma comment (lib, "KmEngine.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	GEngine->CreateRenderManager("CrazyArcade");
	GEngine->CreateTimeManager();
	GEngine->CreateKeyManager();

	GEngine->GetEngineSubsystem<URenderManager>()->SetWindowSize(FVector2D(800.0f, 600.0f));
	GEngine->SetTargetFPS(240.0f);

	UGameInstance* TemporaryGameInstance = new UGameInstance{};
	GEngine->SetGameInstance(TemporaryGameInstance);

	GEngine->RunForever();

	delete GEngine;

	_CrtDumpMemoryLeaks();
}