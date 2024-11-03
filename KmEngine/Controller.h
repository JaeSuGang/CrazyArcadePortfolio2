#pragma once
#include "Actor.h"
#include "Pawn.h"

class AController : public AActor
{
	typedef AActor Super;

public:
	void Possess(APawn* Pawn);

public:
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
	void BeginPlay() override;

public:
	void Release();
	~AController();

private:
	APawn* m_Pawn;
};

