#pragma once
#include "Actor.h"

class APawn : public AActor
{
	typedef AActor Super;

public:
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
	void BeginPlay() override;
};

