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
	float GetRadius() const;
	void SetRadius(float fRadius);
	FVector2D GetVelocity();
	void RegisterMovableAtMovementManager();

public:
	void BeginPlay() override;
	void TickComponent(float fDeltaTime) override;

public:
	UMovableComponent();

private:
	FVector2D m_Velocity;
	float m_fCollisionRadius;
	float m_MaxSpeed;
};

