#pragma once
#include "KmEngine/Actor.h"

class AGameUI : public AActor
{
	typedef AActor Super;

public:
	void BeginPlay() override;
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
};

