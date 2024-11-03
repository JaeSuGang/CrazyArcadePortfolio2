#include "stdafx.h"
#include "PhysicsManager.h"
#include "Engine.h"
#include "Actor.h"
#include "PhysicsComponent.h"
#include "TimeManager.h"
#include "DebugManager.h"
#include "Level.h"

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
			float fDeltaTime = TimeManager->GetDeltaTime();
			FVector2D LoopedActorPos = LoopedActor->GetPosition();
			FVector2D CurrentVelocity = PhysicsComponent->GetVelocity();
			FVector2D CurrentVelocityPerFrame = CurrentVelocity * fDeltaTime;
			float MaxSpeed = PhysicsComponent->GetMaxSpeed();
			float MaxSpeedPerFrame = MaxSpeed * fDeltaTime;
			float CurrentSpeed = CurrentVelocity.GetLength();
			float CurrentSpeedPerFrame = CurrentVelocityPerFrame.GetLength();

			GEngine->GetEngineSubsystem<UDebugManager>()->AddDebugText("Speed : " + std::to_string((int)CurrentSpeed));
			GEngine->GetEngineSubsystem<UDebugManager>()->AddDebugText("SpeedPerFrame : " + std::to_string(CurrentSpeedPerFrame));
			if (CurrentSpeedPerFrame > MaxSpeedPerFrame)
			{
				CurrentVelocityPerFrame = CurrentVelocityPerFrame / CurrentSpeedPerFrame * MaxSpeedPerFrame;
			}
			LoopedActor->SetPosition(LoopedActorPos + CurrentVelocityPerFrame);
			PhysicsComponent->SetVelocity(FVector2D::Zero);
		}

		++ActorIter;
	}

}

void UPhysicsManager::Initialize()
{
	m_PhysicsEvents.reserve(1000);
}
