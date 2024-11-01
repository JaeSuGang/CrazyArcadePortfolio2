#pragma once
#include "KmEngine/Actor.h"


class ACharacter : public AActor
{
	typedef AActor Super;

public:
	void Move(FVector2D Direction);
	void Idle(FVector2D Direction);

public:
	void Initialize() override;
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
	void BeginPlay() override;

private:
	string m_strCharacterName;
	bool m_bIsAlreadyMoving;

};

