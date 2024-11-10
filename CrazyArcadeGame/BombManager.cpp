#include "stdafx.h"
#include "KmEngine/Engine.h"
#include "KmEngine/Actor.h"
#include "BombManager.h"
#include "SpawnManager.h"
#include "MovementManager.h"
#include "WallComponent.h"
#include "AxisAlignedBoundingBox.h"
#include "InGameObjectComponent.h"

bool UBombManager::TryPutBomb(int nTileIndex)
{
	UMovementManager* MovementManager = GEngine->GetGameInstance()->GetGameInstanceSubsystem<UMovementManager>();

	FVector2D BombSpawnPos = TileIndexToVector(nTileIndex);
	FAxisAlignedBoundingBox BombSpawnAABB = { BombSpawnPos , TileWidth / 2, TileHeight / 2 };

	for (AActor* WallActor : MovementManager->m_Walls)
	{
		UInGameObjectComponent* WallInGameObjectComponent = WallActor->GetComponentByClass<UInGameObjectComponent>();
		FAxisAlignedBoundingBox WallAABB = {
			WallActor->GetPosition(),
			WallInGameObjectComponent->m_InGameObjectProperty.m_CollisionSize.X / 2,
			WallInGameObjectComponent->m_InGameObjectProperty.m_CollisionSize.Y / 2 };

		if (BombSpawnAABB.GetIsCollidedWith(WallAABB))
		{
			return false;
		}
	}

	this->ForcePutBomb(nTileIndex);
	return true;
}

void UBombManager::ForcePutBomb(int nTileIndex)
{
	USpawnManager* SpawnManager = GEngine->GetGameInstance()->GetGameInstanceSubsystem<USpawnManager>();
	SpawnManager->SpawnBomb(TileIndexToVector(nTileIndex));
}

void UBombManager::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);


}
