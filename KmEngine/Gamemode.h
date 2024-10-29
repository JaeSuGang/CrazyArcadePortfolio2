#pragma once
#include "Actor.h"

class AGamemode : public AActor
{
	typedef AActor Super;
	friend class ULevel;
	friend class UEngine;

protected:
	virtual void Tick(float fDeltaTime) override = 0;
	virtual void BeginPlay() override = 0;
};

