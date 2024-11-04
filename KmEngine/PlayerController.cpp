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

void APlayerController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	UKeyManager* KeyManager = GEngine->GetEngineSubsystem<UKeyManager>();
	KeyManager->ClearBindKey();
	m_Pawn->OnPlayerPossessed();
}
