#pragma once
#include "KmEngine/Level.h"

class UTestLevel : public ULevel
{
	typedef ULevel Super;

public:
	void Tick(float fDeltaTime) override;
	void BeginPlay() override;
	void Initialize() override;
};

