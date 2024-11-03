#pragma once
#include "Object.h"

class ULevel;

class UGameInstanceSubsystem : public UObject
{
public:
	ULevel* GetActiveLevel();

public:
	virtual void Tick(float fDeltaTime) = 0;
};

