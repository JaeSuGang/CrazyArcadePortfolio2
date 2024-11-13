#include "stdafx.h"
#include "KmEngine/RenderComponent.h"
#include "BombManager.h"
#include "MovementManager.h"
#include "Bomb.h"
#include "Character.h"

void ABomb::SetSpawner(ACharacter* Spawner)
{
	m_Spawner = Spawner;
}

ACharacter* ABomb::GetSpawner() const
{
	return m_Spawner;
}

float ABomb::GetTimer() const
{
	return m_fTimer;
}

void ABomb::SetTimer(float fTime)
{
	m_fTimer = fTime;
}

void ABomb::SetBombRange(int nRange)
{
	m_nBombRange = nRange;
}

int ABomb::GetBombRange() const
{
	return m_nBombRange;
}

void ABomb::BeginPlay()
{
	Super::BeginPlay();


}

void ABomb::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	URenderComponent* RenderComponent = GetComponentByClass<URenderComponent>();

	RenderComponent->PlayAnimation();

	if (m_fTimer < 0.0f)
	{
		this->OnExploded();
	}

	m_fTimer -= fDeltaTime;
}

void ABomb::LateTick(float fDeltaTime)
{
	Super::LateTick(fDeltaTime);

}

void ABomb::CheckAndHide()
{
	UMovementManager* MovementManager = GetGameInstance()->GetGameInstanceSubsystem<UMovementManager>();
	AActor* HidablePlace = MovementManager->GetIsInHidable(this);

	URenderComponent* RenderComponent = GetComponentByClass<URenderComponent>();
	if (HidablePlace)
		RenderComponent->SetIsHidden(true);
	else
		RenderComponent->SetIsHidden(false);
}

void ABomb::OnExploded()
{
	if (m_bIsAlreadyExploded)
		return;

	m_bIsAlreadyExploded = true;

	int CorrectBombTileLocationIndex = VectorToTileIndex(GetPosition());

	if (ACharacter* Spawner = GetSpawner())
		Spawner->SetBombLeft(Spawner->GetBombLeft() + 1);

	UBombManager* BombManager = GetGameInstance()->GetGameInstanceSubsystem<UBombManager>();
	BombManager->Explode(CorrectBombTileLocationIndex, m_nBombRange);

	this->Destroy();
}
