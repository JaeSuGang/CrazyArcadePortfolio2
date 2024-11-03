#include "stdafx.h"
#include "MovementManager.h"
#include "MovableComponent.h"
#include "KmEngine/Actor.h"

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
			
		}

		++MovableIter;
	}
}
