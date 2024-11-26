#pragma once
#include "GameLevelBase.h"

class BP_GameStage_Village_2 : public UGameLevelBase
{
public:
	// Constructors and Overrides
	BP_GameStage_Village_2();

	virtual void CheckGameFinished() override;
};

