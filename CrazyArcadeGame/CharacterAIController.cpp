#include "stdafx.h"
#include "CharacterAIController.h"
#include "Character.h"
#include "AIManager.h"


void ACharacterAIController::SetRandomPositionToGo()
{
	UAIManager* AIManager = GetGameInstance()->GetSubsystem<UAIManager>();
	AIManager->SetCharacterRandomPositionToGo(this);
}

bool ACharacterAIController::CheckPositionWhetherSafeToPutBomb(FVector2D Position, FVector2D& EscapeDest) const
{
	UAIManager* AIManager = GetGameInstance()->GetSubsystem<UAIManager>();
	return AIManager->CheckPositionWhetherSafeToPutBomb(m_Character, Position, EscapeDest);
}

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

	UAIManager* AIManager = GetGameInstance()->GetSubsystem<UAIManager>();

	return AIManager->FindPath(m_Pawn->GetPosition(), Destination, m_Path);
}

void ACharacterAIController::SetPathByClicking()
{
	UKeyManager* KeyManager = GEngine->GetEngineSubsystem<UKeyManager>();
	this->SetPathUsingAStar(KeyManager->GetMousePos());
}

float ACharacterAIController::GetChangeDirectionTime()
{
	return idleTimer;
}

FVector2D ACharacterAIController::GetDirection()
{
	return m_Direction;
}

void ACharacterAIController::SetRandomIdleTimer()
{
	m_fIdleTimer = ((float)(rand() % 200) + 100.0f) / 100.0f;
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
	m_fAccumulatedTime += fDeltaTime;
	m_fIdleTimer -= fDeltaTime;


	//if (m_Path.size() == 0)
	//	m_AIState = ACharacterAIController::EAIState::Idle;
	//else
	//	m_AIState = ACharacterAIController::EAIState::Move;

	//if (m_Character)
	//{
	//	switch (m_AIState)
	//	{
	//	case ACharacterAIController::EAIState::Idle:
	//		if ((int)(m_fAccumulatedTime / 0.01f) % 50 != 0)
	//		{
	//			if (m_Character->GetBombLeft() > 0 && m_fIdleLastingTime < m_fAccumulatedTime)
	//			{
	//				FVector2D EscapePosition{};
	//				if (this->CheckPositionWhetherSafeToPutBomb(m_Character->GetPosition(), EscapePosition))
	//				{
	//					m_Character->TryPutBomb();
	//					this->SetPathUsingAStar(EscapePosition);
	//				}

	//			}
	//		}

	//		if (m_fAccumulatedTime > m_fIdleLastingTime)
	//		{
	//			this->SetRandomPositionToGo();
	//		}
	//		break;

	//	case ACharacterAIController::EAIState::Move:
	//	{
	//		for (FVector2D Dest : m_Path)
	//		{
	//			if ((m_Character->GetPosition() - Dest).GetLength() < 6.0f)
	//			{
	//				m_Path.erase(m_Path.begin());
	//				break;
	//			}

	//			if (m_Character->GetPosition().X < Dest.X - 3.0f)
	//				m_Character->Move(FVector2D::Right);
	//			else if (m_Character->GetPosition().X > Dest.X + 3.0f)
	//				m_Character->Move(FVector2D::Left);

	//			if (m_Character->GetPosition().Y < Dest.Y - 3.0f)
	//				m_Character->Move(FVector2D::Down);
	//			else if (m_Character->GetPosition().Y > Dest.Y + 3.0f)
	//				m_Character->Move(FVector2D::Up);

	//			break;
	//		}
	//	}

	//		break;

	//	default:
	//		break;
	//	}

	//}
}

void ACharacterAIController::LateTick(float fDeltaTime)
{
	Super::LateTick(fDeltaTime);
}

void ACharacterAIController::BeginPlay()
{
	Super::BeginPlay();

	m_FSM->ChangeState<UIdleState>();
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
	m_fIdleTimer{},
	m_fAccumulatedTime{},
	m_Character{}
{
	m_FSM = CreateDefaultSubobject<UFSMComponent>();
	m_FSM->CreateState<UIdleState>();
	m_FSM->CreateState<UTaskState>();
	m_FSM->CreateState<UEvadeState>();
}

void ACharacterAIController::UIdleState::OnStateEnter()
{
	ACharacterAIController* Controller = static_cast<ACharacterAIController*>(this->m_Owner);
	ACharacter* Character = static_cast<ACharacter*>(Controller->GetPawn());

	Controller->SetRandomIdleTimer();
}

void ACharacterAIController::UIdleState::OnStateUpdate(float fDeltaTime)
{
	ACharacterAIController* Controller = static_cast<ACharacterAIController*>(this->m_Owner);
	ACharacter* Character = static_cast<ACharacter*>(Controller->GetPawn());

	Controller->SetRandomIdleTimer

	if (Controller->GetDebugMode())
		Character->GetRenderManager()->DrawDebugText(Character->GetPosition() + FVector2D::Down * 20.0f, "IdleState");

}

void ACharacterAIController::UIdleState::OnStateExit()
{
}

void ACharacterAIController::UTaskState::OnStateEnter()
{
}

void ACharacterAIController::UTaskState::OnStateUpdate(float fDeltaTime)
{
}

void ACharacterAIController::UTaskState::OnStateExit()
{
}

void ACharacterAIController::UEvadeState::OnStateEnter()
{
}

void ACharacterAIController::UEvadeState::OnStateUpdate(float fDeltaTime)
{
}

void ACharacterAIController::UEvadeState::OnStateExit()
{
}
