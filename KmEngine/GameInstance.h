#pragma once
#include "Object.h"

class ULevel;

class UGameInstance : public UObject
{
	friend class UEngine;
	
public:
	UGameInstance();

protected:
	virtual void Tick(float fDeltaTime);
	virtual void BeginPlay();

protected:
	void Release();
	virtual ~UGameInstance();

protected:
	ULevel* m_ActiveLevel;
};

