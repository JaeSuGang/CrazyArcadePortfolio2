#pragma once
#include "kmEngine/ActorComponent.h"

class UMovableComponent : public UActorComponent
{
	typedef UActorComponent Super;

public:
	void BeginPlay() override;
	void TickComponent(float fDeltaTime) override;
};

