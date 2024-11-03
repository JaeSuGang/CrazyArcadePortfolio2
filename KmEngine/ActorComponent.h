#pragma once
#include "Object.h"
#include "Engine.h"
#include "GameInstanceSubsystem.h"

class AActor;

class UActorComponent : public UObject
{
	friend class AActor;

public:
	template <typename T>
	T* GetGameInstanceSubsystem()
	{
		return GEngine->GetGameInstance()->GetGameInstanceSubsystem<T>();
	}

public:
	virtual void BeginPlay() = 0;
	virtual void TickComponent(float fDeltaTime) = 0;

public:
	UActorComponent();

protected:
	AActor* m_Owner;
};

