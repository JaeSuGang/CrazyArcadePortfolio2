#pragma once
#include "KmEngine/ActorComponent.h"

struct FInGameObjectProperty
{
public:
	static const FInGameObjectProperty Character;
	static const FInGameObjectProperty Bomb;
	static const FInGameObjectProperty Explosion;
	static const FInGameObjectProperty HidableWall;
	static const FInGameObjectProperty MovableWall;
	static const FInGameObjectProperty ExplodableWall;
	static const FInGameObjectProperty NonExplodableWall;

public:
	AActor* m_Spawner;

	FVector2D m_CollisionSize;
	FVector2D m_Velocity;

	float m_fTimer;
	float m_fElapsedTimeAfterExplosion;
	float m_fSpeed;

	int m_nBombLeft;
	int m_nBombRange;

	bool m_bIsAlreadyExploded;
	bool m_bIsExplosionCenter;
	bool m_bIsExplosion;
	bool m_bIsBomb;
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
	void PlayFadeAnimation();
	void AddVelocity(FVector2D VelocityToAdd);
	void AddOnExplodedEvent(std::function<void()> Event);
	void OnExploded();

private:
	void OnExploded_Bomb();
	void OnExploded_Block();

public:
	void BeginPlay() override;
	void TickComponent(float fDeltaTime) override;

public:
	void Release();
	~UInGameObjectComponent();

public:
	FInGameObjectProperty m_InGameObjectProperty;

private:
	vector<std::function<void()>> m_OnExplodedEvents;

};

