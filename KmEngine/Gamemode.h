#pragma once
#include "Actor.h"

class AGamemode : public AActor
{
	typedef AActor Super;
	friend class ULevel;

protected:
	virtual void Tick(float fDeltaTime) override;
	virtual void BeginPlay() override;
};

