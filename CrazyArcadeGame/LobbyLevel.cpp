#include "stdafx.h"
#include "LobbyLevel.h"
#include "GameUI.h"
#include "KmEngine/Engine.h"
#include "KmEngine/RenderComponent.h"
#include "KmEngine/SoundManager.h"
#include "KmEngine/KeyManager.h"

void ULobbyLevel::ChangeLevelState(ELevelState LevelState)
{
	this->m_LevelState = LevelState;

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
		USoundManager* SoundManager = GEngine->GetEngineSubsystem<USoundManager>();
		SoundManager->Play("Resources\\Sound\\lobbybgm.wav");
		LobbyScreen->BeginPlay();

		this->AddLevelTimeEvent(std::bind(&ULobbyLevel::ChangeLevelState, this, ULobbyLevel::ELevelState::Lobby_Tutorial), 0.5f);
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
	case ULobbyLevel::ELevelState::Room:
	{

		for (AActor* Actor : m_Actors)
			Actor->Destroy();

		AGameUI* RoomScreen = this->InitializeActorForPlay<AGameUI>();
		RoomScreen->SetPosition(FVector2D(599.0f, 449.0f));
		URenderComponent* RoomScreenRenderComponent = RoomScreen->CreateDefaultSubobject<URenderComponent>();
		RoomScreenRenderComponent->SetStaticImage("Resources\\UI\\gamelobby.bmp");
		RoomScreenRenderComponent->SetRenderType(URenderComponent::ERenderType::UI);
		RoomScreenRenderComponent->SetRenderPriority(1);
		USoundManager* SoundManager = GEngine->GetEngineSubsystem<USoundManager>();
		SoundManager->StopAllSounds();
		SoundManager->Play("Resources\\Sound\\roombgm.wav");
		RoomScreen->BeginPlay();
		break;
	}
	default:
		break;
	}
}

void ULobbyLevel::AddLevelTimeEvent(std::function<void()> Function, float fElapseTimeToTrigger)
{
	FTimeEvent LevelEvent{};
	LevelEvent.m_nUUID = (float)rand();
	LevelEvent.m_Function = Function;
	LevelEvent.m_fElapsedTimeToTrigger = m_fElapseTime + fElapseTimeToTrigger;

	m_TimeEvents.insert(LevelEvent);
}

void ULobbyLevel::OnClicked()
{
	UKeyManager* KeyManager = GEngine->GetEngineSubsystem<UKeyManager>();

	switch (this->m_LevelState)
	{
	case ELevelState::Lobby_Tutorial:
	{
		if (KeyManager->GetMousePos().X > 1025 && KeyManager->GetMousePos().X < 1172 &&
			KeyManager->GetMousePos().Y > 117 && KeyManager->GetMousePos().Y < 152)
		{
			this->ChangeLevelState(ULobbyLevel::ELevelState::Room);
		}
		break;
	}

	default:
		break;
	}
}


void ULobbyLevel::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	auto EventIter = m_TimeEvents.begin();

	while (EventIter != m_TimeEvents.end())
	{
		if (m_fElapseTime > EventIter->m_fElapsedTimeToTrigger)
		{
			EventIter->m_Function();
			EventIter = m_TimeEvents.erase(EventIter);
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

	UKeyManager* KeyManager = GEngine->GetEngineSubsystem<UKeyManager>();

	KeyManager->BindKey(VK_LBUTTON, UKeyManager::EKeyState::KeyDown, std::bind(&ULobbyLevel::OnClicked, this));

	this->ChangeLevelState(ULobbyLevel::ELevelState::Login);

	this->AddLevelTimeEvent(std::bind(&USoundManager::Play, GEngine->GetEngineSubsystem<USoundManager>(), "Resources\\Sound\\click.wav"), 2.5f);

	this->AddLevelTimeEvent(std::bind(&ULobbyLevel::ChangeLevelState, this, ULobbyLevel::ELevelState::Lobby), 3.0f);
}

bool ULobbyLevel::FTimeEvent::operator==(const FTimeEvent& Other) const
{
	return m_fElapsedTimeToTrigger == Other.m_fElapsedTimeToTrigger && m_nUUID == Other.m_nUUID;
}

std::size_t ULobbyLevel::FTimeEventHash::operator()(const FTimeEvent& Event) const
{
	std::size_t h1 = std::hash<float>()(Event.m_fElapsedTimeToTrigger);
	std::size_t h2 = std::hash<float>()(Event.m_nUUID);

	return h1 ^ (h2 << 1);
}
