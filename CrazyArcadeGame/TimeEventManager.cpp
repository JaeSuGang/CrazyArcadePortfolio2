#include "stdafx.h"
#include "TimeEventManager.h"

void UTimeEventManager::Tick(float fDeltaTime)
{
	TimeElapsed += fDeltaTime;

	this->HandleTimeEvents();
}

void UTimeEventManager::AddTimeEvent(std::function<void()> Function, float TriggerDelay)
{
	FTimeEvent TimeEvent;
	TimeEvent.FunctionToTrigger = Function;
	TimeEvent.TimeToTrigger = TimeElapsed + TriggerDelay;

	TimeEvents.push_back(TimeEvent);
}

void UTimeEventManager::HandleTimeEvents()
{
	if (TimeEvents.size() > 0)
	{
		auto EndIterToErase = std::remove_if(TimeEvents.begin(), TimeEvents.end(),
			[this](FTimeEvent& Event)
			{
				if (Event.TimeToTrigger <= this->GetTimeElapsed())
				{
					Event.FunctionToTrigger();
					return true;
				}
				return false;
			});

		if (EndIterToErase != TimeEvents.end())
			TimeEvents.erase(EndIterToErase, TimeEvents.end());
	}
}

void UTimeEventManager::ClearTimeEvents()
{
	TimeEvents.clear();
}
