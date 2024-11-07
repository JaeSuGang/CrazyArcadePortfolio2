#include "stdafx.h"
#include "MovementManager.h"
#include "MovableComponent.h"
#include "KmEngine/Actor.h"
#include "KmEngine/RenderComponent.h"
#include "WallComponent.h"

void UMovementManager::SetMapRange(RECT Range)
{
	m_MapRange = Range;
}

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

void UMovementManager::AddWall(UWallComponent* WallComponent)
{
	m_Walls.insert(WallComponent);
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

			for (UWallComponent* WallComponent : m_Walls)
			{
				AActor* Wall = WallComponent->GetOwner();
				FVector2D WallPos = Wall->GetPosition();
				FVector2D PositionDifference = NewPosition - WallPos;
				if (PositionDifference.GetLength() > 60)
					continue;

				if (std::abs(PositionDifference.X) < 60)
				{
					// 캐릭터가 벽보다 오른쪽
					NewPosition.X = PositionDifference.X > 0 ? WallPos.X + 60 : WallPos.X - 60;
				}
				if (std::abs(PositionDifference.Y) < 60)
				{
					// 캐릭터가 벽보다 위쪽
					NewPosition.Y = PositionDifference.Y > 0 ? WallPos.Y + 60 : WallPos.Y - 60;
				}
			}


			NewPosition.X = (NewPosition.X < m_MapRange.left + fRadius) ? m_MapRange.left + fRadius : NewPosition.X;
			NewPosition.X = (NewPosition.X > m_MapRange.right - fRadius) ? m_MapRange.right - fRadius : NewPosition.X;
			NewPosition.Y = (NewPosition.Y < m_MapRange.top + fRadius) ? m_MapRange.top + fRadius : NewPosition.Y;
			NewPosition.Y = (NewPosition.Y > m_MapRange.bottom - fRadius) ? m_MapRange.bottom - fRadius : NewPosition.Y;
			MovableActor->SetPosition(NewPosition);

			if (URenderComponent* RenderComponent = MovableActor->GetComponentByClass<URenderComponent>())
			{
				RenderComponent->SetRenderPriority(10 + (NewPosition.Y - 60) / 60);
			}
		}

		++MovableIter;
	}
}

UMovementManager::UMovementManager()
	:
	m_MapRange{},
	m_Movables{},
	m_Walls{}
{
}
