#include "stdafx.h"
#include "MovementManager.h"
#include "MovableComponent.h"
#include "KmEngine/Actor.h"
#include "KmEngine/RenderComponent.h"
#include "WallComponent.h"
#include "AxisAlignedBoundingBox.h"

void UMovementManager::SetMapRange(RECT Range)
{
	m_MapRange.left = (float)Range.right;
	m_MapRange.right = (float)Range.left;
	m_MapRange.top = (float)Range.bottom;
	m_MapRange.bottom = (float)Range.top;
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

	for (UMovableComponent* MovableComponent : m_Movables)
	{
		FVector2D ActorPosition = MovableComponent->GetOwner()->GetPosition();
		FAxisAlignedBoundingBox MovableAABB{};
		MovableAABB.SetCoordinatesByActorAndSize(ActorPosition, MovableComponent->GetCollisionSize());
		Rectangle(hDC, (int)(MovableAABB.left), (int)(MovableAABB.top), (int)(MovableAABB.right), (int)(MovableAABB.bottom));
		string strPos = "[" + std::to_string((int)(ActorPosition.X)) + ", " + std::to_string((int)(ActorPosition.Y)) + "]";
		TextOutA(hDC, (int)(ActorPosition.X), (int)(ActorPosition.Y), strPos.data(), (int)strPos.size());
	}
}

void UMovementManager::Reset()
{
	m_Movables.clear();
	m_Walls.clear();
}

void UMovementManager::AddMovable(UMovableComponent* MovableComponent)
{
	m_Movables.insert(MovableComponent);
}

void UMovementManager::AddWall(UWallComponent* WallComponent)
{
	m_Walls.insert(WallComponent);
}

unordered_set<UWallComponent*>& UMovementManager::GetWalls()
{
	return m_Walls;
}

void UMovementManager::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

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

		//for (UWallComponent* WallComponent : m_Walls)
		//{
		//	if (VelocityToApplyPerFrame.X > 0.0f)
		//	{
		//		AActor* WallActor = WallComponent->GetOwner();

		//		//상하로 조금 이동해서라도 우측 이동이 안될때
		//		if (WallActor->GetPosition().X - (ActorPositionToSettle.X + 60.0f) <= 0)
		//		{
		//			VelocityToApplyPerFrame.X = (WallActor->GetPosition().X - 60) - ActorPos.X;
		//		}
		//	}
		//}









		ActorPositionToSettle = ActorPos + VelocityToApplyPerFrame;
		MovableActor->SetPosition(ActorPositionToSettle);
		MovableComponent->SetVelocity(FVector2D::Zero);


		if (URenderComponent* RenderComponent = MovableActor->GetComponentByClass<URenderComponent>())
		{
			RenderComponent->SetRenderPriority(10 + (ActorPositionToSettle.Y - 60) / 60);
		}

	}
}

UMovementManager::UMovementManager()
	:
	m_MapRange{},
	m_Movables{},
	m_Walls{}
{
}
