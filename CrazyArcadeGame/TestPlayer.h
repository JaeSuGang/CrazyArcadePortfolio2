#pragma once
#include "KmEngine/Actor.h"


class ATestPlayer : public AActor
{
public:
	void Move(FVector2D Direction);

public:
	void Initialize() override;
	void Tick(float fDeltaTime) override;
	void BeginPlay() override;
};

