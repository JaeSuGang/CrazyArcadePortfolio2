#pragma once
#include "Block.h"
#include "Explodable.h"
#include "Hidable.h"

class ABomb : public ABlock, public IExplodable, public IHidable
{
	typedef ABlock Super;

public:
	void SetTimer(float fTime);
	void SetBombRange(int nRange);
	void SetSpawner(ACharacter* Spawner);

	ACharacter* GetSpawner() const;
	float GetTimer() const;
	int GetBombRange() const;

public:
	void CheckAndHide() override;
	void OnExploded() override;
	void BeginPlay() override;
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;

public:
	void Release();
	~ABomb();

protected:
	ACharacter* m_Spawner;
	float m_fTimer;
	int m_nBombRange;
};

