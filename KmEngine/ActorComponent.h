#pragma once
#include "Object.h"

class AActor;

class UActorComponent : public UObject
{
	friend class AActor;

public:
	virtual void Initialize() = 0;
	virtual void BeginPlay() = 0;
	virtual void TickComponent(float fDeltaTime) = 0;

public:
	UActorComponent();

protected:
	AActor* m_Owner;
};

