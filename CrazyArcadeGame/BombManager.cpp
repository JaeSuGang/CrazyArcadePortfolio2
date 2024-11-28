#include "stdafx.h"
#include "KmEngine/Engine.h"
#include "KmEngine/Actor.h"
#include "KmEngine/Level.h"
#include "BombManager.h"
#include "SpawnManager.h"
#include "MovementManager.h"
#include "WallComponent.h"
#include "AxisAlignedBoundingBox.h"
#include "Explosion.h"
#include "Block.h"
#include "Bomb.h"
#include "InGameProperty.h"
#include "KmEngine/SoundManager.h"

void UBombManager::AddBlock(ABlock* BlockActor)
{
	m_Blocks.insert(BlockActor);
}

void UBombManager::AddExplodable(IExplodable* Explodable)
{
	m_Explodables.insert(Explodable);
}

void UBombManager::AddCharacter(ACharacter* CharacterActor)
{
	m_Characters.insert(CharacterActor);
}

void UBombManager::AddExplosion(AExplosion* ExplosionActor)
{
	m_Explosions.insert(ExplosionActor);
}

void UBombManager::RemoveExplosion(AExplosion* ExplosionActor)
{
	m_Explosions.erase(ExplosionActor);
}

bool UBombManager::TryPutBomb(int nTileIndex, ACharacter* Spawner)
{
	UMovementManager* MovementManager = GEngine->GetGameInstance()->GetSubsystem<UMovementManager>();

	FVector2D BombSpawnPos = TileIndexToVector(nTileIndex);
	FAxisAlignedBoundingBox BombSpawnAABB = { BombSpawnPos , TILE_WIDTH / 2, TILE_HEIGHT / 2 };

	for (ABlock* WallActor : MovementManager->m_Blocks)
	{
		FAxisAlignedBoundingBox WallAABB = {
			WallActor->GetPosition(),
			WallActor->m_CollisionSize.X / 2,
			WallActor->m_CollisionSize.Y / 2 };

		if (BombSpawnAABB.GetIsCollidedWith(WallAABB))
		{
			if (!WallActor->GetPassable())
				return false;
		}
	}

	this->ForcePutBomb(nTileIndex, Spawner);
	return true;
}

void UBombManager::ForcePutBomb(int nTileIndex, ACharacter* Spawner)
{
	USpawnManager* SpawnManager = GEngine->GetGameInstance()->GetSubsystem<USpawnManager>();
	ABomb* BombActor = SpawnManager->SpawnBomb(TileIndexToVector(nTileIndex), Spawner);
	BombActor->CheckAndHide();
}

void UBombManager::Explode(int nTileIndex, int nRange)
{
	UMovementManager* MovementManager = GEngine->GetGameInstance()->GetSubsystem<UMovementManager>();
	USpawnManager* SpawnManager = GEngine->GetGameInstance()->GetSubsystem<USpawnManager>();
	USoundManager* SoundManager = GEngine->GetEngineSubsystem<USoundManager>();
	SoundManager->Play("Resources\\Sound\\explosion.wav");

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

			for (ABlock* WallActor : m_Blocks)
			{
				if (!WallActor->GetPassable() && AABB.GetIsCollidedWith(WallActor->GetPosition()))
				{
					bSkipThisDirection = true;
					WallActor->OnExploded();
					break;
				}
			}

			if (bSkipThisDirection)
				break;
			else
			{
				bool bIsEnd = (j == nRange);
				SpawnManager->SpawnExplosion(AABB.m_Center, i+1, j * 0.02f, bIsEnd);
			}
		}
	}

}

void UBombManager::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	m_fAccumulatedDeltaTime += fDeltaTime;

	if (m_fAccumulatedDeltaTime > 0.05f)
	{
		m_fAccumulatedDeltaTime = 0.0f;

		FAxisAlignedBoundingBox TileSizeCollider = { FVector2D::Zero, TILE_WIDTH / 2, TILE_HEIGHT / 2 };

		for (AExplosion* ExplosionActor : m_Explosions)
		{
			TileSizeCollider.m_Center = ExplosionActor->GetPosition();

			for (IExplodable* Explodable : m_Explodables)
			{
				AActor* ExplodableActor = dynamic_cast<AActor*>(Explodable);
				FInGameProperty* ExplodableActorProperty = dynamic_cast<FInGameProperty*>(Explodable);
				if (!ExplodableActorProperty->m_bIsAlreadyExploded && TileSizeCollider.GetIsCollidedWith(ExplodableActor->GetPosition()))
				{
					Explodable->OnExploded();
				}
			}
		}
	}
}
