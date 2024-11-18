#pragma once
#include "KmEngine/Level.h"

class ULobbyLevel : public ULevel
{
	typedef ULevel Super;

public:



public:
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
	void BeginPlay() override;

};

