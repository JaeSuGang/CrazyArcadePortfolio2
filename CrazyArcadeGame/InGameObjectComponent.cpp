#include "stdafx.h"
#include "InGameObjectComponent.h"
#include "KmEngine/Actor.h"
#include "KmEngine/RenderComponent.h"
#include "MovementManager.h"
#include "BombManager.h"
#include "SpawnManager.h"



const FInGameObjectProperty FInGameObjectProperty::Character = []()
	{
		FInGameObjectProperty Property{};
		Property.m_bIsCharacter = true;
		Property.m_nBombLeft = 10;
		Property.m_nBombRange = 4;
		Property.m_fSpeed = 200.0f;
		Property.m_CollisionSize = { 60.0f, 60.0f };
		Property.m_bIsExplodable = true;
		return Property;
	}();

const FInGameObjectProperty FInGameObjectProperty::Explosion = []()
	{
		FInGameObjectProperty Property{};
		Property.m_CollisionSize = { 60.0f, 60.0f };
		Property.m_fTimer = 0.4f;
		Property.m_bIsExplosion = true;
		Property.m_bIsAlreadyExploded = true;
		return Property;
	}();

const FInGameObjectProperty FInGameObjectProperty::Bomb = []()
	{
		FInGameObjectProperty Property{};
		Property.m_fTimer = 3.0f;
		Property.m_bIsBomb = true;
		Property.m_bBlockCharacter = true;
		Property.m_bIsExplodable = true;
		Property.m_bCanBeFliedOver = true;
		Property.m_CollisionSize = { 60.0f, 60.0f };
		return Property;
	}();

const FInGameObjectProperty FInGameObjectProperty::HidableWall = []()
	{
		FInGameObjectProperty Property{};
		Property.m_bIsExplodable = true;
		Property.m_bIsHidablePlace = true;
		return Property;
	}();

const FInGameObjectProperty FInGameObjectProperty::ExplodableWall = []()
	{
		FInGameObjectProperty Property{};
		Property.m_bBlockCharacter = true;
		Property.m_bIsExplodable = true;
		Property.m_bCanBeFliedOver = true;
		Property.m_CollisionSize = { 60.0f, 60.0f };
		return Property;
	}();

const FInGameObjectProperty FInGameObjectProperty::MovableWall = []()
	{
		FInGameObjectProperty Property{};
		Property.m_bBlockCharacter = true;
		Property.m_bIsExplodable = true;
		Property.m_bIsPushable = true;
		Property.m_bCanBeFliedOver = true;
		Property.m_CollisionSize = { 60.0f, 60.0f };
		return Property;
	}();

const FInGameObjectProperty FInGameObjectProperty::NonExplodableWall = []()
	{
		FInGameObjectProperty Property{};
		Property.m_bBlockCharacter = true;
		Property.m_CollisionSize = { 60.0f, 60.0f };
		return Property;
	}();



void UInGameObjectComponent::PlayFadeAnimation()
{
	int nFlicker = (int)(m_InGameObjectProperty.m_fElapsedTimeAfterExplosion / 0.02f);
	
	if (nFlicker % 2 == 0)
		GetOwner()->GetComponentByClass<URenderComponent>()->SetIsHidden(true);
	else
		GetOwner()->GetComponentByClass<URenderComponent>()->SetIsHidden(false);
}

void UInGameObjectComponent::AddVelocity(FVector2D VelocityToAdd)
{
	m_InGameObjectProperty.m_Velocity += VelocityToAdd;
}

void UInGameObjectComponent::AddOnExplodedEvent(std::function<void()> Event)
{
	m_OnExplodedEvents.push_back(Event);
}

void UInGameObjectComponent::OnExploded()
{
	if (m_InGameObjectProperty.m_bIsAlreadyExploded)
		return;

	else
		m_InGameObjectProperty.m_bIsAlreadyExploded = true;

	if (m_InGameObjectProperty.m_bIsExplodable)
	{
		for (std::function<void()> Event : m_OnExplodedEvents)
		{
			Event();
		}
 	}
}

void UInGameObjectComponent::OnExploded_Character()
{
	m_InGameObjectProperty.m_fSpeed = 25.0f;
}

void UInGameObjectComponent::OnExploded_Bomb()
{
	AActor* BombActor = GetOwner();
	int CorrectBombTileLocationIndex = VectorToTileIndex(BombActor->GetPosition());

	if (m_InGameObjectProperty.m_Spawner)
	{
		UInGameObjectComponent* SpawnerInGameObjectComponent = m_InGameObjectProperty.m_Spawner->GetComponentByClass<UInGameObjectComponent>();
		SpawnerInGameObjectComponent->m_InGameObjectProperty.m_nBombLeft++;
	}

	UBombManager* BombManager = GetGameInstanceSubsystem<UBombManager>();
	BombManager->Explode(CorrectBombTileLocationIndex, m_InGameObjectProperty.m_nBombRange);

	BombActor->Destroy();
}

void UInGameObjectComponent::OnExploded_Block()
{
	// 아이템 확률 생성 코드 추가하기


}

void UInGameObjectComponent::OnExploded_Hidable()
{
	GetOwner()->Destroy();
}

void UInGameObjectComponent::BeginPlay()
{
	Super::BeginPlay();

	UMovementManager* MovementManager = GetGameInstanceSubsystem<UMovementManager>();
	UBombManager* BombManager = GetGameInstanceSubsystem<UBombManager>();

	if (m_InGameObjectProperty.m_bIsCharacter)
	{
		MovementManager->AddMovable(this->GetOwner());
		std::function<void()> Event1 = std::bind(&UInGameObjectComponent::OnExploded_Character, this);
		this->m_OnExplodedEvents.push_back(Event1);
	}

	if (m_InGameObjectProperty.m_bBlockCharacter)
	{
		MovementManager->AddWall(this->GetOwner());
		std::function<void()> Event1 = std::bind(&UInGameObjectComponent::OnExploded_Block, this);
		this->m_OnExplodedEvents.push_back(Event1);
	}

	if (m_InGameObjectProperty.m_bIsBomb)
	{
		MovementManager->AddWall(GetOwner());
		std::function<void()> Event1 = std::bind(&UInGameObjectComponent::OnExploded_Bomb, this);
		this->m_OnExplodedEvents.push_back(Event1);
	}

	if (m_InGameObjectProperty.m_bIsHidablePlace)
	{
		std::function<void()> Event1 = std::bind(&UInGameObjectComponent::OnExploded_Hidable, this);
		this->m_OnExplodedEvents.push_back(Event1);
	}

	if (m_InGameObjectProperty.m_bIsExplosion)
	{
		BombManager->AddExplosion(GetOwner());
	}

}

void UInGameObjectComponent::TickComponent(float fDeltaTime)
{
	Super::TickComponent(fDeltaTime);

	AActor* Owner = this->GetOwner();
	URenderComponent* RenderComponent = Owner->GetComponentByClass<URenderComponent>();

	if (m_InGameObjectProperty.m_fTimer > 0)
		m_InGameObjectProperty.m_fTimer -= fDeltaTime;

	if (m_InGameObjectProperty.m_bIsAlreadyExploded)
	{
		if (m_InGameObjectProperty.m_bBlockCharacter)
			this->PlayFadeAnimation();

		m_InGameObjectProperty.m_fElapsedTimeAfterExplosion += fDeltaTime;
	}

	if (m_InGameObjectProperty.m_fElapsedTimeAfterExplosion > 0.4f && !m_InGameObjectProperty.m_bIsCharacter)
		Owner->Destroy();

	if (m_InGameObjectProperty.m_bIsCharacter)
		this->Tick_Character(fDeltaTime);

	if (m_InGameObjectProperty.m_bIsBomb)
		this->Tick_Bomb(fDeltaTime);

	if (m_InGameObjectProperty.m_bIsExplosion)
		this->Tick_Explosion(fDeltaTime);
}

void UInGameObjectComponent::Tick_Explosion(float fDeltaTime)
{
	AActor* Owner = this->GetOwner();
	URenderComponent* RenderComponent = Owner->GetComponentByClass<URenderComponent>();
	if (m_InGameObjectProperty.m_fTimer > 0.1)
	{
		RenderComponent->PlayAnimation("ExplosionLoop");
	}

	else if (m_InGameObjectProperty.m_fTimer > 0.0)
	{
		RenderComponent->PlayAnimation("ExplosionFade");
	}
}

void UInGameObjectComponent::Tick_Bomb(float fDeltaTime)
{
	AActor* Owner = this->GetOwner();
	URenderComponent* RenderComponent = Owner->GetComponentByClass<URenderComponent>();

	RenderComponent->PlayAnimation();

	if (m_InGameObjectProperty.m_fTimer < 0.0f)
	{
		this->OnExploded();
	}
}

void UInGameObjectComponent::Tick_Character(float fDeltaTime)
{
	if (m_InGameObjectProperty.m_bIsAlreadyExploded)
	{
		URenderComponent* RenderComponent = GetOwner()->GetComponentByClass<URenderComponent>();
		if (m_InGameObjectProperty.m_fElapsedTimeAfterExplosion > 3.0f)
		{
			RenderComponent->PlayAnimation("BubbleFade");
		}
		else if (m_InGameObjectProperty.m_fElapsedTimeAfterExplosion > 0.0f)
		{
			RenderComponent->PlayAnimation("BubbleLoop");
		}
	}
}

void UInGameObjectComponent::Release()
{
	UMovementManager* MovementManager = GetGameInstanceSubsystem<UMovementManager>();
	UBombManager* BombManager = GetGameInstanceSubsystem<UBombManager>();
	MovementManager->m_Walls.erase(m_Owner);
	MovementManager->m_Movables.erase(m_Owner);
	MovementManager->m_Explosions.erase(m_Owner);
	BombManager->m_Explosions.erase(m_Owner);
}

UInGameObjectComponent::~UInGameObjectComponent()
{
	this->Release();
}
