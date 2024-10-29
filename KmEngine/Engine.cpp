#include "stdafx.h"
#include "Engine.h"
#include "GameInstance.h"
#include "KeyManager.h"
#include "RenderManager.h"
#include "TimeManager.h"

using std::pair;

void UEngine::Tick()
{
	UKeyManager* KeyManager = GetEngineSubsystem<UKeyManager>();
	UTimeManager* TimeManager = GetEngineSubsystem<UTimeManager>();
	URenderManager* RenderManager = GetEngineSubsystem<URenderManager>();
	UGameInstance* GameInstance = GetGameInstance();

	float fDeltaTime = TimeManager->GetDeltaTime();

	if (fDeltaTime >= 1 / GetTargetFPS())
	{
		KeyManager->Tick(fDeltaTime);

		GameInstance->Tick(fDeltaTime);
	


		RenderManager->Tick();

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
		SHOW_ERROR("GameInstance�� �������� �ʰ� ������ ������׽��ϴ�")
	}

	return m_ActiveGameInstance;
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

void UEngine::SetGameInstance(UGameInstance* GameInstance)
{
	m_ActiveGameInstance = GameInstance;
	m_ActiveGameInstance->BeginPlay();
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
