#include "stdafx.h"
#include "KmEngine/Level.h"
#include "MovementManager.h"
#include "MovableComponent.h"
#include "KmEngine/Actor.h"
#include "KmEngine/RenderComponent.h"
#include "WallComponent.h"
#include "AxisAlignedBoundingBox.h"
#include "InGameObjectComponent.h"

AActor* UMovementManager::GetActorInAABB(FAxisAlignedBoundingBox AABB) const
{
	for (AActor* Actor : GetActiveLevel()->m_Actors)
	{
		if (AABB.GetIsCollidedWith(Actor->GetPosition()))
			return Actor;
	}

	return nullptr;
}

AActor* UMovementManager::GetWallInAABB(FAxisAlignedBoundingBox AABB) const
{
	FAxisAlignedBoundingBox WallAABB;
	for (AActor* Actor : m_Walls)
	{
		UInGameObjectComponent* InGameObjectComponent = Actor->GetComponentByClass<UInGameObjectComponent>();
		WallAABB = { Actor->GetPosition(),
			InGameObjectComponent->m_InGameObjectProperty.m_CollisionSize.X / 2,
			InGameObjectComponent->m_InGameObjectProperty.m_CollisionSize.Y / 2};
		if (AABB.GetIsCollidedWith(WallAABB))
			return Actor;
	}

	return nullptr;
}

AActor* UMovementManager::GetMovableInAABB(FAxisAlignedBoundingBox AABB) const
{
	for (AActor* Actor : m_Movables)
	{
		if (AABB.GetIsCollidedWith(Actor->GetPosition()))
			return Actor;
	}

	return nullptr;
}

AActor* UMovementManager::GetHidablePlaceInAABB(FAxisAlignedBoundingBox AABB) const
{
	for (AActor* Actor : m_HidablePlaces)
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

	for (AActor* HidablePlaceActor : m_HidablePlaces)
	{
		HidableAABB.m_Center = HidablePlaceActor->GetPosition();
		if (HidableAABB.GetIsCollidedWith(ActorPos))
			return HidablePlaceActor;
	}

	return nullptr;
}

void UMovementManager::EnableDebugRender()
{
	URenderManager* RenderManager = GEngine->GetEngineSubsystem<URenderManager>();
	RenderManager->AddCustomRenderEvent(std::bind(&UMovementManager::DebugRender, this));

	HDC hDC = RenderManager->GetBackBufferHandle();
	HPEN hGreenPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	HBRUSH hHollowBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	HPEN hOldPen = (HPEN)SelectObject(hDC, hGreenPen);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hHollowBrush);
}

void UMovementManager::DebugRender()
{
	URenderManager* RenderManager = GEngine->GetEngineSubsystem<URenderManager>();
	HDC hDC = RenderManager->GetBackBufferHandle();

	for (AActor* MovableActor : m_Movables)
	{
		UInGameObjectComponent* InGameObjectComponent = MovableActor->GetComponentByClass<UInGameObjectComponent>();
		FAxisAlignedBoundingBox MovableAABB = {
			MovableActor->GetPosition(),
			InGameObjectComponent->m_InGameObjectProperty.m_CollisionSize.X / 2,
			InGameObjectComponent->m_InGameObjectProperty.m_CollisionSize.Y / 2};
		Rectangle(hDC, 
			(int)(MovableAABB.m_Center.X - MovableAABB.m_WidthRadius),
			(int)(MovableAABB.m_Center.Y - MovableAABB.m_HeightRadius),
			(int)(MovableAABB.m_Center.X + MovableAABB.m_WidthRadius),
			(int)(MovableAABB.m_Center.Y + MovableAABB.m_HeightRadius));
		string strPos = "[" +
			std::to_string((int)(MovableAABB.m_Center.X)) + ", " +
			std::to_string((int)(MovableAABB.m_Center.Y)) + "]";
		TextOutA(hDC, (int)(MovableAABB.m_Center.X), (int)(MovableAABB.m_Center.Y), strPos.data(), (int)strPos.size());
	}
}

void UMovementManager::Reset()
{
	m_Movables.clear();
	m_Walls.clear();
}

void UMovementManager::AddHidablePlace(AActor* HidablePlaceActor)
{
	m_HidablePlaces.insert(HidablePlaceActor);
}

void UMovementManager::AddMovable(AActor* Movable)
{
	m_Movables.insert(Movable);
}

void UMovementManager::AddWall(AActor* Wall)
{
	m_Walls.insert(Wall);
}

void UMovementManager::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	ULevel* ActiveLevel = GetActiveLevel();

	for (AActor* MovableActor : m_Movables)
	{
		UInGameObjectComponent* MovableInGameObjectComponent = MovableActor->GetComponentByClass<UInGameObjectComponent>();
		if (!MovableInGameObjectComponent)
			continue;


		FVector2D OriginalPos = MovableActor->GetPosition();
		FInGameObjectProperty& InGameObjectProperty = MovableInGameObjectComponent->m_InGameObjectProperty;
		if (InGameObjectProperty.m_Velocity != FVector2D::Zero)
		{
			URenderComponent* RenderComponent = MovableActor->GetComponentByClass<URenderComponent>();

			FVector2D VelocityToApplyInFrame = InGameObjectProperty.m_Velocity * fDeltaTime;
			VelocityToApplyInFrame.X = VelocityToApplyInFrame.X > MAX_SPEED_PER_FRAME ? MAX_SPEED_PER_FRAME : VelocityToApplyInFrame.X;
			VelocityToApplyInFrame.X = VelocityToApplyInFrame.X < - MAX_SPEED_PER_FRAME ? - MAX_SPEED_PER_FRAME : VelocityToApplyInFrame.X;
			VelocityToApplyInFrame.Y = VelocityToApplyInFrame.Y > MAX_SPEED_PER_FRAME ? MAX_SPEED_PER_FRAME : VelocityToApplyInFrame.Y;
			VelocityToApplyInFrame.Y = VelocityToApplyInFrame.Y < - MAX_SPEED_PER_FRAME ? - MAX_SPEED_PER_FRAME : VelocityToApplyInFrame.Y;


			FAxisAlignedBoundingBox DestinationAABB = {
				OriginalPos + VelocityToApplyInFrame,
				InGameObjectProperty.m_CollisionSize.X / 2,
				InGameObjectProperty.m_CollisionSize.Y / 2 };

			bool bAlreadyPushedWall = false;
			for (AActor* WallActor : m_Walls)
			{
				UInGameObjectComponent* WallInGameObjectComponent = WallActor->GetComponentByClass<UInGameObjectComponent>();
				FAxisAlignedBoundingBox WallAABB = {
					WallActor->GetPosition(),
					WallInGameObjectComponent->m_InGameObjectProperty.m_CollisionSize.X / 2,
					WallInGameObjectComponent->m_InGameObjectProperty.m_CollisionSize.Y / 2 };

				if (DestinationAABB.GetIsCollidedWith(WallAABB))
				{
					DestinationAABB = DestinationAABB.CalculateCorrectPos(OriginalPos, WallAABB);
					if (!bAlreadyPushedWall)
					{
						WallInGameObjectComponent->m_InGameObjectProperty.m_fAccumulatedPushedTime += fDeltaTime;
						if (WallInGameObjectComponent->m_InGameObjectProperty.m_fAccumulatedPushedTime > 0.25f)
						{
							WallInGameObjectComponent->OnPushed(VelocityToApplyInFrame.GetNormalized());
							bAlreadyPushedWall = true;
						}
					}
					bAlreadyPushedWall = true;
				}
			}

			MovableInGameObjectComponent->CheckAndHandleHidable();

			MovableActor->SetPosition(DestinationAABB.m_Center);
			MovableActor->GetComponentByClass<URenderComponent>()->SetRenderPriority(VectorToRenderPriority(MovableActor->GetPosition()));
			MovableInGameObjectComponent->m_InGameObjectProperty.m_Velocity = FVector2D::Zero;
		}
	}

}

UMovementManager::UMovementManager()
	:
	m_Movables{},
	m_Walls{},
	m_hBrush{},
	m_hPen{}
{
}

FLerpEvent::FLerpEvent(FVector2D StartPos, FVector2D DestPos, float fTotalTime)
	:
	m_StartPos{ StartPos },
	m_DestPos{ DestPos },
	m_fTotalTime{ fTotalTime },
	m_fAccumulatedTime{}
{

}
