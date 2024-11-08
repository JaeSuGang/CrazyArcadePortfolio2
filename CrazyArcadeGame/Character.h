#pragma once
#include "KmEngine/Pawn.h"


class ACharacter : public APawn
{
	typedef APawn Super;

public:
	void SetCharacterName(string strCharacterName);
	string GetCharacterName();
	void Move(FVector2D Direction);
	void Idle(FVector2D Direction);
	void TryPutBomb();

public:
	void OnAIPossessed() override;
	void OnPlayerPossessed() override;
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
	void BeginPlay() override;

public:
	ACharacter();

private:
	string m_strCharacterName;
	bool m_bIsAlreadyMoving;

};

