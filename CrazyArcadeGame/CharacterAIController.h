#pragma once
#include "KmEngine/AIController.h"

class ACharacter;

class ACharacterAIController : public AAIController
{
	typedef AAIController Super;

public:
	class UBaseState abstract
	{
	public:
		virtual void OnStateEnter() = 0;
		virtual void OnStateUpdate() = 0;
		virtual void OnStateExit() = 0;
	};

	class UIdleState : public UBaseState
	{
	public:
		void OnStateEnter() override;
		void OnStateUpdate() override;
		void OnStateExit() override;
	};

	class UWorkState : public UBaseState
	{
	public:
		void OnStateEnter() override;
		void OnStateUpdate() override;
		void OnStateExit() override;
	};

	class UEvadeState : public UBaseState
	{
	public:
		void OnStateEnter() override;
		void OnStateUpdate() override;
		void OnStateExit() override;
	};

public:
	// Constructor and overrides
	ACharacterAIController();
	void Possess(APawn* Pawn) override;
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
	void BeginPlay() override;
	void OnDebug() override;


	void SetRandomPositionToGo();

	bool CheckPositionWhetherSafeToPutBomb(FVector2D Position, FVector2D& EscapeDest) const;

	void LocatePosToPutBomb();

	bool SetPathUsingAStar(FVector2D Destination);

	void SetPathByClicking();

	float GetChangeDirectionTime();

	FVector2D GetDirection();

	void SetNewIdleLastingTime(float fDuration);

	void SetAccumulatedTime(float fTime);

	float GetAccumulatedTime();


public:
	std::list<FVector2D> m_Path;

	UBaseState* m_AIState;

	ACharacter* m_Character;


protected:
	float m_fIdleLastingTime;

	float m_fAccumulatedTime;

	FVector2D m_Direction;
};

