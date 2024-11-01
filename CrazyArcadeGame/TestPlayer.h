#pragma once
#include "KmEngine/Actor.h"


class ATestPlayer : public AActor
{
	typedef AActor Super;

public:
	void Move(FVector2D Direction);
	void Idle(FVector2D Direction);

public:
	void Initialize() override;
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
	void BeginPlay() override;

private:
	bool m_bIsAlreadyMoving;

};

