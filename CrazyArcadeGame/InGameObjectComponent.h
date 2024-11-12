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
	FVector2D m_DestinationPos;

	float m_fTimer;
	float m_fElapsedTimeAfterExplosion;
	float m_fAccumulatedPushedTime;
	float m_fSpeed;

	int m_nBombLeft;
	int m_nBombRange;

	bool m_bIsAlreadyExploded;
	bool m_bIsAlreadyMoving;
	bool m_bIsHidablePlace;
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
	void CheckAndHandleHidable();

public:
	void AddVelocity(FVector2D VelocityToAdd);
	void AddOnExplodedEvent(std::function<void()> Event);
	void OnExploded();
	void OnPushed(FVector2D Direction);

private:
	void OnPushed_MovableBlock(FVector2D Direction);
	void OnExploded_Character();
	void OnExploded_Bomb();
	void OnExploded_Block();
	void OnExploded_Hidable();
	void Tick_Explosion(float fDeltaTime);
	void Tick_Bomb(float fDeltaTime);
	void Tick_Character(float fDeltaTime);
	void Tick_PushableBlock(float fDeltaTime);

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
	vector<std::function<void(FVector2D)>> m_OnPushedEvents;

};

