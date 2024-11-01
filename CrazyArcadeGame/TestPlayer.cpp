#include "stdafx.h"
#include "TestPlayer.h"
#include "KmEngine/Engine.h"
#include "KmEngine/RenderComponent.h"
#include "KmEngine/KeyManager.h"
#include "KmEngine/TimeManager.h"
#include "KmEngine/KeyManager.h"
#include "KmEngine/PhysicsComponent.h"

void ATestPlayer::Move(FVector2D Direction)
{
	UKeyManager* KeyManager = GEngine->GetEngineSubsystem<UKeyManager>();
	UTimeManager* TimeManager = GEngine->GetEngineSubsystem<UTimeManager>();
	UPhysicsComponent* PhysicsComponent = GetComponentByClass<UPhysicsComponent>();
	PhysicsComponent->AddVelocity(Direction * TimeManager->GetDeltaTime() * 200.0f);
}

void ATestPlayer::Initialize()
{
	URenderComponent* RenderComponent = InitializeComponentForPlay<URenderComponent>();
	UPhysicsComponent* PhysicsComponent = InitializeComponentForPlay<UPhysicsComponent>();
	RenderComponent->SetStaticImage("bazzidownidle.BMP");
	PhysicsComponent->SetMaxSpeed(200.0f);
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
