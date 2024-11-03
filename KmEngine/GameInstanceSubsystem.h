#pragma once
#include "Object.h"

class ULevel;

class UGameInstanceSubsystem : public UObject
{
public:
	ULevel* GetActiveLevel();
};

