#pragma once
#include "KmEngine/AIController.h"

class ACharacter;

class ACharacterAIController : public AAIController
{
	typedef AAIController Super;

public:
	enum class EAIState
	{
		Idle,
		Move
	};

public:
	void LocatePosToPutBomb();
	bool SetPathUsingAStar(FVector2D Destination);
	void SetPathByClicking();

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

public:
	std::list<FVector2D> m_Path;
	EAIState m_AIState;
	ACharacter* m_Character;
	bool m_bDebugMode{};
	HPEN m_hDebugPen;

protected:
	float m_fChangeDirectionTime;
	float m_fAccumulatedTime;
	FVector2D m_Direction;
};

