#include "stdafx.h"
#include "Level.h"
#include "Engine.h"
#include "GameInstance.h"
#include "KeyManager.h"
#include "RenderManager.h"
#include "TimeManager.h"
#include "Gamemode.h"
#include "PhysicsManager.h"
#include "DebugManager.h"

using std::pair;

void UEngine::Tick()
{
	UKeyManager* KeyManager = GetEngineSubsystem<UKeyManager>();
	UTimeManager* TimeManager = GetEngineSubsystem<UTimeManager>();
	URenderManager* RenderManager = GetEngineSubsystem<URenderManager>();
	UPhysicsManager* PhysicsManager = GetEngineSubsystem<UPhysicsManager>();
	UDebugManager* DebugManager = GetEngineSubsystem<UDebugManager>();
	UGameInstance* GameInstance = GetGameInstance();

	float fDeltaTime = TimeManager->GetDeltaTime();

	if (fDeltaTime >= 1 / GetTargetFPS())
	{
		PhysicsManager->Tick(fDeltaTime);

		KeyManager->Tick(fDeltaTime);

		GameInstance->Tick(fDeltaTime);

		RenderManager->Tick();

		#ifdef _DEBUG:
		DebugManager->Tick(fDeltaTime);
		#endif

		TimeManager->ResetDeltaTime();
	}


}

void UEngine::RunForever()
{
	while (m_bEngineSwitch)
	{
		this->Tick();
	}
}

void UEngine::TerminateEngine()
{
	m_bEngineSwitch = false;
}

UGameInstance* UEngine::GetGameInstance() const
{
	if (m_ActiveGameInstance == nullptr)
	{
		SHOW_ERROR("GameInstance를 정해주지 않고 엔진을 실행시켰습니다")
	}

	return m_ActiveGameInstance;
}

void UEngine::CreateResourceManager(HWND hGameWindow)
{
	UResourceManager* Subsystem = new UResourceManager{};
	Subsystem->Initialize(hGameWindow);

	string ClassName = typeid(UResourceManager).name();
	pair<string, UEngineSubsystem*> PairToInsert{ ClassName, Subsystem };
	m_Subsystems.insert(PairToInsert);
}

void UEngine::CreateDebugManager(HDC hGameWindowDC)
{
	UDebugManager* Subsystem = new UDebugManager{};
	Subsystem->Initialize(hGameWindowDC);

	string ClassName = typeid(UDebugManager).name();
	pair<string, UEngineSubsystem*> PairToInsert{ ClassName, Subsystem };
	m_Subsystems.insert(PairToInsert);
}

void UEngine::CreateRenderManager(const char* lpszTitle)
{
	URenderManager* Subsystem = new URenderManager{};
	Subsystem->Initialize(lpszTitle);

	string ClassName = typeid(URenderManager).name();
	pair<string, UEngineSubsystem*> PairToInsert{ClassName, Subsystem};
	m_Subsystems.insert(PairToInsert);
}

void UEngine::CreateTimeManager()
{
	UTimeManager* Subsystem = new UTimeManager{};
	Subsystem->Initialize();

	string ClassName = typeid(UTimeManager).name();
	pair<string, UEngineSubsystem*> PairToInsert{ ClassName, Subsystem };
	m_Subsystems.insert(PairToInsert);
}

void UEngine::CreateKeyManager()
{
	UKeyManager* Subsystem = new UKeyManager{};
	Subsystem->Initialize();

	string ClassName = typeid(UKeyManager).name();
	pair<string, UEngineSubsystem*> PairToInsert{ ClassName, Subsystem };
	m_Subsystems.insert(PairToInsert);
}

void UEngine::CreatePhysicsManager()
{
	UPhysicsManager* Subsystem = new UPhysicsManager{};
	Subsystem->Initialize();

	string ClassName = typeid(UPhysicsManager).name();
	pair<string, UEngineSubsystem*> PairToInsert{ ClassName, Subsystem };
	m_Subsystems.insert(PairToInsert);
}


float UEngine::GetTargetFPS() const
{
	return m_fTargetFPS;
}

void UEngine::SetTargetFPS(float fTargetFPS)
{
	m_fTargetFPS = fTargetFPS;
}

UEngine::~UEngine()
{
	this->Release();
}

UEngine::UEngine()
	:
	m_bEngineSwitch{true},
	m_Subsystems{},
	m_ActiveGameInstance{},
	m_fTargetFPS{}
{
}

void UEngine::Release()
{
	SAFE_DELETE(m_ActiveGameInstance);

	auto iter = m_Subsystems.begin();

	while (iter != m_Subsystems.end())
	{
		SAFE_DELETE((*iter).second);
		++iter;
	}
}


UEngine* GEngine = new UEngine{};
