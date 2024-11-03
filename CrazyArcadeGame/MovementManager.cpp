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
			FVector2D MaxVelocity = MovableComponent->GetMaxVelocity();
			FVector2D MaxVelocityPerFrame = MaxVelocity * fDeltaTime;

			if ()

			AActor* MovableActor = MovableComponent->GetOwner();
			MovableActor->AddPosition(VelocityToApplyPerFrame);
			
		}

		++MovableIter;
	}
}
