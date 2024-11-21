#pragma once
#include "Object.h"
#include "Engine.h"
#include "GameInstanceSubsystem.h"

class AActor;

class UActorComponent : public UObject
{
	friend class AActor;

public:
	AActor* GetOwner() const;

	template <typename T>
	T* GetGameInstanceSubsystem()
	{
		return GEngine->GetGameInstance()->GetSubsystem<T>();
	}

public:
	virtual void BeginPlay() = 0;
	virtual void TickComponent(float fDeltaTime) = 0;

public:
	UActorComponent();

protected:
	AActor* m_Owner;
};

