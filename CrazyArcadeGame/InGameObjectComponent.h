#pragma once
#include "KmEngine/ActorComponent.h"

struct FInGameObjectProperty
{
public:
	static const FInGameObjectProperty Character;
	static const FInGameObjectProperty HidableWall;
	static const FInGameObjectProperty MovableWall;
	static const FInGameObjectProperty ExplodableWall;
	static const FInGameObjectProperty NonExplodableWall;

public:
	FVector2D m_CollisionSize;
	FVector2D m_MaxVelocity;
	FVector2D m_Velocity;

	bool m_bIsFlying;
	bool m_bBlockCharacter;
	bool m_bCanBeFliedOver;
	bool m_bIsCharacter;
	bool m_bIsExplodable;
	bool m_bIsPushable;
};



class UInGameObjectComponent : public UActorComponent
{
	typedef UActorComponent Super;

public:
	void AddVelocity(FVector2D VelocityToAdd);

	void AddOnExplodedEvent(std::function<void()> Event);
	void OnExploded();

public:
	void BeginPlay() override;
	void TickComponent(float fDeltaTime) override;

public:
	FInGameObjectProperty m_InGameObjectProperty;

private:
	vector<std::function<void()>> m_OnExplodedEvents;

};

