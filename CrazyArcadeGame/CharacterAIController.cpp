#include "stdafx.h"
#include "CharacterAIController.h"
#include "Character.h"
#include "AIManager.h"


void ACharacterAIController::SetRandomPositionToGo()
{
	UAIManager* AIManager = GetGameInstance()->GetSubsystem<UAIManager>();
	AIManager->SetCharacterRandomPositionToGo(this);
}

bool ACharacterAIController::GetRandomPlaceToPutBomb(FVector2D& Output)
{
	UAIManager* AIManager = GetGameInstance()->GetSubsystem<UAIManager>();
	return AIManager->GetRandomPlaceToPutBomb(m_Character->GetPosition(), Output);
}

bool ACharacterAIController::CheckPositionWhetherSafeToPutBomb(FVector2D Position) const
{
	UAIManager* AIManager = GetGameInstance()->GetSubsystem<UAIManager>();
	return AIManager->CheckPositionWhetherSafeToPutBomb(m_Character, Position);
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

	return AIManager->FindPath(m_Pawn->GetPosition(), Destination, Path);
}

void ACharacterAIController::SetPathByClicking()
{
	UKeyManager* KeyManager = GEngine->GetEngineSubsystem<UKeyManager>();
	this->SetPathUsingAStar(KeyManager->GetMousePos());
}



FVector2D ACharacterAIController::GetDirection()
{
	return Direction;
}

void ACharacterAIController::SetRandomDirection()
{
	switch (rand() % 4)
	{
	case 0:
		this->Direction = FVector2D::Up;
		break;

	case 1:
		this->Direction = FVector2D::Right;
		break;

	case 2:
		this->Direction = FVector2D::Down;
		break;

	case 3:
		this->Direction = FVector2D::Left;
		break;

	default:
		break;
	}
}

void ACharacterAIController::SetRandomDirectionTimer()
{
	DirectionTimer = (rand() % 700 + 300.0f) / 1000.0f;
}

void ACharacterAIController::SetRandomTaskSearchTimer()
{
	TaskSearchCooldownTimer = (rand() % 2000 + 1000.0f) / 1000.0f;
}

void ACharacterAIController::SetRandomIdleTimer()
{
	IdleTimer = ((float)(rand() % 2000) + 800.0f) / 1000.0f;
}

void ACharacterAIController::SubtractTaskSearchCooldown(float fDeltaTime)
{
	this->TaskSearchCooldownTimer -= fDeltaTime;
}

void ACharacterAIController::SubtractDirectionTimer(float fDeltaTime)
{
	this->DirectionTimer -= fDeltaTime;
}

void ACharacterAIController::SetAccumulatedTime(float fTime)
{
	AccumulatedTime = fTime;
}

float ACharacterAIController::GetAccumulatedTime()
{
	return AccumulatedTime;
}

void ACharacterAIController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	m_Character = dynamic_cast<ACharacter*>(Pawn);
}

void ACharacterAIController::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);
	AccumulatedTime += fDeltaTime;


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

	FSM->ChangeState<UIdleState>();
}

void ACharacterAIController::OnDebug()
{
	if (!m_Pawn)
		return;

	URenderManager* RenderManager = GEngine->GetEngineSubsystem<URenderManager>();


	FVector2D PreviousPosition = m_Pawn->GetPosition();
	for (FVector2D Position : Path)
	{
		RenderManager->DrawDebugLine(PreviousPosition, Position, m_Pawn->GetDebugPen());
		PreviousPosition = Position;
	}
}

void ACharacterAIController::FollowPath()
{
	if (!m_Character || Path.begin() == Path.end())
		return;

	FVector2D PositionToGo = *Path.begin();

	if (m_Character->GetPosition().X < PositionToGo.X - 5.0f)
		Direction = FVector2D::Right;
	else if (m_Character->GetPosition().X > PositionToGo.X + 5.0f)
		Direction = FVector2D::Left;
	else if (m_Character->GetPosition().Y < PositionToGo.Y - 5.0f)
		Direction = FVector2D::Down;
	else if (m_Character->GetPosition().Y > PositionToGo.Y + 5.0f)
		Direction = FVector2D::Up;
	else
	{
		Path.erase(Path.begin());
		return;
	}

	m_Character->Move(Direction);
}

ACharacterAIController::ACharacterAIController()
	:
	Direction{},
	IdleTimer{},
	AccumulatedTime{},
	m_Character{}
{
	FSM = CreateDefaultSubobject<UFSMComponent>();
	FSM->CreateState<UIdleState>();
	FSM->CreateState<UTaskState>();
	FSM->CreateState<UEvadeState>();
}

void ACharacterAIController::UIdleState::OnStateEnter()
{
	ACharacterAIController* Controller = static_cast<ACharacterAIController*>(this->Owner);
	ACharacter* Character = static_cast<ACharacter*>(Controller->GetPawn());

	Controller->SetRandomIdleTimer();
	Controller->SetRandomDirection();
	Controller->SetRandomDirectionTimer();

}

void ACharacterAIController::UIdleState::OnStateUpdate(float fDeltaTime)
{
	ACharacterAIController* Controller = static_cast<ACharacterAIController*>(this->Owner);
	ACharacter* Character = static_cast<ACharacter*>(Controller->GetPawn());

	Controller->SubtractDirectionTimer(fDeltaTime);
	Controller->SubtractTaskSearchCooldown(fDeltaTime);

	if (Controller->GetDebugMode())
	{
		Character->GetRenderManager()->DrawDebugText(Character->GetPosition() + FVector2D::Down * 20.0f,
			"IdleState");
	}

	if (Controller->GetTaskSearchCooldownTimer() <= 0.0f)
	{
		Controller->SetRandomTaskSearchTimer();

		FVector2D PositionToPutBomb{};
		if (Controller->GetRandomPlaceToPutBomb(PositionToPutBomb))
		{
			if (Controller->CheckPositionWhetherSafeToPutBomb(PositionToPutBomb))
			{
				Controller->SetPathUsingAStar(PositionToPutBomb);
				FSM->ChangeState<UTaskState>();
			}
		}
	}

	if (Controller->GetDirectionTimer() <= 0.0f)
	{
		Controller->SetRandomDirection();
		Controller->SetRandomDirectionTimer();
	}

	Character->Move(Controller->GetDirection());
}

void ACharacterAIController::UIdleState::OnStateExit()
{
}

void ACharacterAIController::UTaskState::OnStateEnter()
{

}

void ACharacterAIController::UTaskState::OnStateUpdate(float fDeltaTime)
{
	ACharacterAIController* Controller = static_cast<ACharacterAIController*>(this->Owner);
	ACharacter* Character = static_cast<ACharacter*>(Controller->GetPawn());

	if (Controller->GetDebugMode())
	{
		Character->GetRenderManager()->DrawDebugText(Character->GetPosition() + FVector2D::Down * 20.0f,
			"TaskState");
	}

	Controller->FollowPath();
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
