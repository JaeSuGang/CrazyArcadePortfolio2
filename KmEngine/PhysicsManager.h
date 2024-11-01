#pragma once
#include "EngineSubsystem.h"

class UPhysicsManager : public UEngineSubsystem
{
public:
	void Tick(float fDeltaTime);

public:
	void Initialize();
};

