#pragma once
#include "KmEngine/GameInstanceSubsystem.h"
#include "KmBase/Vector.h"

enum class EItemCode;
class APlayerController;
class AAIController;
class ACharacterAIController;
class ACharacter;
class AGameUI;
class ABlock;
class ABomb;
class APowerUpItem;
class AExplosion;
class FTilemap;

class USpawnManager : public UGameInstanceSubsystem
{
	typedef UGameInstanceSubsystem Super;

public:
	ABlock* GenerateVoidWallTile(FVector2D Pos);
	void GenerateWallTile(FVector2D Pos, int nTileValue, int nGroundTileValue);
	void GenerateWallTile(int nTileIndex, int nTileValue, int nGroundTileValue);
	void GenerateGroundTile(int nTileIndex, int nValue);
	void GenerateTilemap(FTilemap* TilemapStruct);
	AGameUI* SpawnGameUI(string strImagePath, FVector2D PositionVector);
	ACharacter* SpawnBazzi(FVector2D PositionVector);
	ACharacter* SpawnDao(FVector2D PositionVector);
	ACharacter* SpawnCappi(FVector2D PositionVector);
	ACharacter* SpawnMarid(FVector2D PositionVector);
	APowerUpItem* SpawnRandomItem(FVector2D PositionVector);
	APowerUpItem* SpawnItem(FVector2D PositionVector, EItemCode ItemCode);
	ABomb* SpawnBomb(FVector2D PositionVector, ACharacter* Spawner);
	AExplosion* SpawnExplosion(FVector2D PositionVector, int nDirection, bool bIsEnd);
	AExplosion* SpawnExplosion(FVector2D PositionVector, int nDirection, float fDelayTimer, bool bIsEnd);
	APlayerController* SpawnPlayerController();
	ACharacterAIController* SpawnCharacterAIController();

public:
	void Tick(float fDeltaTime) override;

private:
	FTilemap* m_Tilemap;
};

