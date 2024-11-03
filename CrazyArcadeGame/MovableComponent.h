#pragma once
#include "KmBase/Vector.h"
#include "kmEngine/ActorComponent.h"

class UMovableComponent : public UActorComponent
{
	typedef UActorComponent Super;

public:
	void AddVelocity(FVector2D Velocity);
	void SetVelocity(FVector2D Velocity);
	void SetMaxSpeed(float MaxSpeed);
	float GetMaxSpeed();
	FVector2D GetVelocity();
	void RegisterAtMovementManager();

public:
	void BeginPlay() override;
	void TickComponent(float fDeltaTime) override;

public:
	UMovableComponent();

private:
	float m_fRadius;
	FVector2D m_Velocity;
	float m_MaxSpeed;
};

