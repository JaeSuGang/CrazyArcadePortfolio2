#include "stdafx.h"
#include "LobbyLevel.h"
#include "GameUI.h"
#include "KmEngine/RenderComponent.h"

void ULobbyLevel::ChangeLevelState(ELevelState LevelState)
{

}

void ULobbyLevel::AddLevelEvent(std::function<void()> Function, float fElapseTimeToTrigger)
{
}

void ULobbyLevel::AddLevelEvent(FLevelEvent LevelEvent)
{
	m_Events.push_back(LevelEvent);
}

void ULobbyLevel::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	for (ULobbyLevel::FLevelEvent LevelEvent : m_Events)
	{
		if (m)
	}

	m_fElapsedTime += fDeltaTime;
}

void ULobbyLevel::LateTick(float fDeltaTime)
{
	Super::LateTick(fDeltaTime);

}

void ULobbyLevel::BeginPlay()
{
	Super::BeginPlay();

	AGameUI* LoginScreen = this->InitializeActorForPlay<AGameUI>();
	LoginScreen->SetPosition(FVector2D(599.0f, 449.0f));
	URenderComponent* Renderer = LoginScreen->CreateDefaultSubobject<URenderComponent>();
	Renderer->SetStaticImage("Resources\\UI\\login.bmp");
	LoginScreen->BeginPlay();
}
