#pragma once
#include "GameInstance.h"
class UTestGameInstance : public UGameInstance
{
	typedef UGameInstance Super;

public:
	void Tick(float fDeltaTime) override;
	void BeginPlay() override;
	void Initialize() override;
};

