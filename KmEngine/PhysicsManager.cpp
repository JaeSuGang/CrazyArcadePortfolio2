#include "stdafx.h"
#include "PhysicsManager.h"
#include "Engine.h"
#include "Actor.h"
#include "PhysicsComponent.h"

void UPhysicsManager::Tick(float fDeltaTime)
{
	ULevel* ActiveLevel = GEngine->GetGameInstance()->GetActiveLevel();

	auto ActorIter = ActiveLevel->m_Actors.begin();
	while (ActorIter != ActiveLevel->m_Actors.end())
	{
		AActor* LoopedActor = *ActorIter;
		if (UPhysicsComponent* PhysicsComponent = LoopedActor->GetComponentByClass<UPhysicsComponent>();)
		{
			FVector2D CurrentVelocity = PhysicsComponent->GetVelocity();
			float MaxSpeed = PhysicsComponent->GetMaxSpeed();
			float CurrentSpeed = CurrentVelocity.GetLength();

			if (CurrentSpeed > MaxSpeed)
			{
				CurrentVelocity =
			}
		}
	}

}

void UPhysicsManager::Initialize()
{

}
