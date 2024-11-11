#include "stdafx.h"
#include "Character.h"
#include "KmEngine/Engine.h"
#include "KmEngine/RenderComponent.h"
#include "KmEngine/KeyManager.h"
#include "KmEngine/TimeManager.h"
#include "KmEngine/KeyManager.h"
#include "BombManager.h"
#include "AIManager.h"
#include "InGameObjectComponent.h"

void ACharacter::SetBombCount(int nValue)
{
	m_nBombCount = nValue;
}

int ACharacter::GetBombCount() const
{
	return m_nBombCount;
}

void ACharacter::SetCharacterName(string strCharacterName)
{
	m_strCharacterName = strCharacterName;
}

string ACharacter::GetCharacterName()
{
	return m_strCharacterName;
}

void ACharacter::Move(FVector2D DirectionVector)
{
	if (m_bIsAlreadyMoving == false)
	{
		m_bIsAlreadyMoving = true;
		UInGameObjectComponent* InGameObjectComponent = GetComponentByClass<UInGameObjectComponent>();
		InGameObjectComponent->AddVelocity(DirectionVector * InGameObjectComponent->m_InGameObjectProperty.m_fSpeed);

		URenderComponent* RenderComponent = GetComponentByClass<URenderComponent>();
		if (!InGameObjectComponent->m_InGameObjectProperty.m_bIsAlreadyExploded)
		{
			if (DirectionVector == FVector2D::Up)
			{
				RenderComponent->PlayAnimation("UpWalk");
			}
			else if (DirectionVector == FVector2D::Right)
			{
				RenderComponent->PlayAnimation("RightWalk");
			}
			else if (DirectionVector == FVector2D::Left)
			{
				RenderComponent->PlayAnimation("LeftWalk");
			}
			else if (DirectionVector == FVector2D::Down)
			{
				RenderComponent->PlayAnimation("DownWalk");
			}
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

void ACharacter::TryPutBomb()
{
	UInGameObjectComponent* CharacterInGameObjectComponent = GetComponentByClass<UInGameObjectComponent>();

	int& nBombCountRef = CharacterInGameObjectComponent->m_InGameObjectProperty.m_nBombLeft;

	if (nBombCountRef <= 0)
		return;

	UBombManager* BombManager = GEngine->GetGameInstance()->GetGameInstanceSubsystem<UBombManager>();
	if (BombManager->TryPutBomb(VectorToTileIndex(this->GetPosition()), this))
		nBombCountRef--;
}

void ACharacter::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);


}

void ACharacter::BeginPlay()
{
	Super::BeginPlay();

}

ACharacter::ACharacter()
	:
	m_bIsAlreadyMoving{},
	m_strCharacterName{}
{

}

void ACharacter::OnAIPossessed()
{
	Super::OnAIPossessed();

	UAIManager* AIManager = GEngine->GetGameInstance()->GetGameInstanceSubsystem<UAIManager>();
	AIManager->AddAIPawn(this);
}

void ACharacter::OnPlayerPossessed()
{
	Super::OnPlayerPossessed();

	UKeyManager* km = GEngine->GetEngineSubsystem<UKeyManager>();
	km->BindKey(VK_UP, UKeyManager::EKeyState::Triggered, std::bind(&ACharacter::Move, this, FVector2D::Up));
	km->BindKey(VK_DOWN, UKeyManager::EKeyState::Triggered, std::bind(&ACharacter::Move, this, FVector2D::Down));
	km->BindKey(VK_RIGHT, UKeyManager::EKeyState::Triggered, std::bind(&ACharacter::Move, this, FVector2D::Right));
	km->BindKey(VK_LEFT, UKeyManager::EKeyState::Triggered, std::bind(&ACharacter::Move, this, FVector2D::Left));

	km->BindKey(VK_UP, UKeyManager::EKeyState::KeyUp, std::bind(&ACharacter::Idle, this, FVector2D::Up));
	km->BindKey(VK_DOWN, UKeyManager::EKeyState::KeyUp, std::bind(&ACharacter::Idle, this, FVector2D::Down));
	km->BindKey(VK_RIGHT, UKeyManager::EKeyState::KeyUp, std::bind(&ACharacter::Idle, this, FVector2D::Right));
	km->BindKey(VK_LEFT, UKeyManager::EKeyState::KeyUp, std::bind(&ACharacter::Idle, this, FVector2D::Left));

	km->BindKey(VK_SPACE, UKeyManager::EKeyState::KeyDown, std::bind(&ACharacter::TryPutBomb, this));


}

void ACharacter::LateTick(float fDeltaTime)
{
	Super::LateTick(fDeltaTime);

	m_bIsAlreadyMoving = false;
}
