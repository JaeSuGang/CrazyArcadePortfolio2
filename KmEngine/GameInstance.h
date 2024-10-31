#pragma once
#include "stdafx.h"
#include "Object.h"
#include "CrazyArcadeGame/TestPlayer.h"

class ULevel;

class UGameInstance : public UObject
{
	friend class UEngine;
	
public:
	ULevel* GetActiveLevel() const;
	typedef ATestPlayer T;
	//template <typename T>
	T* OpenLevel()
	{
		SAFE_DELETE(m_ActiveLevel);
		T NewLevel = new T{};
	}


public:
	void Release();
	UGameInstance();
	virtual ~UGameInstance();

public:
	virtual void Tick(float fDeltaTime) = 0;
	virtual void BeginPlay() = 0;
	virtual void Initialize() = 0;

// 접근 제한 차후 수정
public:
	ULevel* m_ActiveLevel;
};

