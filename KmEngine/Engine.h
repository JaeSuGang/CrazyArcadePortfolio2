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

// ����ڰ� ������ Subsystem�� Create�ؾ� �մϴ�
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
		// typeid�� unordered_map�� key������ Ž��
		// �����̳��� ��� ��ҵ��� ��ȯ�ϸ鼭 dynamic_cast�Ͽ� ã�°ͺ��� �ſ� ȿ����
		string ClassName = typeid(T).name();
		auto iter = m_Subsystems.find(ClassName);

		// #ifdef _DEBUG �� ���� ����� ��忡���� Ȯ���� �� �ִ� ���� ����
		// ������ ��忡���� ����ȭ�Ǿ�, ���� �ڵ尡 ��
		if (iter == m_Subsystems.end())
		{
			SHOW_ERROR(("�������� �ʴ� ���� ����ý����Դϴ� : " + ClassName).c_str());
		}

		// ĳ���� ������ ������ �� �ֱ� ������,
		// ���� ������带 ���̰��� dynamic_cast ��� static_cast ���
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

