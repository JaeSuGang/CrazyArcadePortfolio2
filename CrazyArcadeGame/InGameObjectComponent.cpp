#include "stdafx.h"
#include "InGameObjectComponent.h"
#include "MovementManager.h"

const FInGameObjectProperty FInGameObjectProperty::Character = []()
	{
		FInGameObjectProperty Property{};
		Property.m_bIsCharacter = true;
		Property.m_CollisionSize = { 60.0f, 60.0f };
		Property.m_MaxVelocity = { 500.0f, 500.0f};
		Property.m_bIsExplodable = true;
		return Property;
	}();

const FInGameObjectProperty FInGameObjectProperty::HidableWall = []()
	{
		FInGameObjectProperty Property{};
		Property.m_bIsExplodable = true;
		Property.m_bCanBeFliedOver = true;
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

void UInGameObjectComponent::BeginPlay()
{
	Super::BeginPlay();

	UMovementManager* MovementManager = GetGameInstanceSubsystem<UMovementManager>();

	if (m_InGameObjectProperty.m_bIsCharacter)
		MovementManager->AddMovable(GetOwner());

	if (m_InGameObjectProperty.m_bBlockCharacter)
		MovementManager->AddWall(GetOwner());

}

void UInGameObjectComponent::TickComponent(float fDeltaTime)
{
	Super::TickComponent(fDeltaTime);
}
