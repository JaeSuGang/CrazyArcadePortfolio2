#include "stdafx.h"
#include "KmEngine/Engine.h"

#pragma comment (lib, "KmBase.lib")
#pragma comment (lib, "KmEngine.lib")

class UKeyManager;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GEngine->GetEngineSubsystem<UKeyManager>();

	delete GEngine;
}