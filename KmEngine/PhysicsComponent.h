#pragma once
#include "ActorComponent.h"

class FCollider
{
public:
	enum class EShape
	{
		Circle,
		Square
	};

public:
	bool Enabled;
	EShape Shape;
	float Radius;
};

class UPhysicsComponent : public UActorComponent
{
	typedef UActorComponent Super;

public:
	void SetColliderRadius(float Radius);
	void SetColliderShape(FCollider::EShape Shape);
	void EnableCollision();
	void DisableCollision();
	void AddVelocity(FVector2D AddedVelocity);
	void SetVelocity(FVector2D Velocity);
	FVector2D GetVelocity();
	float GetMaxSpeed() const;
	void SetMaxSpeed(float fValue);

public:
	void BeginPlay() override;
	void TickComponent(float fDeltaTime) override;

public:
	UPhysicsComponent();

private:
	float m_fMaxSpeed;
	FCollider m_Collider;
	FVector2D m_Velocity;
};

