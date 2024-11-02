#pragma once
#include "EngineSubsystem.h"

class UPhysicsManager : public UEngineSubsystem
{
public:
	class FPhysicsEvent
	{

	};

public:
	void Tick(float fDeltaTime);
	//void 

public:
	void Initialize();

private:
	vector<FPhysicsEvent> m_PhysicsEvents;
};

