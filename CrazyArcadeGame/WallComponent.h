#pragma once
#include "KmEngine/ActorComponent.h"

class UWallComponent : public UActorComponent
{
	typedef UActorComponent Super;

public:
	FVector2D GetCollisionSize() const;
	void SetCollisionSize(FVector2D Size);
	void RegisterAtMovementManager(bool CanBeFliedOver);
	bool GetCanBeFliedOver() const;
	void SetCanBeFliedOver(bool bValue);

public:
	void BeginPlay() override;
	void TickComponent(float fDeltaTime) override;

private:
	FVector2D m_CollisionSize;
	bool m_bCanBeFliedOver;
};

