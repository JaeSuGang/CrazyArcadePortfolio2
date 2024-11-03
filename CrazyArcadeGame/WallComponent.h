#pragma once
#include "KmEngine/ActorComponent.h"

class UWallComponent : public UActorComponent
{
	typedef UActorComponent Super;

public:
	void BeginPlay() override;
	void TickComponent(float fDeltaTime) override;
};

