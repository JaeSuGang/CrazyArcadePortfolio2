#pragma once
#include "Actor.h"
#include "Pawn.h"

class AController : public AActor
{
	typedef AActor Super;

public:
	virtual void Possess(APawn* Pawn);

public:
	APawn* GetPawn() const;
	void SetPawn(APawn* Pawn);

public:
	void Destroy() override;
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
	void BeginPlay() override;

public:
	void Release();
	~AController();
	AController();

protected:
	APawn* m_Pawn;
};

