#pragma once
#include "KmEngine/GameInstanceSubsystem.h"
#include "KmBase/Vector.h"

class APlayerController;
class ACharacter;
class AGameUI;

class USpawnManager : public UGameInstanceSubsystem
{
	typedef UGameInstanceSubsystem Super;

public:
	AGameUI* SpawnGameUI(string strImagePath, FVector2D PositionVector);
	ACharacter* SpawnCharacter(string strCharacterName, FVector2D PositionVector);
	APlayerController* SpawnPlayerController();

public:
	void Tick(float fDeltaTime) override;
};

