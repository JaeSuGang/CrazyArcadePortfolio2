#include "stdafx.h"
#include "TestPlayer.h"
#include "KmEngine/Engine.h"
#include "KmEngine/RenderComponent.h"
#include "KmEngine/TimeManager.h"
#include "KmEngine/KeyManager.h"

void ATestPlayer::Move(FVector2D Direction)
{
	UTimeManager* TimeManager = GEngine->GetEngineSubsystem<UTimeManager>();
	m_Position +=  Direction * TimeManager->GetDeltaTime() * 300.0f;
}

void ATestPlayer::Initialize()
{
	URenderComponent* RenderComponent = InitializeComponentForPlay<URenderComponent>();
	RenderComponent->SetStaticImage("bazzidownidle.BMP");
}

void ATestPlayer::Tick(float fDeltaTime)
{
}

void ATestPlayer::BeginPlay()
{
	UKeyManager* km = GEngine->GetEngineSubsystem<UKeyManager>();
	km->BindKey(VK_UP, UKeyManager::EKeyState::Triggered, std::bind(&ATestPlayer::Move, this, FVector2D::Up));
	km->BindKey(VK_DOWN, UKeyManager::EKeyState::Triggered, std::bind(&ATestPlayer::Move, this, FVector2D::Down));
	km->BindKey(VK_LEFT, UKeyManager::EKeyState::Triggered, std::bind(&ATestPlayer::Move, this, FVector2D::Left));
	km->BindKey(VK_RIGHT, UKeyManager::EKeyState::Triggered, std::bind(&ATestPlayer::Move, this, FVector2D::Right));
}
