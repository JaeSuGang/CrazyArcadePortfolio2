#pragma once
#include "ActorComponent.h"

class UPhysicsComponent : public UActorComponent
{
	typedef UActorComponent Super;

public:
	void AddVelocity(FVector2D AddedVelocity);
	void SetVelocity(FVector2D Velocity);
	FVector2D GetVelocity();
	float GetMaxSpeed() const;
	void SetMaxSpeed(float fValue);

public:
	void Initialize() override;
	void BeginPlay() override;
	void TickComponent(float fDeltaTime) override;

public:
	UPhysicsComponent();

private:
	bool m_bHasCollision;
	float m_fMaxSpeed;
	FVector2D m_Velocity;
};

