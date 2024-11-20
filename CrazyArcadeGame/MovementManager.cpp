#include "stdafx.h"
#include "KmEngine/Level.h"
#include "MovementManager.h"
#include "MovableComponent.h"
#include "KmEngine/Actor.h"
#include "KmEngine/RenderComponent.h"
#include "WallComponent.h"
#include "AxisAlignedBoundingBox.h"
#include "Block.h"
#include "Character.h"
#include "PowerUpItem.h"

AActor* UMovementManager::GetActorInAABB(FAxisAlignedBoundingBox AABB) const
{
	for (AActor* Actor : GetActiveLevel()->m_Actors)
	{
		if (AABB.GetIsCollidedWith(Actor->GetPosition()))
			return Actor;
	}

	return nullptr;
}

ABlock* UMovementManager::GetBlockInAABB(FAxisAlignedBoundingBox AABB) const
{
	FAxisAlignedBoundingBox WallAABB;
	for (ABlock* BlockActor : m_Blocks)
	{
		WallAABB = { BlockActor->GetPosition(),
			BlockActor->m_CollisionSize.X / 2,
			BlockActor->m_CollisionSize.Y / 2};
		if (AABB.GetIsCollidedWith(WallAABB))
			return BlockActor;
	}

	return nullptr;
}

AActor* UMovementManager::GetMovableInAABB(FAxisAlignedBoundingBox AABB) const
{
	for (AActor* Actor : m_Characters)
	{
		if (AABB.GetIsCollidedWith(Actor->GetPosition()))
			return Actor;
	}

	return nullptr;
}

AActor* UMovementManager::GetHidablePlaceInAABB(FAxisAlignedBoundingBox AABB) const
{
	for (AActor* Actor : m_HidableBlocks)
	{
		if (AABB.GetIsCollidedWith(Actor->GetPosition()))
			return Actor;
	}

	return nullptr;
}

AActor* UMovementManager::GetIsInHidable(AActor* ActorToCheck)
{
	FVector2D ActorPos = ActorToCheck->GetPosition();
	FAxisAlignedBoundingBox HidableAABB = { FVector2D::Zero, TILE_WIDTH / 2, TILE_HEIGHT / 2 };

	for (AActor* HidablePlaceActor : m_HidableBlocks)
	{
		HidableAABB.m_Center = HidablePlaceActor->GetPosition();
		if (HidableAABB.GetIsCollidedWith(ActorPos))
			return HidablePlaceActor;
	}

	return nullptr;
}

void UMovementManager::DebugRender()
{
	URenderManager* RenderManager = GEngine->GetEngineSubsystem<URenderManager>();
	HDC hDC = RenderManager->GetBackBufferHandle();

	for (ACharacter* CharacterActor : m_Characters)
	{
		FAxisAlignedBoundingBox CharacterAABB = {
			CharacterActor->GetPosition(),
			CharacterActor->m_CollisionSize.X / 2,
			CharacterActor->m_CollisionSize.Y / 2};
		Rectangle(hDC, 
			(int)(CharacterAABB.m_Center.X - CharacterAABB.m_WidthRadius),
			(int)(CharacterAABB.m_Center.Y - CharacterAABB.m_HeightRadius),
			(int)(CharacterAABB.m_Center.X + CharacterAABB.m_WidthRadius),
			(int)(CharacterAABB.m_Center.Y + CharacterAABB.m_HeightRadius));
		string strPos = "[" +
			std::to_string((int)(CharacterAABB.m_Center.X)) + ", " +
			std::to_string((int)(CharacterAABB.m_Center.Y)) + "]";
		TextOutA(hDC, (int)(CharacterAABB.m_Center.X), (int)(CharacterAABB.m_Center.Y), strPos.data(), (int)strPos.size());
	}
}

void UMovementManager::Reset()
{
	m_Characters.clear();
	m_Blocks.clear();
}

void UMovementManager::AddHidableBlock(ABlock* HidablePlaceActor)
{
	m_HidableBlocks.insert(HidablePlaceActor);
}

void UMovementManager::AddCharacter(ACharacter* Movable)
{
	m_Characters.insert(Movable);
}

void UMovementManager::AddBlock(ABlock* Wall)
{
	m_Blocks.insert(Wall);
}

void UMovementManager::AddPowerUpItem(APowerUpItem* Item)
{
	m_PowerUpItems.insert(Item);
}

void UMovementManager::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	ULevel* ActiveLevel = GetActiveLevel();

	for (ACharacter* CharacterActor : m_Characters)
	{
		FVector2D OriginalPos = CharacterActor->GetPosition();
		if (CharacterActor->m_Velocity != FVector2D::Zero)
		{
			URenderComponent* RenderComponent = CharacterActor->GetComponentByClass<URenderComponent>();

			FVector2D VelocityToApplyInFrame = CharacterActor->m_Velocity * fDeltaTime;
			VelocityToApplyInFrame.X = VelocityToApplyInFrame.X > MAX_SPEED_PER_FRAME ? MAX_SPEED_PER_FRAME : VelocityToApplyInFrame.X;
			VelocityToApplyInFrame.X = VelocityToApplyInFrame.X < - MAX_SPEED_PER_FRAME ? - MAX_SPEED_PER_FRAME : VelocityToApplyInFrame.X;
			VelocityToApplyInFrame.Y = VelocityToApplyInFrame.Y > MAX_SPEED_PER_FRAME ? MAX_SPEED_PER_FRAME : VelocityToApplyInFrame.Y;
			VelocityToApplyInFrame.Y = VelocityToApplyInFrame.Y < - MAX_SPEED_PER_FRAME ? - MAX_SPEED_PER_FRAME : VelocityToApplyInFrame.Y;


			FAxisAlignedBoundingBox DestinationAABB = {
				OriginalPos + VelocityToApplyInFrame,
				CharacterActor->m_CollisionSize.X / 2,
				CharacterActor->m_CollisionSize.Y / 2 };

			bool bAlreadyPushedWall = false;
			// 캐릭터가 블록에 닿음
			for (ABlock* BlockActor : m_Blocks)
			{
				if (BlockActor->GetPassable())
					continue;

				FAxisAlignedBoundingBox WallAABB = {
					BlockActor->GetPosition(),
					BlockActor->m_CollisionSize.X / 2,
					BlockActor->m_CollisionSize.Y / 2 };

				if (DestinationAABB.GetIsCollidedWith(WallAABB))
				{
					DestinationAABB = DestinationAABB.CalculateCorrectPos(OriginalPos, WallAABB);
					if (!bAlreadyPushedWall)
					{
						BlockActor->AddAccumulatedPushedTime(fDeltaTime);
						if (BlockActor->GetAccumulatedPushedTime() > 0.25f)
						{
							BlockActor->OnPushed(VelocityToApplyInFrame.GetNormalized());
							bAlreadyPushedWall = true;
						}
					}
					bAlreadyPushedWall = true;
				}
			}

			// 캐릭터가 캐릭터에 닿음
			for (ACharacter* OtherCharacter : m_Characters)
			{
				if (CharacterActor == OtherCharacter)
					continue;

				if (DestinationAABB.GetIsCollidedWith(OtherCharacter->GetPosition()))
				{
					if (OtherCharacter->m_bIsAlreadyExploded)
						OtherCharacter->Die();
				}
			}

			// 캐릭터가 아이템에 닿음

			if (!CharacterActor->m_bIsAlreadyExploded)
			{
				for (APowerUpItem* PowerUpItem : m_PowerUpItems)
				{
					if (DestinationAABB.GetIsCollidedWith(PowerUpItem->GetPosition()))
					{
						switch (PowerUpItem->GetItemCode())
						{
						case EItemCode::BombCount:
							CharacterActor->SetBombLeft(CharacterActor->GetBombLeft() + 1);
							if (CharacterActor->GetBombLeft() > 6)
								CharacterActor->SetBombLeft(6);
							break;
						case EItemCode::BombRange:
							CharacterActor->SetBombRange(CharacterActor->GetBombRange() + 1);
							if (CharacterActor->GetBombRange() > 6)
								CharacterActor->SetBombRange(6);
							break;
						case EItemCode::Speed:
							CharacterActor->SetSpeed(CharacterActor->GetSpeed() + 40.0f);
							if (CharacterActor->GetSpeed() > CharacterActor->GetMaxSpeed())
								CharacterActor->SetSpeed(CharacterActor->GetMaxSpeed());
							break;
						}

						PowerUpItem->Destroy();
					}
				}
			}

			CharacterActor->CheckAndHide();
			CharacterActor->SetPosition(DestinationAABB.m_Center);
			CharacterActor->GetComponentByClass<URenderComponent>()->SetRenderPriority(VectorToRenderPriority(CharacterActor->GetPosition()));
			CharacterActor->m_Velocity = FVector2D::Zero;
		}
	}

}

UMovementManager::UMovementManager()
	:
	m_Characters{},
	m_Blocks{},
	m_hBrush{},
	m_hPen{}
{
}
