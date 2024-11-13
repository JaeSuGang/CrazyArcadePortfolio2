#pragma once
#include "KmEngine/Actor.h"
#include "Explodable.h"
#include "InGameProperty.h"

enum class EItemCode
{
	None,
	BombCount,
	BombRange
};

class APowerUpItem : public AActor, public FInGameProperty, public IExplodable
{
	typedef AActor Super;

public:
	void OnExploded() override;
	void BeginPlay() override;
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;

private:
	EItemCode m_nItemCode;

};
