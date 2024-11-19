#include "stdafx.h"
#include "Controller.h"
#include "Engine.h"
#include "KeyManager.h"
#include "Level.h"


void AController::Possess(APawn* Pawn)
{
	if (Pawn)
	{
		Pawn->SetController(this);
		m_Pawn = Pawn;
	}
}

void AController::SetPawn(APawn* Pawn)
{
	m_Pawn = Pawn;
}

void AController::Destroy()
{
	auto FindIter = std::find(m_Level->m_ActorsToDestroy.begin(), m_Level->m_ActorsToDestroy.end(), this);
	if (FindIter != m_Level->m_ActorsToDestroy.end())
		return;

	if (!m_Pawn)
		m_Level->m_ActorsToDestroy.push_back(this);
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
	if (m_Pawn)
	{
		m_Pawn->SetController(nullptr);
		m_Pawn = nullptr;
	}
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
