#include "stdafx.h"
#include <crtdbg.h>

#include "KmEngine/Engine.h"
#include "KmEngine/GameInstance.h"
#include "KmEngine/TestGameInstance.h"
#include "KmEngine/TestGamemode.h"
#include "KmEngine/Level.h"

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

	// Editor 구현되면 그곳에서 객체를 만들기
	UTestGameInstance* TestGameInstance = new UTestGameInstance{};
	ULevel* TestLevel = new ULevel{};
	AActor* TestActor = new AActor{};
	ATestGamemode* TestGamemode = new ATestGamemode{};
	TestLevel->m_Actors.insert(TestActor);
	TestLevel->m_Gamemode = TestGamemode;

	GEngine->SetGameInstance(TestGameInstance);
	GEngine->GetGameInstance()->LoadLevel("TestLevel", TestLevel);
	GEngine->GetGameInstance()->OpenLevel("TestLevel");

	GEngine->RunForever();

	delete GEngine;

	_CrtDumpMemoryLeaks();
}