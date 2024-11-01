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
	// 자식 Initialize에서 OpenLevel호출할것
	// OpenLevel에서 Level의 initialize()를 호출하는것이지,
	// Initialize에서 level Initialize를 호출해서는 안됨
	virtual void Initialize() = 0;

// 접근 제한 차후 수정
public:
	ULevel* m_ActiveLevel;
};

