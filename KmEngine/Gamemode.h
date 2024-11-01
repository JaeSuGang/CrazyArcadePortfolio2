#pragma once
#include "Actor.h"

class AGamemode : public AActor
{
	typedef AActor Super;
	friend class ULevel;
	friend class UEngine;

protected:

	// AActor��(��) ���� ��ӵ�
	void Initialize() override;
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
	void BeginPlay() override;
};

