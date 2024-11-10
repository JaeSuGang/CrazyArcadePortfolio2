#include "stdafx.h"
#include "KmEngine/Level.h"
#include "MovementManager.h"
#include "MovableComponent.h"
#include "KmEngine/Actor.h"
#include "KmEngine/RenderComponent.h"
#include "WallComponent.h"
#include "AxisAlignedBoundingBox.h"
#include "InGameObjectComponent.h"

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
			FVector2D VelocityToApplyInFrame = InGameObjectProperty.m_Velocity;
			VelocityToApplyInFrame.X = VelocityToApplyInFrame.X > InGameObjectProperty.m_MaxVelocity.X ? InGameObjectProperty.m_MaxVelocity.X : VelocityToApplyInFrame.X;
			VelocityToApplyInFrame.Y = VelocityToApplyInFrame.Y > InGameObjectProperty.m_MaxVelocity.Y ? InGameObjectProperty.m_MaxVelocity.Y : VelocityToApplyInFrame.Y;

			VelocityToApplyInFrame = VelocityToApplyInFrame * fDeltaTime;

			FAxisAlignedBoundingBox DestinationAABB = {
				OriginalPos + VelocityToApplyInFrame,
				InGameObjectProperty.m_CollisionSize.X / 2,
				InGameObjectProperty.m_CollisionSize.Y / 2 };

			for (AActor* WallActor : m_Walls)
			{
				UInGameObjectComponent* WallInGameObjectComponent = WallActor->GetComponentByClass<UInGameObjectComponent>();
				FAxisAlignedBoundingBox WallAABB = {
					WallActor->GetPosition(),
					InGameObjectProperty.m_CollisionSize.X / 2,
					InGameObjectProperty.m_CollisionSize.Y / 2 };

				if (DestinationAABB.GetIsCollidedWith(WallAABB))
				{
					DestinationAABB.SetToCorrectPos(OriginalPos, WallAABB);
				}
			}

			MovableActor->SetPosition(DestinationAABB.m_Center);
			MovableInGameObjectComponent->m_InGameObjectProperty.m_Velocity = FVector2D::Zero;
		}
	}

	// Obsolete Physics
	/*
	for (UMovableComponent* MovableComponent : m_Movables)
	{
		FVector2D VelocityToApply = MovableComponent->GetVelocity();
		if (VelocityToApply == FVector2D::Zero)
			continue;

		FVector2D VelocityToApplyPerFrame = VelocityToApply * fDeltaTime;
		AActor* MovableActor = MovableComponent->GetOwner();
		FVector2D ActorPos = MovableActor->GetPosition();
		float MaxSpeed = MovableComponent->GetMaxSpeed();
		float MaxSpeedPerFrame = MaxSpeed * fDeltaTime;
		float SpeedToApply = VelocityToApply.GetLength();
		float SpeedToApplyPerFrame = SpeedToApply* fDeltaTime;

		if (SpeedToApplyPerFrame > MaxSpeedPerFrame)
		{
			VelocityToApplyPerFrame = VelocityToApplyPerFrame / SpeedToApplyPerFrame * MaxSpeedPerFrame;
		}

		FVector2D ActorPositionToSettle = ActorPos + VelocityToApplyPerFrame;

		for (UWallComponent* WallComponent : m_Walls)
		{
			if (VelocityToApplyPerFrame.X > 0.0f)
			{
				AActor* WallActor = WallComponent->GetOwner();
				// 벽을 15, 30, 15의 픽셀로 나눔 
				// 벽때문에 못지나갈때
				if (ActorPositionToSettle.Y < WallActor->GetPosition().Y + 15.0f &&
					ActorPositionToSettle.Y > WallActor->GetPosition().Y - 15.0f &&
					ActorPositionToSettle.X + 60.0f > WallActor->GetPosition().X &&
					ActorPositionToSettle.X + 60.0f < WallActor->GetPosition().X + 30.0f)
				{
					VelocityToApplyPerFrame.X = 0.0f;
				}
			}
		}





		ActorPositionToSettle = ActorPos + VelocityToApplyPerFrame;
		MovableActor->SetPosition(ActorPositionToSettle);
		MovableComponent->SetVelocity(FVector2D::Zero);


		if (URenderComponent* RenderComponent = MovableActor->GetComponentByClass<URenderComponent>())
		{
			RenderComponent->SetRenderPriority(10 + (ActorPositionToSettle.Y - 60) / 60);
		}

	}
	*/
}

UMovementManager::UMovementManager()
	:
	m_Movables{},
	m_Walls{}
{
}
