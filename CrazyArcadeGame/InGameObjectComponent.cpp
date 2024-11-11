#include "stdafx.h"
#include "InGameObjectComponent.h"
#include "KmEngine/Actor.h"
#include "KmEngine/RenderComponent.h"
#include "MovementManager.h"
#include "BombManager.h"

const FInGameObjectProperty FInGameObjectProperty::Character = []()
	{
		FInGameObjectProperty Property{};
		Property.m_bIsCharacter = true;
		Property.m_nBombLeft = 1;
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
	for (std::function<void()> Event : m_OnExplodedEvents)
	{
		Event();
	}
}

void UInGameObjectComponent::OnExploded_Bomb()
{
	if (m_InGameObjectProperty.m_bIsAlreadyExploded)
		return;

	if (m_InGameObjectProperty.m_Spawner)
	{
		UInGameObjectComponent* SpawnerInGameObjectComponent = m_InGameObjectProperty.m_Spawner->GetComponentByClass<UInGameObjectComponent>();
		SpawnerInGameObjectComponent->m_InGameObjectProperty.m_nBombLeft++;
	}

	GetOwner()->Destroy();
}

void UInGameObjectComponent::BeginPlay()
{
	Super::BeginPlay();

	UMovementManager* MovementManager = GetGameInstanceSubsystem<UMovementManager>();
	UBombManager* BombManager = GetGameInstanceSubsystem<UBombManager>();

	if (m_InGameObjectProperty.m_bIsCharacter)
		MovementManager->AddMovable(this->GetOwner());

	if (m_InGameObjectProperty.m_bBlockCharacter)
		MovementManager->AddWall(this->GetOwner());

	if (m_InGameObjectProperty.m_bIsBomb)
	{
		MovementManager->AddWall(GetOwner());
		BombManager->m_Bombs.insert(this->GetOwner());
		std::function<void()> Event1 = std::bind(&UInGameObjectComponent::OnExploded_Bomb, this);
		this->m_OnExplodedEvents.push_back(Event1);
	}

	if (m_InGameObjectProperty.m_bIsExplosion)
	{
		MovementManager->AddExplosion(GetOwner());
	}
}

void UInGameObjectComponent::TickComponent(float fDeltaTime)
{
	Super::TickComponent(fDeltaTime);
	AActor* Owner = this->GetOwner();
	URenderComponent* RenderComponent = Owner->GetComponentByClass<URenderComponent>();

	if (m_InGameObjectProperty.m_bIsBomb)
	{
		m_InGameObjectProperty.m_fTimer -= fDeltaTime;
		RenderComponent->PlayAnimation();
	}

	else if (m_InGameObjectProperty.m_bIsExplosion)
	{
		m_InGameObjectProperty.m_fTimer -= fDeltaTime;
		RenderComponent->PlayAnimation();
	}
}

void UInGameObjectComponent::Release()
{
	UMovementManager* MovementManager = GetGameInstanceSubsystem<UMovementManager>();
	UBombManager* BombManager = GetGameInstanceSubsystem<UBombManager>();
	MovementManager->m_Walls.erase(m_Owner);
	MovementManager->m_Movables.erase(m_Owner);
	MovementManager->m_Explosions.erase(m_Owner);
	BombManager->m_Bombs.erase(m_Owner);
}

UInGameObjectComponent::~UInGameObjectComponent()
{
	this->Release();
}
