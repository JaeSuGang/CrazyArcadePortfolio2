#pragma once
#include "stdafx.h"
#include "KmEngine/AIController.h"
#include "FSM.h"

class ACharacter;

class ACharacterAIController : public AAIController
{
	typedef AAIController Super;

public:
	class UIdleState : public UBaseState
	{
	public:
		void OnStateEnter() override;
		void OnStateUpdate(float fDeltaTime) override;
		void OnStateExit() override;
	};

	class UTaskState : public UBaseState
	{
	public:
		void OnStateEnter() override;
		void OnStateUpdate(float fDeltaTime) override;
		void OnStateExit() override;
	};

	class UEvadeState : public UBaseState
	{
	public:
		void OnStateEnter() override;
		void OnStateUpdate(float fDeltaTime) override;
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

	void SetRandomIdleTimer();

	void SetAccumulatedTime(float fTime);

	float GetAccumulatedTime();


public:
	std::list<FVector2D> m_Path;

	UFSMComponent* m_FSM;

	ACharacter* m_Character;


public:
	ATTTIBUTE_ACCESSORS(float, IdleTimer);

protected:
	float IdleTimer;

	float m_fAccumulatedTime;

	FVector2D m_Direction;
};

