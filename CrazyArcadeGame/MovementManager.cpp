#include "stdafx.h"
#include "MovementManager.h"
#include "MovableComponent.h"

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
		FVector2D Velocity = (*MovableIter)->GetVelocity();
		if (Velocity != FVector2D::Zero)
		{
			dfasfs
		}

		++MovableIter;
	}
}
