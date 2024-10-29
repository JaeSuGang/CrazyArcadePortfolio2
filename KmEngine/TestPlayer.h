#pragma once
#include "Actor.h"

class ATestPlayer : public AActor
{
	typedef AActor Super;

public:
	// AActor을(를) 통해 상속됨
	void Initialize() override;
	void Tick(float fDeltaTime) override;
	void BeginPlay() override;
};

