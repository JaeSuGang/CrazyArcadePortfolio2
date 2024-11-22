#include "stdafx.h"
#include "CharacterAIController.h"
#include "Character.h"
#include "AIManager.h"
#include "BombManager.h"

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

bool ACharacterAIController::GetRandomPlaceToGo(FVector2D& Output)
{
	UAIManager* AIManager = GetGameInstance()->GetSubsystem<UAIManager>();
	return AIManager->GetRandomPlaceToGo(m_Character->GetPosition(), Output);
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
	TaskSearchCooldown = (rand() % 2000 + 1000.0f) / 1000.0f;
}

void ACharacterAIController::SetRandomIdleTimer()
{
	IdleTimer = ((float)(rand() % 2000) + 800.0f) / 1000.0f;
}

void ACharacterAIController::SetRandomEvadeCheckCooldown()
{
	EvadeCheckCooldown = ((float)(rand() % 100) + 100.0f) / 1000.0f;
}

void ACharacterAIController::SubtractEvadeWaitTimer(float fDeltaTime)
{
	EvadeWaitTimer -= fDeltaTime;
}

void ACharacterAIController::SubtractTaskSearchCooldown(float fDeltaTime)
{
	this->TaskSearchCooldown -= fDeltaTime;
}

void ACharacterAIController::SubtractDirectionTimer(float fDeltaTime)
{
	this->DirectionTimer -= fDeltaTime;
}

void ACharacterAIController::SubtractEvadeCheckCooldown(float fDeltaTime)
{
	this->EvadeCheckCooldown -= fDeltaTime;
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

bool ACharacterAIController::GetIsInDangerousPosition() const
{
	UAIManager* AIManager = GetGameInstance()->GetSubsystem<UAIManager>();

	return AIManager->GetIsDangerousPosition(m_Character->GetPosition());
}

bool ACharacterAIController::GetIsDangerousPosition(FVector2D PositionToCheck) const
{
	UAIManager* AIManager = GetGameInstance()->GetSubsystem<UAIManager>();

	return AIManager->GetIsDangerousPosition(PositionToCheck);
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

	Controller->SetRandomTaskSearchTimer();
	Controller->SetRandomDirection();
	Controller->SetRandomDirectionTimer();

}

void ACharacterAIController::UIdleState::OnStateUpdate(float fDeltaTime)
{
	ACharacterAIController* Controller = static_cast<ACharacterAIController*>(this->Owner);
	ACharacter* Character = static_cast<ACharacter*>(Controller->GetPawn());

	Controller->SubtractDirectionTimer(fDeltaTime);
	Controller->SubtractTaskSearchCooldown(fDeltaTime);
	Controller->SubtractEvadeCheckCooldown(fDeltaTime);

	if (Controller->GetDebugMode())
	{
		Character->GetRenderManager()->DrawDebugText(Character->GetPosition() + FVector2D::Down * 20.0f,
			"IdleState");
	}

	if (Controller->GetTaskSearchCooldown() <= 0.0f)
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

	if (Controller->GetEvadeCheckCooldown() <= 0.0f)
	{
		Controller->SetRandomEvadeCheckCooldown();

		if (Controller->GetIsInDangerousPosition())
		{
			FVector2D RandomPlaceToGo{};
			if (Controller->GetRandomPlaceToGo(RandomPlaceToGo))
			{
				if (!Controller->GetIsDangerousPosition(RandomPlaceToGo))
				{
					Controller->SetPathUsingAStar(RandomPlaceToGo);
					FSM->ChangeState<UEvadeState>();
				}
			}
		}
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

	Controller->SubtractEvadeCheckCooldown(fDeltaTime);

	if (Controller->GetDebugMode())
	{
		Character->GetRenderManager()->DrawDebugText(Character->GetPosition() + FVector2D::Down * 20.0f,
			"TaskState");
	}

	if (Controller->Path.size() == 0)
	{
		Character->TryPutBomb();
		FSM->ChangeState<UIdleState>();
		return;
	}

	Controller->FollowPath();
}

void ACharacterAIController::UTaskState::OnStateExit()
{
}

void ACharacterAIController::UEvadeState::OnStateEnter()
{
	ACharacterAIController* Controller = static_cast<ACharacterAIController*>(this->Owner);
	ACharacter* Character = static_cast<ACharacter*>(Controller->GetPawn());

	Controller->SetEvadeWaitTimer(3.5f);
}

void ACharacterAIController::UEvadeState::OnStateUpdate(float fDeltaTime)
{
	ACharacterAIController* Controller = static_cast<ACharacterAIController*>(this->Owner);
	ACharacter* Character = static_cast<ACharacter*>(Controller->GetPawn());

	Controller->SubtractEvadeWaitTimer(fDeltaTime);


	if (Controller->GetEvadeWaitTimer() <= 0.0f)
	{
		FSM->ChangeState<UIdleState>();
	}


	Controller->FollowPath();
}

void ACharacterAIController::UEvadeState::OnStateExit()
{
}
