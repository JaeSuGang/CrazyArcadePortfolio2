#include "stdafx.h"
#include "CharacterAIController.h"

float ACharacterAIController::GetChangeDirectionTime()
{
	return m_fChangeDirectionTime;
}

FVector2D ACharacterAIController::GetDirection()
{
	return m_Direction;
}

void ACharacterAIController::SetRandomDirection()
{
	int nRandomResult = rand() % 4;

	switch (nRandomResult)
	{
	case 0:
		m_Direction = FVector2D::Up;
		break;
	case 1:
		m_Direction = FVector2D::Down;
		break;
	case 2:
		m_Direction = FVector2D::Left;
		break;
	case 3:
		m_Direction = FVector2D::Right;
		break;
	}

	m_fChangeDirectionTime = (rand() % 70 + 10) / 100.0f;
}

void ACharacterAIController::SetAccumulatedTime(float fTime)
{
	m_fAccumulatedTime = fTime;
}

float ACharacterAIController::GetAccumulatedTime()
{
	return m_fAccumulatedTime;
}

void ACharacterAIController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);
}

void ACharacterAIController::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	m_fAccumulatedTime += fDeltaTime;
}

void ACharacterAIController::LateTick(float fDeltaTime)
{
	Super::LateTick(fDeltaTime);
}

void ACharacterAIController::BeginPlay()
{
	Super::BeginPlay();
}
