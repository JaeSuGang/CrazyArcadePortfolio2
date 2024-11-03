#pragma once
#include "Actor.h"
#include "Pawn.h"

class AController : public AActor
{
	typedef AActor Super;

public:


public:
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
	void BeginPlay() override;

private:
	APawn* m_Pawn;
};

