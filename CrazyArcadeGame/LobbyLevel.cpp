#include "stdafx.h"
#include "LobbyLevel.h"
#include "GameUI.h"
#include "KmEngine/RenderComponent.h"
#include "KmEngine/SoundManager.h"
#include "TimeEventManager.h"
#include "RoomLevel.h"

void ULobbyLevel::Tick(float fDeltaTime)
{
}

void ULobbyLevel::LateTick(float fDeltaTime)
{
	Super::LateTick(fDeltaTime);
}

void ULobbyLevel::BeginPlay()
{

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
			GetGameInstance()->OpenLevel<URoomLevel>();
		}
		break;
	}

	default:
		break;
	}
}

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

		UTimeEventManager* TimeEventManager = GetGameInstance()->GetSubsystem<UTimeEventManager>();
		TimeEventManager->AddTimeEvent(std::bind(&ULobbyLevel::ChangeLevelState, this, ULobbyLevel::ELevelState::Lobby_Tutorial), 0.5f);
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
