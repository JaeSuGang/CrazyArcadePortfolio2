#include "stdafx.h"
#include "Pawn.h"

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

void APawn::OnAIPossessed()
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
