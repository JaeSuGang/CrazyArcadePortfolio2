#include "stdafx.h"
#include "AIController.h"

void AAIController::Unpossess()
{
	if (m_Pawn)
	{
		m_Pawn->OnAIUnpossessed();
		m_Pawn = nullptr;
	}
}

void AAIController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	Pawn->OnAIPossessed();
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

void AAIController::Release()
{
}

AAIController::~AAIController()
{
	this->Release();
}
