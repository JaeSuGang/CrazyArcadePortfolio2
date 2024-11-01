#include "stdafx.h"
#include "TestPlayer.h"
#include "KmEngine/Engine.h"
#include "KmEngine/RenderComponent.h"
#include "KmEngine/KeyManager.h"
#include "KmEngine/TimeManager.h"
#include "KmEngine/KeyManager.h"
#include "KmEngine/PhysicsComponent.h"

void ATestPlayer::Move(FVector2D DirectionVector)
{
	if (m_bIsAlreadyMoving == false)
	{
		m_bIsAlreadyMoving = true;

		UKeyManager* KeyManager = GEngine->GetEngineSubsystem<UKeyManager>();
		UTimeManager* TimeManager = GEngine->GetEngineSubsystem<UTimeManager>();
		UPhysicsComponent* PhysicsComponent = GetComponentByClass<UPhysicsComponent>();
		URenderComponent* RenderComponent = GetComponentByClass<URenderComponent>();
		PhysicsComponent->AddVelocity(DirectionVector * TimeManager->GetDeltaTime() * 300.0f);
		if (DirectionVector == FVector2D::Up)
		{
			RenderComponent->PlayAnimation("BazziUpWalk");
		}
		else if (DirectionVector == FVector2D::Right)
		{
			RenderComponent->PlayAnimation("BazziRightWalk");
		}
		else if (DirectionVector == FVector2D::Left)
		{
			RenderComponent->PlayAnimation("BazziLeftWalk");
		}
		else if (DirectionVector == FVector2D::Down)
		{
			RenderComponent->PlayAnimation("BazziDownWalk");
		}
	}
}

void ATestPlayer::Idle(FVector2D DirectionVector)
{
	URenderComponent* RenderComponent = GetComponentByClass<URenderComponent>();

	if (DirectionVector == FVector2D::Up)
	{
		RenderComponent->SetStaticImage("Resources\\Bazzi\\BazziUpIdle.bmp");
	}
	else if (DirectionVector == FVector2D::Right)
	{
		RenderComponent->SetStaticImage("Resources\\Bazzi\\BazziRightIdle.bmp");
	}
	else if (DirectionVector == FVector2D::Left)
	{
		RenderComponent->SetStaticImage("Resources\\Bazzi\\BazziLeftIdle.bmp");
	}
	else if (DirectionVector == FVector2D::Down)
	{
		RenderComponent->SetStaticImage("Resources\\Bazzi\\BazziDownIdle.bmp");
	}
}

void ATestPlayer::Initialize()
{
	Super::Initialize();

	URenderComponent* RenderComponent = InitializeComponentForPlay<URenderComponent>();
	UPhysicsComponent* PhysicsComponent = InitializeComponentForPlay<UPhysicsComponent>();
	RenderComponent->SetStaticImage("Resources\\Bazzi\\BazziDownIdle.bmp");
	PhysicsComponent->SetMaxSpeed(300.0f);

	RenderComponent->CreateAnimation("BazziDownWalk", "Resources\\Bazzi\\BazziDownWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("BazziLeftWalk", "Resources\\Bazzi\\BazziLeftWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("BazziRightWalk", "Resources\\Bazzi\\BazziRightWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation("BazziUpWalk", "Resources\\Bazzi\\BazziUpWalk", 4, 0.1f, true);
}

void ATestPlayer::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);


}

void ATestPlayer::BeginPlay()
{
	Super::BeginPlay();

	UKeyManager* km = GEngine->GetEngineSubsystem<UKeyManager>();
	km->BindKey(VK_UP, UKeyManager::EKeyState::Triggered, std::bind(&ATestPlayer::Move, this, FVector2D::Up));
	km->BindKey(VK_DOWN, UKeyManager::EKeyState::Triggered, std::bind(&ATestPlayer::Move, this, FVector2D::Down));
	km->BindKey(VK_RIGHT, UKeyManager::EKeyState::Triggered, std::bind(&ATestPlayer::Move, this, FVector2D::Right));
	km->BindKey(VK_LEFT, UKeyManager::EKeyState::Triggered, std::bind(&ATestPlayer::Move, this, FVector2D::Left));

	km->BindKey(VK_UP, UKeyManager::EKeyState::KeyUp, std::bind(&ATestPlayer::Idle, this, FVector2D::Up));
	km->BindKey(VK_DOWN, UKeyManager::EKeyState::KeyUp, std::bind(&ATestPlayer::Idle, this, FVector2D::Down));
	km->BindKey(VK_RIGHT, UKeyManager::EKeyState::KeyUp, std::bind(&ATestPlayer::Idle, this, FVector2D::Right));
	km->BindKey(VK_LEFT, UKeyManager::EKeyState::KeyUp, std::bind(&ATestPlayer::Idle, this, FVector2D::Left));


}

void ATestPlayer::LateTick(float fDeltaTime)
{
	Super::LateTick(fDeltaTime);

	m_bIsAlreadyMoving = false;
}
