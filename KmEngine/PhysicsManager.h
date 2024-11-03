#pragma once
#include "stdafx.h"
#include "EngineSubsystem.h"


// This class is obsolete, no more used.
class UPhysicsManager : public UEngineSubsystem
{
public:
	class FPhysicsEvent
	{
	public:
		std::function<void()> Function;
	};

public:

public:
	void Tick(float fDeltaTime);
	//void 

public:
	void Initialize();

private:
	vector<FPhysicsEvent> m_PhysicsEvents;
};

