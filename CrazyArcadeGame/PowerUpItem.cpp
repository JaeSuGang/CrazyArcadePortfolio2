#include "stdafx.h"
#include "PowerUpItem.h"
#include "BombManager.h"
#include "MovementManager.h"
#include "KmEngine/RenderComponent.h"

void APowerUpItem::BeginPlay()
{
	Super::BeginPlay();

	UBombManager* BombManager = GetGameInstance()->GetGameInstanceSubsystem<UBombManager>();
	BombManager->AddExplodable(this);

	UMovementManager* MovementManager = GetGameInstance()->GetGameInstanceSubsystem<UMovementManager>();
	MovementManager->AddPowerUpItem(this);
}

void APowerUpItem::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	URenderComponent* RenderComponent = GetComponentByClass<URenderComponent>();
	RenderComponent->PlayAnimation();

	this->PlayFloatingAnimation();

	m_AccumulatedFloatingAnimationTime += fDeltaTime;
}

void APowerUpItem::LateTick(float fDeltaTime)
{
	Super::LateTick(fDeltaTime);

}

void APowerUpItem::Release()
{
	UBombManager* BombManager = GetGameInstance()->GetGameInstanceSubsystem<UBombManager>();
	BombManager->m_Explodables.erase(this);

	UMovementManager* MovementManager = GetGameInstance()->GetGameInstanceSubsystem<UMovementManager>();
	MovementManager->m_PowerUpItems.erase(this);
}

APowerUpItem::~APowerUpItem()
{
	this->Release();
}

void APowerUpItem::PlayFloatingAnimation()
{
	URenderComponent* RenderComponent = GetComponentByClass<URenderComponent>();

	if (m_AccumulatedFloatingAnimationTime > 1.5f)
		m_AccumulatedFloatingAnimationTime = 0.0f;

	else if (m_AccumulatedFloatingAnimationTime > 0.75f)
		RenderComponent->SetStaticImageOffset(FVector2D(0.0f, - 10.0f - m_AccumulatedFloatingAnimationTime * 20));

	else if (m_AccumulatedFloatingAnimationTime > 0.0f)
		RenderComponent->SetStaticImageOffset(FVector2D(0.0f, - 40.0f + m_AccumulatedFloatingAnimationTime * 20));
	}

void APowerUpItem::SetItemCode(EItemCode ItemCode)
{
	m_ItemCode = ItemCode;
}

EItemCode APowerUpItem::GetItemCode() const
{
	return m_ItemCode;
}

void APowerUpItem::OnExploded()
{
	this->Destroy();
}
