#pragma once
#include "stdafx.h"
#include "KmEngine/AIController.h"
#include "FSM.h"
#include "AttributeData.h"

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

	bool CheckAndEvade();

	bool GetIsInDangerousPosition() const;

	bool GetIsDangerousPosition(FVector2D PositionToCheck) const;

	void FollowPath();

	void SetRandomPositionToGo();

	bool GetRandomPlaceToPutBomb(FVector2D& Output);

	bool GetRandomPlaceToGo(FVector2D& Output);

	bool CheckPositionWhetherSafeToPutBomb(FVector2D Position) const;

	void LocatePosToPutBomb();

	bool SetPathUsingAStar(FVector2D Destination);

	void SetPathByClicking();

	FVector2D GetDirection();

	void SetRandomDirection();

	void SetRandomDirectionTimer();

	void SetRandomTaskSearchTimer();

	void SetRandomIdleTimer();

	void SetRandomEvadeCheckCooldown(float fAdditionalTime);

	void SubtractEvadeWaitTimer(float fDeltaTime);

	void SubtractTaskSearchCooldown(float fDeltaTime);

	void SubtractDirectionTimer(float fDeltaTime);

	void SubtractEvadeCheckCooldown(float fDeltaTime);

	void SetAccumulatedTime(float fTime);

	float GetAccumulatedTime();


public:
	std::list<FVector2D> Path;

	UFSMComponent* FSM;

	ACharacter* m_Character;


public:
	ACCESSORS_ALL(float, IdleTimer)
	ACCESSORS_ALL(float, TaskSearchCooldown)
	ACCESSORS_ALL(float, EvadeCheckCooldown)
	ACCESSORS_ALL(float, EvadeWaitTimer)
	ACCESSORS_GETTER(float, DirectionTimer)

protected:
	float EvadeWaitTimer;

	float IdleTimer;

	float EvadeCheckCooldown;

	float TaskSearchCooldown;

	float DirectionTimer;

	float AccumulatedTime;

	FVector2D Direction;
};

