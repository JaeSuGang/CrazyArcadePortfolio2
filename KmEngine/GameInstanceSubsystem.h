#pragma once
#include "Object.h"

class ULevel;
class UGameInstance;

class UGameInstanceSubsystem : public UObject
{
public:
	UGameInstance* GetGameInstance() const;

	ULevel* GetActiveLevel() const;

public:
	virtual void Tick(float fDeltaTime) = 0;
};

