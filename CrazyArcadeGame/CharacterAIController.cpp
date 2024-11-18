#include "stdafx.h"
#include "CharacterAIController.h"
#include "Character.h"

void ACharacterAIController::LocatePosToPutBomb()
{
	FVector2D CurTilePos = TileIndexToVector(VectorToTileIndex(this->GetPosition()));
	vector<FVector2D> ConsiderableTilePositions;

	ConsiderableTilePositions.push_back(CurTilePos + FVector2D::Left * 60.0f + FVector2D::Up * 60.0f);
	ConsiderableTilePositions.push_back(CurTilePos + FVector2D::Up * 60.0f);
	ConsiderableTilePositions.push_back(CurTilePos + FVector2D::Right * 60.0f + FVector2D::Up * 60.0f);
	ConsiderableTilePositions.push_back(CurTilePos + FVector2D::Left * 60.0f);
	ConsiderableTilePositions.push_back(CurTilePos);
	ConsiderableTilePositions.push_back(CurTilePos + FVector2D::Right * 60.0f);
	ConsiderableTilePositions.push_back(CurTilePos + FVector2D::Left * 60.0f + FVector2D::Down * 60.0f);
	ConsiderableTilePositions.push_back(CurTilePos + FVector2D::Down * 60.0f);
	ConsiderableTilePositions.push_back(CurTilePos + FVector2D::Right * 60.0f + FVector2D::Down * 60.0f);

	for (FVector2D TilePos : ConsiderableTilePositions)
	{

	}
}

bool ACharacterAIController::SetPathUsingAStar(FVector2D Destination)
{
	

	return false;
}

void ACharacterAIController::SetPathByClicking()
{
	
}

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

	m_fChangeDirectionTime = m_fAccumulatedTime + (rand() % 70 + 10) / 100.0f;
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

	m_Character = dynamic_cast<ACharacter*>(Pawn);
}

void ACharacterAIController::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	if (m_Path.size() == 0)
		m_AIState = ACharacterAIController::EAIState::Idle;

	if (m_Character)
	{
		switch (m_AIState)
		{
		case ACharacterAIController::EAIState::Idle:
			if (m_fAccumulatedTime > m_fChangeDirectionTime)
			{
				this->SetRandomDirection();
			}
			m_Character->Move(m_Direction);
			break;

		case ACharacterAIController::EAIState::Move:

			if (m_bDebugMode)
			{
				for (FVector2D Path : m_Path)
				{

				}
			}

			break;

		default:
			break;
		}
	}

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

ACharacterAIController::ACharacterAIController()
	:
	m_Direction{},
	m_fChangeDirectionTime{},
	m_fAccumulatedTime{},
	m_AIState{ ACharacterAIController::EAIState::Idle}
{
}
