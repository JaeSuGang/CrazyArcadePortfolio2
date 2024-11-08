#include "stdafx.h"
#include "KmEngine/Engine.h"
#include "KmEngine/Actor.h"
#include "BombManager.h"
#include "SpawnManager.h"
#include "MovementManager.h"
#include "WallComponent.h"

void UBombManager::TryPutBomb(FVector2D BombPosition)
{
	UMovementManager* MovementManager = GEngine->GetGameInstance()->GetGameInstanceSubsystem<UMovementManager>();

	for (UWallComponent* WallComponent : MovementManager->GetWalls())
	{
		AActor* WallActor = WallComponent->GetOwner();
		FVector2D WallActorPos = WallActor->GetPosition();

		if (BombPosition.X > WallActorPos.X - 30.0f &&
			BombPosition.X < WallActorPos.X + 30.0f &&
			BombPosition.Y > WallActorPos.Y - 30.0f &&
			BombPosition.Y < WallActorPos.Y + 30.0f)
		{
			return;
		}
	}

	PutBomb(VectorToTileIndex(BombPosition));
}

void UBombManager::PutBomb(int nTileIndex)
{
	USpawnManager* SpawnManager = GEngine->GetGameInstance()->GetGameInstanceSubsystem<USpawnManager>();
	SpawnManager->SpawnBomb(TileIndexToVector(nTileIndex));
}

void UBombManager::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);


}
