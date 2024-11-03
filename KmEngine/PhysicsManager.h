#pragma once
#include "stdafx.h"
#include "EngineSubsystem.h"

class UPhysicsManager : public UEngineSubsystem
{
public:
	class FPhysicsEvent
	{
	public:
		std::function<void()> Function;
	};

public:
	void AddMovePhysicsEvent(std::function<void()> Function);

public:
	void Tick(float fDeltaTime);
	//void 

public:
	void Initialize();

private:
	vector<FPhysicsEvent> m_PhysicsEvents;
};

