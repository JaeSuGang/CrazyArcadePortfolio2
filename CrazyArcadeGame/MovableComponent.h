#pragma once
#include "KmBase/Vector.h"
#include "kmEngine/ActorComponent.h"

class UMovableComponent : public UActorComponent
{
	typedef UActorComponent Super;

public:
	FVector2D GetCollisionSize() const;
	void SetCollisionSize(FVector2D Size);
	void AddVelocity(FVector2D Velocity);
	void SetVelocity(FVector2D Velocity);
	void SetMaxSpeed(float MaxSpeed);
	float GetMaxSpeed();
	FVector2D GetVelocity();
	void RegisterMovableAtMovementManager();

public:
	void BeginPlay() override;
	void TickComponent(float fDeltaTime) override;

public:
	UMovableComponent();

private:
	bool m_bFlying;
	FVector2D m_Velocity;
	FVector2D m_CollisionSize;
	float m_MaxSpeed;
};

