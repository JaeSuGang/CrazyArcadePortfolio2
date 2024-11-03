#include "stdafx.h"
#include "Character.h"
#include "KmEngine/Engine.h"
#include "KmEngine/RenderComponent.h"
#include "KmEngine/KeyManager.h"
#include "KmEngine/TimeManager.h"
#include "KmEngine/KeyManager.h"
#include "KmEngine/PhysicsComponent.h"

void ACharacter::SetCharacterName(string strCharacterName)
{
	m_strCharacterName = strCharacterName;
}

void ACharacter::Move(FVector2D DirectionVector)
{
	if (m_bIsAlreadyMoving == false)
	{
		m_bIsAlreadyMoving = true;
		UPhysicsComponent* PhysicsComponent = GetComponentByClass<UPhysicsComponent>();
		URenderComponent* RenderComponent = GetComponentByClass<URenderComponent>();
		PhysicsComponent->AddVelocity(DirectionVector * 300.0f);
		if (DirectionVector == FVector2D::Up)
		{
			string strAnimationName{ m_strCharacterName + "UpWalk"};
			RenderComponent->PlayAnimation(strAnimationName);
		}
		else if (DirectionVector == FVector2D::Right)
		{
			string strAnimationName{ m_strCharacterName + "RightWalk" };
			RenderComponent->PlayAnimation(strAnimationName);
		}
		else if (DirectionVector == FVector2D::Left)
		{
			string strAnimationName{ m_strCharacterName + "LeftWalk" };
			RenderComponent->PlayAnimation(strAnimationName);
		}
		else if (DirectionVector == FVector2D::Down)
		{
			string strAnimationName{ m_strCharacterName + "DownWalk" };
			RenderComponent->PlayAnimation(strAnimationName);
		}
	}
}

void ACharacter::Idle(FVector2D DirectionVector)
{
	URenderComponent* RenderComponent = GetComponentByClass<URenderComponent>();

	if (DirectionVector == FVector2D::Up)
	{
		RenderComponent->SetStaticImage("Resources\\" + m_strCharacterName + "\\UpIdle.bmp");
	}
	else if (DirectionVector == FVector2D::Right)
	{
		RenderComponent->SetStaticImage("Resources\\" + m_strCharacterName + "\\RightIdle.bmp");
	}
	else if (DirectionVector == FVector2D::Left)
	{
		RenderComponent->SetStaticImage("Resources\\" + m_strCharacterName + "\\LeftIdle.bmp");
	}
	else if (DirectionVector == FVector2D::Down)
	{
		RenderComponent->SetStaticImage("Resources\\" + m_strCharacterName + "\\DownIdle.bmp");
	}
}

//void ACharacter::Initialize()
//{
//	Super::Initialize();
//
//	URenderComponent* RenderComponent = InitializeComponentForPlay<URenderComponent>();
//	UPhysicsComponent* PhysicsComponent = InitializeComponentForPlay<UPhysicsComponent>();
//	PhysicsComponent->EnableCollision();
//	PhysicsComponent->SetColliderShape(FCollider::EShape::Square);
//	PhysicsComponent->SetColliderRadius(50.0f);
//	PhysicsComponent->SetMaxSpeed(300.0f);
//
//	RenderComponent->SetStaticImage("Resources\\" + m_strCharacterName + "\\" + "DownIdle.bmp");
//	RenderComponent->CreateAnimation(m_strCharacterName + "DownWalk", "Resources\\" + m_strCharacterName + "\\DownWalk", 4, 0.1f, true);
//	RenderComponent->CreateAnimation(m_strCharacterName + "LeftWalk", "Resources\\" + m_strCharacterName + "\\LeftWalk", 4, 0.1f, true);
//	RenderComponent->CreateAnimation( m_strCharacterName + "RightWalk", "Resources\\" + m_strCharacterName + "\\RightWalk", 4, 0.1f, true);
//	RenderComponent->CreateAnimation(m_strCharacterName + "UpWalk", "Resources\\" + m_strCharacterName + "\\UpWalk", 4, 0.1f, true);
//}

void ACharacter::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);


}

void ACharacter::BeginPlay()
{
	Super::BeginPlay();

	URenderComponent* RenderComponent = InitializeComponentForPlay<URenderComponent>();
	UPhysicsComponent* PhysicsComponent = InitializeComponentForPlay<UPhysicsComponent>();
	PhysicsComponent->EnableCollision();
	PhysicsComponent->SetColliderShape(FCollider::EShape::Square);
	PhysicsComponent->SetColliderRadius(50.0f);
	PhysicsComponent->SetMaxSpeed(300.0f);

	RenderComponent->SetStaticImage("Resources\\" + m_strCharacterName + "\\" + "DownIdle.bmp");
	RenderComponent->CreateAnimation(m_strCharacterName + "DownWalk", "Resources\\" + m_strCharacterName + "\\DownWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(m_strCharacterName + "LeftWalk", "Resources\\" + m_strCharacterName + "\\LeftWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(m_strCharacterName + "RightWalk", "Resources\\" + m_strCharacterName + "\\RightWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(m_strCharacterName + "UpWalk", "Resources\\" + m_strCharacterName + "\\UpWalk", 4, 0.1f, true);


	UKeyManager* km = GEngine->GetEngineSubsystem<UKeyManager>();
	km->BindKey(VK_UP, UKeyManager::EKeyState::Triggered, std::bind(&ACharacter::Move, this, FVector2D::Up));
	km->BindKey(VK_DOWN, UKeyManager::EKeyState::Triggered, std::bind(&ACharacter::Move, this, FVector2D::Down));
	km->BindKey(VK_RIGHT, UKeyManager::EKeyState::Triggered, std::bind(&ACharacter::Move, this, FVector2D::Right));
	km->BindKey(VK_LEFT, UKeyManager::EKeyState::Triggered, std::bind(&ACharacter::Move, this, FVector2D::Left));

	km->BindKey(VK_UP, UKeyManager::EKeyState::KeyUp, std::bind(&ACharacter::Idle, this, FVector2D::Up));
	km->BindKey(VK_DOWN, UKeyManager::EKeyState::KeyUp, std::bind(&ACharacter::Idle, this, FVector2D::Down));
	km->BindKey(VK_RIGHT, UKeyManager::EKeyState::KeyUp, std::bind(&ACharacter::Idle, this, FVector2D::Right));
	km->BindKey(VK_LEFT, UKeyManager::EKeyState::KeyUp, std::bind(&ACharacter::Idle, this, FVector2D::Left));


}

ACharacter::ACharacter()
	:
	m_bIsAlreadyMoving{},
	m_strCharacterName{}
{

}

void ACharacter::LateTick(float fDeltaTime)
{
	Super::LateTick(fDeltaTime);

	m_bIsAlreadyMoving = false;
}
