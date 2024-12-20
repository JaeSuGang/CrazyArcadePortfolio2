#include "stdafx.h"
#include "Character.h"
#include "KmEngine/Engine.h"
#include "KmEngine/RenderComponent.h"
#include "KmEngine/TimeManager.h"
#include "KmEngine/KeyManager.h"
#include "KmEngine/Controller.h"
#include "KmEngine/SoundManager.h"
#include "KmEngine/PlayerController.h"
#include "MovementManager.h"
#include "BombManager.h"
#include "AIManager.h"
#include "CharacterAIController.h"
#include "GameLevelBase.h"
#include "SpawnManager.h"

void ACharacter::SetMaxStat()
{
	SetBombRange(6);
	SetBombLeft(6);
	SetSpeed(GetMaxSpeed());
}

void ACharacter::SwitchInvincible()
{
	if (!bIsInvincible)
		bIsInvincible = true;
	else
		bIsInvincible = false;
}

void ACharacter::SwitchNoclip()
{
	if (!bIsNoclip)
		bIsNoclip = true;
	else
		bIsNoclip = false;
}

void ACharacter::SetBombLeft(int nCount)
{
	m_nBombLeft = nCount;
}

void ACharacter::SetBombRange(int nRange)
{
	m_nBombRange = nRange;
}

void ACharacter::SetCharacterName(string strCharacterName)
{
	m_strCharacterName = strCharacterName;
}

void ACharacter::SetSpeed(float fSpeed)
{
	m_fSpeed = fSpeed;
}

void ACharacter::SetMaxSpeed(float fSpeed)
{
	m_fMaxSpeed = fSpeed;
}

float ACharacter::GetMaxSpeed() const
{
	return m_fMaxSpeed;
}

float ACharacter::GetSpeed() const
{
	return m_fSpeed;
}

int ACharacter::GetBombLeft() const
{
	return m_nBombLeft;
}

int ACharacter::GetBombRange() const
{
	return m_nBombRange;
}

string ACharacter::GetCharacterName() const
{
	return m_strCharacterName;
}

void ACharacter::Die()
{
	if (!m_bIsDead)
	{
		m_bIsDead = true;
		if (m_Controller)
		{
			if (APlayerController* CharacterController = dynamic_cast<APlayerController*>(m_Controller))
			{
				UKeyManager* KeyManager = GEngine->GetEngineSubsystem<UKeyManager>();
				KeyManager->ClearBindKey();
			}

			UAIManager* AIManager = GetGameInstance()->GetSubsystem<UAIManager>();
			USoundManager* SoundManager = GEngine->GetEngineSubsystem<USoundManager>();
			SoundManager->Play("Resources\\Sound\\die.wav");
			AIManager->RemoveAIPawn(this);
			m_Controller->SetPawn(nullptr);
			m_Controller = nullptr;
		}

	}
}

void ACharacter::Move(FVector2D DirectionVector)
{
	if (m_bIsMoving == false && !m_bIsDead)
	{
		m_bIsMoving = true;
		m_Velocity += (DirectionVector * m_fSpeed);

		if (!m_bIsAlreadyExploded)
		{
			URenderComponent* RenderComponent = GetComponentByClass<URenderComponent>();
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
	if (m_nBombLeft <= 0 || m_bIsDead || m_bIsAlreadyExploded)
		return;

	UBombManager* BombManager = GEngine->GetGameInstance()->GetSubsystem<UBombManager>();
	USoundManager* SoundManager = GEngine->GetEngineSubsystem<USoundManager>();
	if (BombManager->TryPutBomb(VectorToTileIndex(this->GetPosition()), this))
	{
		if (APlayerController* PlayerController = dynamic_cast<APlayerController*>(m_Controller))
			SoundManager->Play("Resources\\Sound\\bomb_set.wav");
		m_nBombLeft--;
	}
}

void ACharacter::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	if (m_Controller && m_Controller->GetComponentByClass<URenderComponent>())
	{
		m_Controller->SetPosition(this->GetPosition());
	}


	if (!m_bIsDead && m_bIsAlreadyExploded)
	{
		URenderComponent* RenderComponent = GetComponentByClass<URenderComponent>();

		if (m_fElapsedTimeAfterExplosion > 5.0f)
			this->Die();

		else if (m_fElapsedTimeAfterExplosion > 3.0f)
			RenderComponent->PlayAnimation("BubbleFade");

		else
			RenderComponent->PlayAnimation("BubbleLoop");

		m_fElapsedTimeAfterExplosion += fDeltaTime;
	}

	if (m_bIsDead)
	{
		int nFlicker = (int)(m_fElapsedTimeAfterDeath / 0.05f);
		URenderComponent* RenderComponent = GetComponentByClass<URenderComponent>();

		RenderComponent->PlayAnimation("Death");

		if (m_fElapsedTimeAfterDeath > 2.5f)
			this->Destroy();

		else if (m_fElapsedTimeAfterDeath > 0.5f)
		{
			if (nFlicker % 2 == 0)
				RenderComponent->SetIsHidden(true);
			else
				RenderComponent->SetIsHidden(false);
		}

		m_fElapsedTimeAfterDeath += fDeltaTime;
	}
}

void ACharacter::BeginPlay()
{
	Super::BeginPlay();

	UBombManager* BombManager = GetGameInstance()->GetSubsystem<UBombManager>();
	BombManager->AddCharacter(this);
	BombManager->AddExplodable(this);

	UMovementManager* MovementManager = GetGameInstance()->GetSubsystem<UMovementManager>();
	MovementManager->AddCharacter(this);
}

void ACharacter::OnDebug()
{
	URenderManager* RenderManager = GEngine->GetEngineSubsystem<URenderManager>();
	RenderManager->DrawDebugRectangle(m_Position, m_CollisionSize, m_hDebugPen);
	RenderManager->DrawDebugPosition(m_Position);
}

void ACharacter::Release()
{
	UBombManager* BombManager = GetGameInstance()->GetSubsystem<UBombManager>();
	BombManager->m_Characters.erase(this);
	BombManager->m_Explodables.erase(this);

	UMovementManager* MovementManager = GetGameInstance()->GetSubsystem<UMovementManager>();
	MovementManager->m_Characters.erase(this);

	if (m_Controller)
	{
		m_Controller->SetPawn(nullptr);
		if (ACharacterAIController* Casted = dynamic_cast<ACharacterAIController*>(m_Controller))
		{
			Casted->m_Character = nullptr;

		}
	}

	if (UGameLevelBase* CastedLevel = dynamic_cast<UGameLevelBase*>(GetLevel()))
	{
		CastedLevel->RemoveFromCharacters(this);
	}
}

ACharacter::~ACharacter()
{
	this->Release();
}

ACharacter::ACharacter()
	:
	m_strCharacterName{},
	m_nBombLeft{},
	m_nBombRange{},
	m_fSpeed{},
	m_bIsDead{},
	m_fElapsedTimeAfterDeath{},
	m_fMaxSpeed{},
	bIsInvincible{},
	bIsNoclip{}
{

}

void ACharacter::CheckAndHide()
{
	UMovementManager* MovementManager = GetGameInstance()->GetSubsystem<UMovementManager>();
	AActor* HidablePlace = MovementManager->GetIsInHidable(this);

	URenderComponent* RenderComponent = GetComponentByClass<URenderComponent>();
	if (HidablePlace)
		RenderComponent->SetIsHidden(true);
	else
		RenderComponent->SetIsHidden(false);
}

void ACharacter::OnExploded()
{
	if (bIsInvincible || m_bIsAlreadyExploded)
		return;

	USoundManager* SoundManager = GEngine->GetEngineSubsystem<USoundManager>();
	SoundManager->Play("Resources\\Sound\\got_bubbled.wav");

	m_bIsAlreadyExploded = true;
	m_fSpeed = 50.0f;


}

void ACharacter::OnAIPossessed()
{
	Super::OnAIPossessed();

	UAIManager* AIManager = GEngine->GetGameInstance()->GetSubsystem<UAIManager>();
	AIManager->AddAIPawn(this);
}

void ACharacter::OnAIUnpossessed()
{
	Super::OnAIUnpossessed();

	UAIManager* AIManager = GEngine->GetGameInstance()->GetSubsystem<UAIManager>();
	AIManager->RemoveAIPawn(this);
}

void ACharacter::OnPlayerPossessed()
{
	Super::OnPlayerPossessed();

	if (UGameLevelBase* GameLevelBase = dynamic_cast<UGameLevelBase*>(GetLevel()))
	{
		GameLevelBase->SetLocalPlayerCharacter(this);
	}

	UKeyManager* KeyManager = GEngine->GetEngineSubsystem<UKeyManager>();
	KeyManager->BindKey(VK_UP, UKeyManager::EKeyState::Triggered, std::bind(&ACharacter::Move, this, FVector2D::Up));
	KeyManager->BindKey(VK_DOWN, UKeyManager::EKeyState::Triggered, std::bind(&ACharacter::Move, this, FVector2D::Down));
	KeyManager->BindKey(VK_RIGHT, UKeyManager::EKeyState::Triggered, std::bind(&ACharacter::Move, this, FVector2D::Right));
	KeyManager->BindKey(VK_LEFT, UKeyManager::EKeyState::Triggered, std::bind(&ACharacter::Move, this, FVector2D::Left));

	KeyManager->BindKey(VK_UP, UKeyManager::EKeyState::KeyUp, std::bind(&ACharacter::Idle, this, FVector2D::Up));
	KeyManager->BindKey(VK_DOWN, UKeyManager::EKeyState::KeyUp, std::bind(&ACharacter::Idle, this, FVector2D::Down));
	KeyManager->BindKey(VK_RIGHT, UKeyManager::EKeyState::KeyUp, std::bind(&ACharacter::Idle, this, FVector2D::Right));
	KeyManager->BindKey(VK_LEFT, UKeyManager::EKeyState::KeyUp, std::bind(&ACharacter::Idle, this, FVector2D::Left));

	KeyManager->BindKey(VK_SPACE, UKeyManager::EKeyState::KeyDown, std::bind(&ACharacter::TryPutBomb, this));

	if (GetDebugMode())
	{
		USpawnManager* SpawnManager = GetGameInstance()->GetSubsystem<USpawnManager>();
		UBombManager* BombManager = GetGameInstance()->GetSubsystem<UBombManager>();
		KeyManager->BindKey('B', UKeyManager::EKeyState::KeyDown, std::bind(&ACharacter::SwitchInvincible, this));
		KeyManager->BindKey('N', UKeyManager::EKeyState::KeyDown, std::bind(&ACharacter::SwitchNoclip, this));
		KeyManager->BindKey('M', UKeyManager::EKeyState::KeyDown, std::bind(&ACharacter::SetMaxStat, this));
		KeyManager->BindKey('H', UKeyManager::EKeyState::KeyDown, std::bind(&UBombManager::ExpoldeAllCharacters, BombManager));
		KeyManager->BindKey('J', UKeyManager::EKeyState::KeyDown, std::bind(static_cast<ACharacterAIController*(USpawnManager::*)(ACharacter*)>(&USpawnManager::SpawnRandomAICharacter), SpawnManager, this));
	}
}

void ACharacter::OnPlayerUnpossessed()
{
	Super::OnPlayerUnpossessed();

	UKeyManager* km = GEngine->GetEngineSubsystem<UKeyManager>();
	km->ClearBindKey();
}

void ACharacter::LateTick(float fDeltaTime)
{
	Super::LateTick(fDeltaTime);

	m_bIsMoving = false;
}
