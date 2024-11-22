#include "stdafx.h"
#include "LobbyLevel.h"
#include "GameUI.h"
#include "KmEngine/RenderComponent.h"

void ULobbyLevel::ChangeLevelState(ELevelState LevelState)
{
	switch (LevelState)
	{
	case ULobbyLevel::ELevelState::Login:
	{
		for (AActor* Actor : m_Actors)
			Actor->Destroy();

		AGameUI* LoginScreen = this->InitializeActorForPlay<AGameUI>();
		LoginScreen->SetPosition(FVector2D(599.0f, 449.0f));
		URenderComponent* Renderer = LoginScreen->CreateDefaultSubobject<URenderComponent>();
		Renderer->SetRenderType(URenderComponent::ERenderType::UI);
		Renderer->SetStaticImage("Resources\\UI\\login.bmp");
		LoginScreen->BeginPlay();
		break;
	}
	case ULobbyLevel::ELevelState::Lobby:
	{
		for (AActor* Actor : m_Actors)
			Actor->Destroy();

		AGameUI* LobbyScreen = this->InitializeActorForPlay<AGameUI>();
		LobbyScreen->SetPosition(FVector2D(599.0f, 449.0f));
		URenderComponent* Renderer = LobbyScreen->CreateDefaultSubobject<URenderComponent>();
		Renderer->SetStaticImage("Resources\\UI\\mainlobby_0.bmp");
		Renderer->SetRenderType(URenderComponent::ERenderType::UI);
		LobbyScreen->BeginPlay();

		this->AddLevelEvent(std::bind(&ULobbyLevel::ChangeLevelState, this, ULobbyLevel::ELevelState::Lobby_Tutorial), 0.5f);
		break;
	}
	case ULobbyLevel::ELevelState::Lobby_Tutorial:
	{
		for (AActor* Actor : m_Actors)
			Actor->Destroy();

		AGameUI* LobbyScreen = this->InitializeActorForPlay<AGameUI>();
		LobbyScreen->SetPosition(FVector2D(599.0f, 449.0f));
		URenderComponent* LobbyScreenRenderer = LobbyScreen->CreateDefaultSubobject<URenderComponent>();
		LobbyScreenRenderer->SetStaticImage("Resources\\UI\\mainlobby_1.bmp");
		LobbyScreenRenderer->SetRenderType(URenderComponent::ERenderType::UI);
		LobbyScreenRenderer->SetRenderPriority(1);
		LobbyScreen->BeginPlay();

		AGameUI* TutorialArrow = this->InitializeActorForPlay<AGameUI>();
		TutorialArrow->SetPosition(FVector2D(1100.0f, 60.0f));
		URenderComponent* ArrowRenderer = TutorialArrow->CreateDefaultSubobject<URenderComponent>();
		ArrowRenderer->SetStaticImage("Resources\\UI\\arrow.bmp");
		ArrowRenderer->SetRenderType(URenderComponent::ERenderType::UI);
		ArrowRenderer->SetRenderPriority(2);
		TutorialArrow->BeginPlay();

		break;
	}
	default:
		break;
	}
}

void ULobbyLevel::AddLevelEvent(std::function<void()> Function, float fElapseTimeToTrigger)
{
	FLevelEvent LevelEvent{};
	LevelEvent.m_nUUID = (float)rand();
	LevelEvent.m_Function = Function;
	LevelEvent.m_fElapsedTimeToTrigger = m_fElapseTime + fElapseTimeToTrigger;

	m_Events.insert(LevelEvent);
}


void ULobbyLevel::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	auto EventIter = m_Events.begin();

	while (EventIter != m_Events.end())
	{
		if (m_fElapseTime > EventIter->m_fElapsedTimeToTrigger)
		{
			EventIter->m_Function();
			EventIter = m_Events.erase(EventIter);
		}
		else
			++EventIter;
	}

	m_fElapseTime += fDeltaTime;
}

void ULobbyLevel::LateTick(float fDeltaTime)
{
	Super::LateTick(fDeltaTime);

}

void ULobbyLevel::BeginPlay()
{
	Super::BeginPlay();

	this->ChangeLevelState(ULobbyLevel::ELevelState::Login);

	this->AddLevelEvent(std::bind(&ULobbyLevel::ChangeLevelState, this, ULobbyLevel::ELevelState::Lobby), 3.0f);
}

bool ULobbyLevel::FLevelEvent::operator==(const FLevelEvent& Other) const
{
	return m_fElapsedTimeToTrigger == Other.m_fElapsedTimeToTrigger && m_nUUID == Other.m_nUUID;
}

std::size_t ULobbyLevel::FLevelEventHash::operator()(const FLevelEvent& Event) const
{
	std::size_t h1 = std::hash<float>()(Event.m_fElapsedTimeToTrigger);
	std::size_t h2 = std::hash<float>()(Event.m_nUUID);

	return h1 ^ (h2 << 1);
}
