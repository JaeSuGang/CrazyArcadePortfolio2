#pragma once
#include "stdafx.h"
#include "Object.h"

class ULevel;
class UGameInstanceSubsystem;

class UGameInstance : public UObject
{
	friend class UEngine;
	
public:
	template <typename T>
	T* GetGameInstanceSubsystem()
	{
		string ClassName = typeid(T).name();
		auto SubsystemIter = m_Subsystems.find(ClassName);

		if (SubsystemIter == m_Subsystems.end())
		{
			SHOW_ERROR("GetGameInstanceSubsystem, �������� �ʴ� Ŭ���� �Դϴ�");
		}

		return static_cast<T*>(SubsystemIter->second);
	}

	template <typename T>
	T* CreateGameInstanceSubsystem()
	{
		static_assert(std::is_base_of<UGameInstanceSubsystem, T>::value);
		T* Subsystem = new T{};
		string ClassName = typeid(T).name();
		pair<string, UGameInstanceSubsystem*> PairToInsert{ ClassName, Subsystem };
		m_Subsystems.insert(PairToInsert);
		return Subsystem;
	}

public:
	ULevel* GetActiveLevel() const;
	//typedef UTestLevel T;
	template <typename T>
	T* OpenLevel()
	{
		SAFE_DELETE(m_ActiveLevel);
		T* NewLevel = new T{};
		m_ActiveLevel = NewLevel;
		NewLevel->m_GameInstance = this;
		NewLevel->BeginPlay();
		return NewLevel;
	}


public:
	void Release();
	UGameInstance();
	virtual ~UGameInstance();

public:
	virtual void Tick(float fDeltaTime) = 0;
	virtual void LateTick(float fDeltaTime) = 0;
	virtual void BeginPlay() = 0;
	// �ڽ� Initialize���� OpenLevelȣ���Ұ�
	// OpenLevel���� Level�� initialize()�� ȣ���ϴ°�����,
	// Initialize���� level Initialize�� ȣ���ؼ��� �ȵ�

// ���� ���� ���� ����
public:
	unordered_map<string, UGameInstanceSubsystem*> m_Subsystems;
	ULevel* m_ActiveLevel;
};

