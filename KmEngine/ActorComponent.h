#pragma once
#include "Object.h"

class AActor;

class UActorComponent : public UObject
{
	friend class AActor;

protected:
	virtual void BeginPlay();
	virtual void TickComponent(float fDeltaTime);

protected:
	AActor* m_Owner;
};

