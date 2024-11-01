#pragma once
#include "Object.h"
#include "stdafx.h"
#include "KeyManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "GameInstance.h"

class UGameInstance;

class UEngine : public UObject
{
public:
	void RunForever();
	void TerminateEngine();

// 사용자가 일일히 Subsystem을 Create해야 합니다
public:
	void CreateResourceManager(HWND hGameWindow);
	void CreateRenderManager(const char* lpszTitle);
	void CreateTimeManager();
	void CreateKeyManager();
	void CreatePhysicsManager();

public:
	UGameInstance* GetGameInstance() const;
	template <typename T>
	void OpenGameInstance()
	{
		SAFE_DELETE(m_ActiveGameInstance);
		m_ActiveGameInstance = new T{};
		m_ActiveGameInstance->Initialize();
		m_ActiveGameInstance->BeginPlay();
	}

	template <typename T>

	T* GetEngineSubsystem()
	{
		// typeid를 unordered_map의 key값으로 탐색
		// 컨테이너의 모든 요소들을 순환하면서 dynamic_cast하여 찾는것보다 매우 효율적
		string ClassName = typeid(T).name();
		auto iter = m_Subsystems.find(ClassName);

		// #ifdef _DEBUG 를 통해 디버그 모드에서만 확인할 수 있는 에러 정보
		// 릴리즈 모드에서는 최적화되어, 없는 코드가 됨
		if (iter == m_Subsystems.end())
		{
			SHOW_ERROR(("존재하지 않는 엔진 서브시스템입니다 : " + ClassName).c_str());
		}

		// 캐스팅 성공을 보장할 수 있기 때문에,
		// 성능 오버헤드를 줄이고자 dynamic_cast 대신 static_cast 사용
		T* Casted = static_cast<T*>((*iter).second);

		return Casted;
	}

	float GetTargetFPS() const;
	void SetTargetFPS(float fTargetFPS);

public:
	UEngine();
	~UEngine();
private:
	void Release();

private:
	void Tick();

private:
	UGameInstance* m_ActiveGameInstance;
	unordered_map<string, UEngineSubsystem*> m_Subsystems;
	float m_fTargetFPS;
	bool m_bEngineSwitch;

};

extern UEngine* GEngine;

