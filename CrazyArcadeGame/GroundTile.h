#pragma once
#include "KmEngine/Actor.h"

class AGroundTile : public AActor
{
	typedef AActor Super;

public:
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
};

