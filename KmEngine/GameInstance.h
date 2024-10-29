#pragma once
#include "Object.h"

class UGameInstance : public UObject
{
	friend class UEngine;

public:
	UGameInstance();

protected:
	virtual void Tick(float fDeltaTime);
	virtual void BeginPlay();
};

