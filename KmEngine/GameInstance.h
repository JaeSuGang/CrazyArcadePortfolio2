#pragma once
#include "stdafx.h"
#include "Object.h"

class ULevel;

class UGameInstance : public UObject
{
	friend class UEngine;
	
public:
	void LoadLevel(const char* lpszLevelName, ULevel* Level);
	void OpenLevel(const char* lpszLevelName);

public:
	UGameInstance();

protected:
	virtual void Tick(float fDeltaTime) = 0;
	virtual void BeginPlay() = 0;
	virtual void Initialize() = 0;

protected:

protected:
	void Release();
	virtual ~UGameInstance();

// 접근 제한 차후 수정
public:
	ULevel* m_ActiveLevel;
	unordered_map<string, ULevel*> m_LoadedLevels;
};

