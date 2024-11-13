#pragma once
#include "KmEngine/Pawn.h"
#include "Explodable.h"
#include "Hidable.h"
#include "InGameProperty.h"

class ACharacter : public APawn, public FInGameProperty, public IExplodable, public IHidable
{
	typedef APawn Super;

public:
	void Move(FVector2D Direction);
	void Idle(FVector2D Direction);
	void TryPutBomb();

public:
	void SetBombLeft(int nCount);
	void SetBombRange(int nRange);
	void SetCharacterName(string strCharacterName);

	int GetBombLeft() const;
	int GetBombRange() const;
	string GetCharacterName() const;

public:
	void CheckAndHide() override;
	void OnExploded() override;
	void OnAIPossessed() override;
	void OnPlayerPossessed() override;
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
	void BeginPlay() override;

public:
	void Release();
	ACharacter();
	~ACharacter();

protected:
	string m_strCharacterName;

	float m_fSpeed;

	int m_nBombLeft;
	int m_nBombRange;
};

