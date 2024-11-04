#pragma once
#include "KmEngine/GameInstanceSubsystem.h"
#include "stdafx.h"

class APawn;

class UAIManager : public UGameInstanceSubsystem
{
	typedef UGameInstanceSubsystem Super;

public:
	void AddAIPawn(APawn* Pawn);
	void RemoveAIPawn(APawn* Pawn);
	void ClearAIPawns();

public:
	void Tick(float fDeltaTime) override;

private:
	unordered_set<APawn*> m_AIPawns;
};

