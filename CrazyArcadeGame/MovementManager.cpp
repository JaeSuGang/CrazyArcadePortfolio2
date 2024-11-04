#include "stdafx.h"
#include "MovementManager.h"
#include "MovableComponent.h"
#include "KmEngine/Actor.h"

void UMovementManager::EnableDebugRender()
{
	URenderManager* RenderManager = GEngine->GetEngineSubsystem<URenderManager>();
	RenderManager->AddCustomRenderEvent(std::bind(&UMovementManager::DebugRender, this));
}

void UMovementManager::DebugRender()
{
	URenderManager* RenderManager = GEngine->GetEngineSubsystem<URenderManager>();
	HDC hDC = RenderManager->GetBackBufferHandle();
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(HOLLOW_BRUSH));
	HPEN hGreenPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hGreenPen);
	auto MovableIter = m_Movables.begin();
	while (MovableIter != m_Movables.end())
	{
		UMovableComponent* MovableComponent = *MovableIter;

		FVector2D ActorPosition = MovableComponent->GetOwner()->GetPosition();
		float fRadius = MovableComponent->GetRadius();
		Rectangle(hDC, (int)(ActorPosition.X - fRadius), (int)(ActorPosition.Y - fRadius), (int)(ActorPosition.X + fRadius), (int)(ActorPosition.Y + fRadius));
		string strPos = "[" + std::to_string((int)(ActorPosition.X)) + ", " + std::to_string((int)(ActorPosition.Y)) + "]";
		TextOutA(hDC, (int)(ActorPosition.X), (int)(ActorPosition.Y), strPos.data(), (int)strPos.size());
		++MovableIter;
	}
	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);
	DeleteObject(hGreenPen);
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

void UMovementManager::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	auto MovableIter = m_Movables.begin();
	while (MovableIter != m_Movables.end())
	{
		UMovableComponent* MovableComponent = *MovableIter;
		FVector2D VelocityToApply = MovableComponent->GetVelocity();
		if (VelocityToApply != FVector2D::Zero)
		{
			FVector2D VelocityToApplyPerFrame = VelocityToApply * fDeltaTime;
			float MaxSpeed = MovableComponent->GetMaxSpeed();
			float MaxSpeedPerFrame = MaxSpeed * fDeltaTime;
			float SpeedToApply = VelocityToApply.GetLength();
			float SpeedToApplyPerFrame = SpeedToApply* fDeltaTime;

			if (SpeedToApplyPerFrame > MaxSpeedPerFrame)
			{
				VelocityToApplyPerFrame = VelocityToApplyPerFrame / SpeedToApplyPerFrame * MaxSpeedPerFrame;
			}

			AActor* MovableActor = MovableComponent->GetOwner();
			MovableActor->AddPosition(VelocityToApplyPerFrame);
			MovableComponent->SetVelocity(FVector2D::Zero);
			float fRadius = MovableComponent->GetRadius();
			
			FVector2D NewPosition = MovableActor->GetPosition();
			NewPosition.X = (NewPosition.X < m_MapLocation.Left + fRadius) ? m_MapLocation.Left + fRadius : NewPosition.X;
			NewPosition.X = (NewPosition.X > m_MapLocation.Right - fRadius) ? m_MapLocation.Right - fRadius : NewPosition.X;
			NewPosition.Y = (NewPosition.Y < m_MapLocation.Up + fRadius) ? m_MapLocation.Up + fRadius : NewPosition.Y;
			NewPosition.Y = (NewPosition.Y > m_MapLocation.Down - fRadius) ? m_MapLocation.Down - fRadius : NewPosition.Y;
			MovableActor->SetPosition(NewPosition);
		}

		++MovableIter;
	}
}

UMovementManager::UMovementManager()
	:
	m_MapLocation{},
	m_Movables{},
	m_Walls{}
{
}
