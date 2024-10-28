#include "stdafx.h"
#include "Engine.h"
#include "KeyManager.h"
#include "WindowManager.h"

using std::pair;

void UEngine::Tick()
{

}

void UEngine::CreateWindowManager()
{
	UEngineSubsystem* Subsystem = new UWindowManager{};


	string ClassName = typeid(UWindowManager).name();
	pair<string, UEngineSubsystem*> PairToInsert{ClassName, Subsystem};
	m_Subsystems.insert(PairToInsert);
}

UEngine::~UEngine()
{
	this->Release();
}

void UEngine::Release()
{
	auto iter = m_Subsystems.begin();

	while (iter != m_Subsystems.end())
	{
		SAFE_DELETE((*iter).second);
		++iter;
	}
}


UEngine* GEngine = new UEngine{};
