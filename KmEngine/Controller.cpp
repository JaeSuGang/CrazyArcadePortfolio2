#include "stdafx.h"
#include "Controller.h"
#include "Engine.h"
#include "KeyManager.h"

void AController::Unpossess()
{
	if (UKeyManager* km = GEngine->GetEngineSubsystem<UKeyManager>())
		km->ClearBindKey();

	if (m_Pawn)
	{
		m_Pawn->SetController(nullptr);
		m_Pawn = nullptr;
	}
}

void AController::Possess(APawn* Pawn)
{
	m_Pawn = Pawn;
	m_Pawn->SetController(this);
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

	UKeyManager* KeyManager = GEngine->GetEngineSubsystem<UKeyManager>();
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
