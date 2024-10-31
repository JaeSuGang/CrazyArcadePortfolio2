#include "stdafx.h"
#include "TestPlayer.h"
#include "KmEngine/RenderComponent.h"

void ATestPlayer::Initialize()
{
	URenderComponent* RenderComponent = InitializeComponentForPlay<URenderComponent>();
	RenderComponent->SetStaticImage("ResouRces\\Bazzi.BMP");
}

void ATestPlayer::Tick(float fDeltaTime)
{
}

void ATestPlayer::BeginPlay()
{
}
