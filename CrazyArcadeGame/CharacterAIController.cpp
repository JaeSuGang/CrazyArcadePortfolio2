#include "stdafx.h"
#include "CharacterAIController.h"
#include "Character.h"
#include "AIManager.h"

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
	if (!m_Pawn)
		return false;

	UAIManager* AIManager = GetGameInstance()->GetGameInstanceSubsystem<UAIManager>();

	return AIManager->FindPath(m_Pawn->GetPosition(), Destination, m_Path);
}

void ACharacterAIController::SetPathByClicking()
{
	UKeyManager* KeyManager = GEngine->GetEngineSubsystem<UKeyManager>();
	this->SetPathUsingAStar(KeyManager->GetMousePos());
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
	else
		m_AIState = ACharacterAIController::EAIState::Move;


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
		{
			for (FVector2D Dest : m_Path)
			{
				if ((m_Character->GetPosition() - Dest).GetLength() < 6.0f)
				{
					m_Path.erase(m_Path.begin());
					break;
				}

				if (m_Character->GetPosition().X < Dest.X - 3.0f)
					m_Character->Move(FVector2D::Right);
				else if (m_Character->GetPosition().X > Dest.X + 3.0f)
					m_Character->Move(FVector2D::Left);

				if (m_Character->GetPosition().Y < Dest.Y - 3.0f)
					m_Character->Move(FVector2D::Down);
				else if (m_Character->GetPosition().Y > Dest.Y + 3.0f)
					m_Character->Move(FVector2D::Up);

				break;
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

void ACharacterAIController::OnDebug()
{
	if (!m_Pawn)
		return;
	URenderManager* RenderManager = GEngine->GetEngineSubsystem<URenderManager>();

	FVector2D PreviousPosition = m_Pawn->GetPosition();
	for (FVector2D Position : m_Path)
	{
		RenderManager->DrawDebugLine(PreviousPosition, Position, m_Pawn->GetDebugPen());
		PreviousPosition = Position;
	}
}

ACharacterAIController::ACharacterAIController()
	:
	m_Direction{},
	m_fChangeDirectionTime{},
	m_fAccumulatedTime{},
	m_AIState{ ACharacterAIController::EAIState::Idle}
{
}
