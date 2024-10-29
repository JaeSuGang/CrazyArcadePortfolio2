#pragma once
#include "Object.h"

class AActor;

class UActorComponent : public UObject
{
	friend class AActor;

protected:
	virtual void Initialize() = 0;
	virtual void BeginPlay() = 0;
	virtual void TickComponent(float fDeltaTime) = 0;

protected:
	AActor* m_Owner;
};

