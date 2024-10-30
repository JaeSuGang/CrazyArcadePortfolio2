#include "stdafx.h"
#include <crtdbg.h>

#include "KmEngine/Engine.h"
#include "KmEngine/GameInstance.h"
#include "KmEngine/TestGameInstance.h"
#include "KmEngine/TestGamemode.h"
#include "KmEngine/Level.h"
#include "LevelDeserializer.h"

#pragma comment (lib, "KmBase.lib")
#pragma comment (lib, "KmEngine.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(302);

	GEngine->CreateRenderManager("CrazyArcade");
	HWND hGameWindow = GEngine->GetEngineSubsystem<URenderManager>()->GetGameWindowHandle();
	GEngine->CreateTimeManager();
	GEngine->CreateKeyManager();
	GEngine->CreateResourceManager(hGameWindow);

	GEngine->GetEngineSubsystem<URenderManager>()->SetWindowSize(FVector2D(800.0f, 600.0f));
	GEngine->SetTargetFPS(240.0f);

	// Editor 구현해서 CLevelDeserializer의 Deserialize함수를 path인자로 받도록 오버로딩
	UTestGameInstance* TestGameInstance = new UTestGameInstance{};
	FLevelData* LevelData = new FLevelData{};
	LevelData->ActorCount = 1;
	LevelData->ActorDatas[0].ActorPosition = FVector2D{300.0f, 300.0f};
	LevelData->ActorDatas[0].ActorType = EActorType::Player;
	LevelData->GamemodeType = EGamemodeType::Test;
	ULevel* DeserializedLevel = CLevelDeserializer::Deserialize(LevelData);

	GEngine->SetGameInstance(TestGameInstance);
	GEngine->GetGameInstance()->LoadLevel("TestLevel", DeserializedLevel);
	GEngine->GetGameInstance()->OpenLevel("TestLevel");

	GEngine->RunForever();

	delete LevelData;
	delete GEngine;

	_CrtDumpMemoryLeaks();
}