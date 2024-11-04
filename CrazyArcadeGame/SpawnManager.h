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
	//AActor* GenerateTileMap(FTileMapData TileMapData);
	AGameUI* SpawnGameUI(string strImagePath, FVector2D PositionVector);
	ACharacter* SpawnBazzi(FVector2D PositionVector);
	ACharacter* SpawnDao(FVector2D PositionVector);
	ACharacter* SpawnCappi(FVector2D PositionVector);
	ACharacter* SpawnMarid(FVector2D PositionVector);
	APlayerController* SpawnPlayerController();

public:
	void Tick(float fDeltaTime) override;
};

