#include "stdafx.h"
#include "PhysicsManager.h"
#include "Engine.h"
#include "Actor.h"
#include "PhysicsComponent.h"
#include "TimeManager.h"
#include "DebugManager.h"

void UPhysicsManager::Tick(float fDeltaTime)
{
	ULevel* ActiveLevel = GEngine->GetGameInstance()->GetActiveLevel();

	auto ActorIter = ActiveLevel->m_Actors.begin();
	while (ActorIter != ActiveLevel->m_Actors.end())
	{
		AActor* LoopedActor = *ActorIter;
		if (UPhysicsComponent* PhysicsComponent = LoopedActor->GetComponentByClass<UPhysicsComponent>())
		{
			// 물리 계산 시작
			UTimeManager* TimeManager = GEngine->GetEngineSubsystem<UTimeManager>();
			FVector2D LoopedActorPos = LoopedActor->GetPosition();
			FVector2D CurrentVelocity = PhysicsComponent->GetVelocity();
			float MaxSpeed = PhysicsComponent->GetMaxSpeed() * TimeManager->GetDeltaTime();
			float CurrentSpeed = CurrentVelocity.GetLength();

			GEngine->GetEngineSubsystem<UDebugManager>()->AddDebugText("Current Speed : " + std::to_string(CurrentSpeed));
			if (CurrentSpeed > MaxSpeed)
			{
				CurrentVelocity = CurrentVelocity / CurrentSpeed * MaxSpeed;
			}
			LoopedActor->SetPosition(LoopedActorPos + CurrentVelocity);
			PhysicsComponent->SetVelocity(FVector2D::Zero);
		}

		++ActorIter;
	}

}

void UPhysicsManager::Initialize()
{

}
