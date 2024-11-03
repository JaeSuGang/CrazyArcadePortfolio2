#pragma once
#include "KmEngine/Actor.h"

class AGameGUI1 : public AActor
{
	typedef AActor Super;
public:
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
	void BeginPlay() override;
};

