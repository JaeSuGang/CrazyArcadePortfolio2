#pragma once
#include "KmEngine/Actor.h"
#include "Explodable.h"
#include "InGameProperty.h"

class ACharacter;

class ABlock : public AActor, public FInGameProperty, public IExplodable
{
	typedef AActor Super;

public:
	void PlayFadeAnimation();
	virtual void OnPushed(FVector2D Direction);

public:
	void SetAccumulatedPushedTime(float fTime);
	void SetPassable(bool bPassable);
	void SetHidable(bool bHidable);
	void SetBreakable(bool bBreakable);
	void SetPushable(bool bPushable);
	bool GetPushable() const;
	bool GetBreakable() const;
	bool GetHidable() const;
	float GetAccumulatedPushedTime() const;
	bool GetPassable() const;
	void AddAccumulatedPushedTime(float fTime);

public:
	void OnExploded() override;
	void BeginPlay() override;
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;

public:
	void Release();
	~ABlock();
	ABlock();

protected:
	FVector2D m_DestinationPos;
	float m_fAccumulatedPushedTime;

	bool m_bIsBreakable;
	bool m_bIsMoving;
	bool m_bIsPassable;
	bool m_bIsPushable;
	bool m_bIsHidable;
};

