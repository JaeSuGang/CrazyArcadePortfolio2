#include "stdafx.h"
#include "PowerUpItem.h"
#include "BombManager.h"
#include "MovementManager.h"

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


}

void APowerUpItem::LateTick(float fDeltaTime)
{
	Super::LateTick(fDeltaTime);

}

APowerUpItem::~APowerUpItem()
{
	UBombManager* BombManager = GetGameInstance()->GetGameInstanceSubsystem<UBombManager>();
	BombManager->m_Explodables.erase(this);

	UMovementManager* MovementManager = GetGameInstance()->GetGameInstanceSubsystem<UMovementManager>();
	MovementManager->m_PowerUpItems.erase(this);
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
