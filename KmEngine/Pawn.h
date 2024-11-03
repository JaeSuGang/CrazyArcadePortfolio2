#pragma once
#include "Actor.h"

class APawn : public AActor
{
	typedef AActor Super;

public:
	virtual void SetupPlayerInput() = 0;

public:
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
	void BeginPlay() override;
};

