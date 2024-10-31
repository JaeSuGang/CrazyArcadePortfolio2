#include "stdafx.h"
#include "TestPlayer.h"
#include "RenderComponent.h"

void ATestPlayer::Initialize()
{
	Super::Initialize();

	AddComponent<URenderComponent>();
}

void ATestPlayer::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);


}

void ATestPlayer::BeginPlay()
{
	Super::BeginPlay();

	URenderComponent* RenderComponent = GetComponentByClass<URenderComponent>();
	RenderComponent->SetStaticImage("reSouRcEs\\baZzi.BMP");
}
