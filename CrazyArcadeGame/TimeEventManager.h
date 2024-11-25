#pragma once
#include "stdafx.h"
#include "KmEngine/GameInstanceSubsystem.h"

class UTimeEventManager : public UGameInstanceSubsystem
{
public:
	struct FTimeEvent
	{
	public:
		float TimeToTrigger;
		std::function<void()> FunctionToTrigger;
	};

public:
	// Constructors and Overrides;
	void Tick(float fDeltaTime) override;

	void AddTimeEvent(std::function<void()> Function, float TriggerDelay);

	void HandleTimeEvents();

	void ClearTimeEvents();

public:
	ACCESSORS_ALL(float, TimeElapsed);

private:
	vector<FTimeEvent> TimeEvents;
	float TimeElapsed;
};

