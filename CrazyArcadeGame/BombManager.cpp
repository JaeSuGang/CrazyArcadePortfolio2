#include "stdafx.h"
#include "KmEngine/Engine.h"
#include "KmEngine/Actor.h"
#include "KmEngine/Level.h"
#include "BombManager.h"
#include "SpawnManager.h"
#include "MovementManager.h"
#include "WallComponent.h"
#include "AxisAlignedBoundingBox.h"
#include "InGameObjectComponent.h"

void UBombManager::AddExplosion(AActor* ExplosionActor)
{
	m_Explosions.insert(ExplosionActor);
}

void UBombManager::RemoveExplosion(AActor* ExplosionActor)
{
	m_Explosions.erase(ExplosionActor);
}

bool UBombManager::TryPutBomb(int nTileIndex, AActor* Spawner)
{
	UMovementManager* MovementManager = GEngine->GetGameInstance()->GetGameInstanceSubsystem<UMovementManager>();

	FVector2D BombSpawnPos = TileIndexToVector(nTileIndex);
	FAxisAlignedBoundingBox BombSpawnAABB = { BombSpawnPos , TILE_WIDTH / 2, TILE_HEIGHT / 2 };

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

	this->ForcePutBomb(nTileIndex, Spawner);
	return true;
}

void UBombManager::ForcePutBomb(int nTileIndex, AActor* Spawner)
{
	USpawnManager* SpawnManager = GEngine->GetGameInstance()->GetGameInstanceSubsystem<USpawnManager>();
	SpawnManager->SpawnBomb(TileIndexToVector(nTileIndex), Spawner);
}

void UBombManager::Explode(int nTileIndex, int nRange)
{
	UMovementManager* MovementManager = GEngine->GetGameInstance()->GetGameInstanceSubsystem<UMovementManager>();
	USpawnManager* SpawnManager = GEngine->GetGameInstance()->GetGameInstanceSubsystem<USpawnManager>();

	FVector2D ExplosionCenterPos = TileIndexToVector(nTileIndex);

	FVector2D Directions[4] = { FVector2D::Up, FVector2D::Right, FVector2D::Down, FVector2D::Left };

	FAxisAlignedBoundingBox AABB { FVector2D::Zero, TILE_WIDTH / 2, TILE_HEIGHT / 2 };

	SpawnManager->SpawnExplosion(TileIndexToVector(nTileIndex), 0, true);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 1; j <= nRange; j++)
		{
			bool bSkipThisDirection = false;
			AABB.m_Center = ExplosionCenterPos + Directions[i] * (float)j * 60.0f;

			for (AActor* WallActor : MovementManager->m_Walls)
			{
				UInGameObjectComponent* WallInGameObjectComponent = WallActor->GetComponentByClass<UInGameObjectComponent>();
				if (AABB.GetIsCollidedWith(WallActor->GetPosition()))
				{
					bSkipThisDirection = true;

					if (WallInGameObjectComponent->m_InGameObjectProperty.m_bIsExplodable)
						WallInGameObjectComponent->OnExploded();
					break;
				}
			}

			if (bSkipThisDirection)
				break;
			else
			{
				bool bIsEnd = (j == nRange);
				SpawnManager->SpawnExplosion(AABB.m_Center, i+1, bIsEnd);
			}
		}
	}

}

void UBombManager::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);


	for (AActor* ExplosionActor : m_Explosions)
	{
		UInGameObjectComponent* ExplosionInGameObjectComponent = ExplosionActor->GetComponentByClass<UInGameObjectComponent>();
		FAxisAlignedBoundingBox ExplosionAABB = {
			ExplosionActor->GetPosition(),
			ExplosionInGameObjectComponent->m_InGameObjectProperty.m_CollisionSize.X / 2,
			ExplosionInGameObjectComponent->m_InGameObjectProperty.m_CollisionSize.Y / 2 };

		for (AActor* TargetActor : GetActiveLevel()->m_Actors)
		{
			UInGameObjectComponent* TargetInGameObjectComponent = TargetActor->GetComponentByClass<UInGameObjectComponent>();
			if (!TargetInGameObjectComponent)
				continue;

			if (ExplosionAABB.GetIsCollidedWith(TargetActor->GetPosition()))
			{
				TargetInGameObjectComponent->OnExploded();
			}
		}
	}
}
