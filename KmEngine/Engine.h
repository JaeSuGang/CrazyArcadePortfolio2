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
	float GetDeltaTime();
	void RunForever();
	void TerminateEngine();

// 사용자가 일일히 Subsystem을 Create해야 합니다
public:
	UResourceManager* CreateResourceManager(HWND hGameWindow);
	void CreateDebugManager(HDC hGameWindowDC);
	URenderManager* CreateRenderManager(const char* lpszTitle, FVector2D WindowSize);
	void CreateTimeManager();
	void CreateKeyManager();
	void CreateSoundManager();
	void CreateRandomManager();

public:
	UGameInstance* GetGameInstance() const;
	template <typename T>
	void OpenGameInstance()
	{
		SAFE_DELETE(m_ActiveGameInstance);
		m_ActiveGameInstance = new T{};
		m_ActiveGameInstance->BeginPlay();
	}

	template <typename T>
	T* GetEngineSubsystem()
	{
		string ClassName = typeid(T).name();
		auto iter = m_Subsystems.find(ClassName);

		if (iter == m_Subsystems.end())
		{
			SHOW_ERROR(("존재하지 않는 엔진 서브시스템입니다 : " + ClassName).c_str());
		}

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

