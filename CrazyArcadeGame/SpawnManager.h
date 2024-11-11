#pragma once
#include "KmEngine/GameInstanceSubsystem.h"
#include "KmBase/Vector.h"

class APlayerController;
class AAIController;
class ACharacter;
class AGameUI;
class FTilemap;

class USpawnManager : public UGameInstanceSubsystem
{
	typedef UGameInstanceSubsystem Super;

public:
	void GenerateWallTile(int nTileIndex, int nValue, int nGroundTileValue);
	void GenerateGroundTile(int nTileIndex, int nValue);
	void GenerateTilemap(FTilemap* TilemapStruct);
	AGameUI* SpawnGameUI(string strImagePath, FVector2D PositionVector);
	ACharacter* SpawnBazzi(FVector2D PositionVector);
	ACharacter* SpawnDao(FVector2D PositionVector);
	ACharacter* SpawnCappi(FVector2D PositionVector);
	ACharacter* SpawnMarid(FVector2D PositionVector);
	AActor* SpawnBomb(FVector2D PositionVector, AActor* Spawner);
	AActor* SpawnExplosion(FVector2D PositionVector, int nDirection, bool bIsEnd);
	APlayerController* SpawnPlayerController();
	AAIController* SpawnCharacterAIController();

public:
	void Tick(float fDeltaTime) override;

private:
	FTilemap* m_Tilemap;
};

