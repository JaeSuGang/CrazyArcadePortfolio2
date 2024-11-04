#pragma once
#include "Controller.h"

class APlayerController : public AController
{
	typedef AController Super;

public:
	void Possess(APawn* Pawn) override;

public:
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
	void BeginPlay() override;
};

