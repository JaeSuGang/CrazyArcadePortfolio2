#pragma once
#include "Actor.h"

class ATestPlayer : public AActor
{
	typedef AActor Super;

public:
	// AActor��(��) ���� ��ӵ�
	void Initialize() override;
	void Tick(float fDeltaTime) override;
	void BeginPlay() override;
};

