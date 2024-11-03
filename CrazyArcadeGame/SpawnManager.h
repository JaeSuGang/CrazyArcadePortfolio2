#pragma once
#include "KmEngine/GameInstanceSubsystem.h"
#include "KmBase/Vector.h"

class USpawnManager : public UGameInstanceSubsystem
{
public:
	void SpawnPlayer(string strCharacterName, FVector2D PositionVector);
	void SpawnPlayerController();
};

