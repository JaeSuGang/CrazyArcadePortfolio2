#pragma once
#include "KmEngine/GameInstanceSubsystem.h"
#include "KmBase/Vector.h"

class APlayerController;
class ACharacter;

class USpawnManager : public UGameInstanceSubsystem
{
public:
	ACharacter* SpawnCharacter(string strCharacterName, FVector2D PositionVector);
	APlayerController* SpawnPlayerController();
};

