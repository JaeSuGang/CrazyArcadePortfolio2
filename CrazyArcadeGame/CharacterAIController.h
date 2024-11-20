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
		Move,
	};

public:
	bool CheckPositionWhetherSafeToPutBomb(FVector2D Position, FVector2D& EscapeDest) const;
	void LocatePosToPutBomb();
	bool SetPathUsingAStar(FVector2D Destination);

	// 디버그용
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
	void OnDebug() override;

public:
	ACharacterAIController();

public:
	std::list<FVector2D> m_Path;
	EAIState m_AIState;
	ACharacter* m_Character;

protected:
	float m_fChangeDirectionTime;
	float m_fAccumulatedTime;
	FVector2D m_Direction;
};

