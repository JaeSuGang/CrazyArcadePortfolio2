#pragma once
#include "KmEngine/Actor.h"
#include "Explodable.h"
#include "InGameProperty.h"

enum class EItemCode
{
	BombCount,
	BombRange,
	Speed,
	End
};

class APowerUpItem : public AActor, public IExplodable, public FInGameProperty
{
	typedef AActor Super;

public:
	void SetItemCode(EItemCode ItemCode);
	EItemCode GetItemCode() const;

public:
	void OnExploded() override;
	void BeginPlay() override;
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;

public:
	void Release();
	~APowerUpItem();

private:
	EItemCode m_ItemCode;

};
