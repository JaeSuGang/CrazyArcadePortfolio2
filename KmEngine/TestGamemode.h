#pragma once
#include "Gamemode.h"
class ATestGamemode : public AGamemode
{
	typedef AGamemode Super;
	friend class ATestGamemode;
	friend class UTestGameInstance;

protected:
	void Tick(float fDeltaTime) override;
	void Initialize() override;
	void BeginPlay() override;

};

