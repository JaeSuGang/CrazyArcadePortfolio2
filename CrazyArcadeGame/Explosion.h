#pragma once
#include "KmEngine/Actor.h"
#include "InGameProperty.h"

class AExplosion : public AActor, public FInGameProperty
{
	typedef AActor Super;

public:
	void SetTimer(float fTime);
	float GetTimer() const;

public:
	virtual void BeginPlay();
	virtual void Tick(float fDeltaTime);
	virtual void LateTick(float fDeltaTime);

public:
	void Release();
	~AExplosion();

private:
	float m_fTimer;
};

