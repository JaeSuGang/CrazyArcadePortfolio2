#pragma once
#include "KmEngine/ActorComponent.h"

class UExplosionComponent : public UActorComponent
{
	typedef UActorComponent Super;

public:
	void BeginPlay() override;
	void TickComponent(float fDeltaTime) override;

private:
	bool bIsCenterExplosion;

};

