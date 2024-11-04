#include "stdafx.h"
#include "AIController.h"

void AAIController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	m_Pawn->OnAIPossessed();
}

void AAIController::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

}

void AAIController::LateTick(float fDeltaTime)
{
	Super::LateTick(fDeltaTime);
}

void AAIController::BeginPlay()
{
	Super::BeginPlay();
}
