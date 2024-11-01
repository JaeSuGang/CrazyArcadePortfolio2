#pragma once
#include "stdafx.h"
#include "Object.h"
#include "CrazyArcadeGame/TestLevel.h"

class ULevel;

class UGameInstance : public UObject
{
	friend class UEngine;
	
public:
	ULevel* GetActiveLevel() const;
	//typedef UTestLevel T;
	template <typename T>
	T* OpenLevel()
	{
		SAFE_DELETE(m_ActiveLevel);
		T* NewLevel = new T{};
		m_ActiveLevel = NewLevel;
		NewLevel->Initialize();
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
	virtual void Initialize() = 0;

// ���� ���� ���� ����
public:
	ULevel* m_ActiveLevel;
};

