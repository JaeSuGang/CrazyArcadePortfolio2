#pragma once
#include "Controller.h"

class AAIController : public AController
{
	typedef AController Super;

public:
	void Unpossess() override;
	void Possess(APawn* Pawn) override;

public:
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
	void BeginPlay() override;

public:
	void Release();
	~AAIController();
};

