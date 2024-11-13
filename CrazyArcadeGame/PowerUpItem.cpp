#include "stdafx.h"
#include "PowerUpItem.h"
#include "BombManager.h"

void APowerUpItem::BeginPlay()
{
	Super::BeginPlay();

	UBombManager* BombManager = GetGameInstance()->GetGameInstanceSubsystem<UBombManager>();
	BombManager->AddExplodable(this);
}

void APowerUpItem::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);


}

void APowerUpItem::LateTick(float fDeltaTime)
{
	Super::LateTick(fDeltaTime);

}

void APowerUpItem::OnExploded()
{
}
