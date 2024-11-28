#pragma once
#include "KmEngine/Pawn.h"
#include "Explodable.h"
#include "Hidable.h"
#include "InGameProperty.h"

class ACharacter : public APawn, public FInGameProperty, public IExplodable, public IHidable
{
	typedef APawn Super;

public:
	void Die();
	void Move(FVector2D Direction);
	void Idle(FVector2D Direction);
	void TryPutBomb();


public:
	void SetMaxStat();
	void SwitchInvincible();
	void SwitchNoclip();
	void SetBombLeft(int nCount);
	void SetBombRange(int nRange);
	void SetCharacterName(string strCharacterName);
	void SetSpeed(float fSpeed);
	void SetMaxSpeed(float fSpeed);

	float GetMaxSpeed() const;
	float GetSpeed() const;
	int GetBombLeft() const;
	int GetBombRange() const;
	string GetCharacterName() const;

public:
	void CheckAndHide() override;
	void OnExploded() override;
	void OnAIPossessed() override;
	void OnAIUnpossessed() override;
	void OnPlayerPossessed() override;
	void OnPlayerUnpossessed() override;
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
	void BeginPlay() override;
	void OnDebug() override;

public:
	void Release();
	ACharacter();
	~ACharacter();

public:
	ACCESSORS_ALL(bool, bIsNoclip);

protected:
	string m_strCharacterName;
	float m_fElapsedTimeAfterDeath;
	float m_fSpeed;
	float m_fMaxSpeed;
	bool m_bIsDead;
	bool bIsNoclip;
	bool bIsInvincible;
	int m_nBombLeft;
	int m_nBombRange;
};

