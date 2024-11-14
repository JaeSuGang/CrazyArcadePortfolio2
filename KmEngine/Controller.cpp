#include "stdafx.h"
#include "Controller.h"
#include "Engine.h"
#include "KeyManager.h"


void AController::Possess(APawn* Pawn)
{
	if (Pawn)
	{
		Pawn->SetController(this);
		m_Pawn = Pawn;
	}
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
	this->Unpossess();

	if (UKeyManager* KeyManager = GEngine->GetEngineSubsystem<UKeyManager>())
		KeyManager->ClearBindKey();
}

AController::~AController()
{
	this->Release();
}

AController::AController()
	:
	m_Pawn{}
{
}
