#pragma once
#include "KmEngine/Actor.h"

enum class EItemCode
{
	None,
	BombCount,
	BombRange
};

class APowerUpItem : public AActor
{
	typedef AActor Super;

public:
	void BeginPlay() override;
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;

private:
	EItemCode m_nItemCode;
};
