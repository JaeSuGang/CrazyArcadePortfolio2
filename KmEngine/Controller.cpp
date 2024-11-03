#include "stdafx.h"
#include "Controller.h"
#include "Engine.h"
#include "KeyManager.h"

void AController::Possess(APawn* Pawn)
{
	m_Pawn = Pawn;

	UKeyManager* KeyManager = GEngine->GetEngineSubsystem<UKeyManager>();
	KeyManager->ClearBindKey();
	m_Pawn->SetupPlayerInput();
}

void AController::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);
}

void AController::LateTick(float fDeltaTime)
{
	Super::LateTick(fDeltaTime);
}

void AController::BeginPlay()
{
	Super::BeginPlay();
}

void AController::Release()
{
	UKeyManager* KeyManager = GEngine->GetEngineSubsystem<UKeyManager>();
	KeyManager->ClearBindKey();
}

AController::~AController()
{
	this->Release();
}
