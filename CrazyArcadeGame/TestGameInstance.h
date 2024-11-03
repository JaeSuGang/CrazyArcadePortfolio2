#pragma once
#include "KmEngine/GameInstance.h"
class UTestGameInstance : public UGameInstance
{
	typedef UGameInstance Super;

public:
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
	void BeginPlay() override;
};

