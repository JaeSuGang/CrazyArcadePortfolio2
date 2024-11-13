#include "stdafx.h"
#include "Explosion.h"
#include "KmEngine/RenderComponent.h"
#include "BombManager.h"

void AExplosion::SetTimer(float fTime)
{
	m_fTimer = fTime;
}

float AExplosion::GetTimer() const
{
	return m_fTimer;
}

void AExplosion::BeginPlay()
{
	Super::BeginPlay();

	UBombManager* BombManager = GetGameInstance()->GetGameInstanceSubsystem<UBombManager>();
	BombManager->AddExplosion(this);
}

void AExplosion::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	// Render
	URenderComponent* RenderComponent = GetComponentByClass<URenderComponent>();
	if (m_fTimer > 0.1)
		RenderComponent->PlayAnimation("ExplosionLoop");
	else if (m_fTimer > 0.0)
		RenderComponent->PlayAnimation("ExplosionFade");
	else
		this->Destroy();

	m_fTimer -= fDeltaTime;
}

void AExplosion::LateTick(float fDeltaTime)
{
	Super::LateTick(fDeltaTime);

}

void AExplosion::Release()
{
	UBombManager* BombManager = GetGameInstance()->GetGameInstanceSubsystem<UBombManager>();
	BombManager->m_Explosions.erase(this);
}

AExplosion::~AExplosion()
{
	this->Release();
}
