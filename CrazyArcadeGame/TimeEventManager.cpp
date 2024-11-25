#include "stdafx.h"
#include "TimeEventManager.h"

void UTimeEventManager::Tick(float fDeltaTime)
{
	this->TimeElapsed += fDeltaTime;
}

void UTimeEventManager::AddTimeEvent(std::function<void()> Function, float TriggerDelay)
{
	FTimeEvent TimeEvent;
	TimeEvent.FunctionToTrigger = Function;
	TimeEvent.TimeToTrigger = TimeElapsed + TriggerDelay;

	TimeEvents.push_back(TimeEvent);
}
