#pragma once
#include "KmEngine/AIController.h"

class ACharacterAIController : public AAIController
{
	typedef AAIController Super;

public:
	float GetChangeDirectionTime();
	FVector2D GetDirection();
	void SetRandomDirection();
	void SetAccumulatedTime(float fTime);
	float GetAccumulatedTime();

public:
	void Possess(APawn* Pawn) override;

public:
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
	void BeginPlay() override;

public:
	ACharacterAIController();

protected:
	float m_fChangeDirectionTime;
	float m_fAccumulatedTime;
	FVector2D m_Direction;
};

