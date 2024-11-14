#include "stdafx.h"
#include "PlayerController.h"

void APlayerController::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);
}

void APlayerController::LateTick(float fDeltaTime)
{
	Super::LateTick(fDeltaTime);
}

void APlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerController::Unpossess()
{
	if (m_Pawn)
	{
		m_Pawn->OnPlayerUnpossessed();
		m_Pawn = nullptr;
	}
}

void APlayerController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	UKeyManager* KeyManager = GEngine->GetEngineSubsystem<UKeyManager>();
	KeyManager->ClearBindKey();
	Pawn->OnPlayerPossessed();
}
