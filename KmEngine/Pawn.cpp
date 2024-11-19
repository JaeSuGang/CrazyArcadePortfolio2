#include "stdafx.h"
#include "Pawn.h"
#include "Controller.h"
#include "Level.h"

AController* APawn::GetController()
{
	return m_Controller;
}

void APawn::SetController(AController* Controller)
{
	m_Controller = Controller;
}

void APawn::OnPlayerPossessed()
{

}

void APawn::OnPlayerUnpossessed()
{

}

void APawn::OnAIPossessed()
{

}

void APawn::OnAIUnpossessed()
{

}

void APawn::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);
}

void APawn::LateTick(float fDeltaTime)
{
	Super::LateTick(fDeltaTime);
}

void APawn::BeginPlay()
{
	Super::BeginPlay();
}

void APawn::Release()
{
	if (m_Controller)
	{
		m_Controller->SetPawn(nullptr);
		m_Controller = nullptr;
	}
}

APawn::~APawn()
{
	this->Release();
}
