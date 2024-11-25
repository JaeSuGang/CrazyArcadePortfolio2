#include "stdafx.h"
#include "LobbyLevel.h"
#include "GameUI.h"
#include "KmEngine/Engine.h"
#include "KmEngine/RenderComponent.h"
#include "KmEngine/SoundManager.h"
#include "KmEngine/KeyManager.h"
#include "MainGameInstance.h"
#include "SpawnManager.h"
#include "Character.h"
#include "BP_GameStage_Village_0.h"

void ULobbyLevel::OnStart()
{

	switch (SelectedGameStage)
	{
	case ULobbyLevel::ESelectedGameStage::Village_1:
		GetGameInstance()->OpenLevel<BP_GameStage_Village_0>();
		break;
	default:
		break;
	}

}

void ULobbyLevel::OnChangedCharacterSelect(UMainGameInstance::ECharacterType CharacterType)
{
	USoundManager* SoundManager = GEngine->GetEngineSubsystem<USoundManager>();
	UMainGameInstance* MainGameInstance = static_cast<UMainGameInstance*>(GetGameInstance());
	USpawnManager* SpawnManager = MainGameInstance->GetSubsystem<USpawnManager>();

	if (ShowingCharacterActor)
	{
		ShowingCharacterActor->Destroy();
		ShowingCharacterActor = nullptr;
	}
	if (ShowingCheckActor)
	{
		ShowingCheckActor->Destroy();
		ShowingCheckActor = nullptr;
	}

	SoundManager->Play("Resources\\Sound\\click.wav");

	MainGameInstance->SetLocalPlayerCharacterType(CharacterType);
	ShowingCheckActor = SpawnManager->SpawnGameUI("Resources\\UI\\check.bmp", FVector2D::Zero);
	ShowingCheckActor->GetComponentByClass<URenderComponent>()->SetRenderPriority(3.0f);
	switch (CharacterType)
	{
	case UMainGameInstance::ECharacterType::Bazzi:
		ShowingCheckActor->SetPosition(FVector2D(750.0f, 125.0f));
		ShowingCharacterActor = SpawnManager->SpawnBazzi(FVector2D(88.0f, 238.0f));
		break;
	case UMainGameInstance::ECharacterType::Dao:
		ShowingCheckActor->SetPosition(FVector2D(853.0f, 125.0f));
		ShowingCharacterActor = SpawnManager->SpawnDao(FVector2D(88.0f, 238.0f));
		break;
	case UMainGameInstance::ECharacterType::Cappi:
		ShowingCheckActor->SetPosition(FVector2D(956.0f, 125.0f));
		ShowingCharacterActor = SpawnManager->SpawnCappi(FVector2D(88.0f, 238.0f));
		break;
	case UMainGameInstance::ECharacterType::Marid:
		ShowingCheckActor->SetPosition(FVector2D(1058.0f, 125.0f));
		ShowingCharacterActor = SpawnManager->SpawnMarid(FVector2D(88.0f, 238.0f));
		break;
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

		this->OnChangedCharacterSelect(UMainGameInstance::ECharacterType::Bazzi);

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
	case ELevelState::Room:
	{
		UMainGameInstance* MainGameInstance = static_cast<UMainGameInstance*>(GetGameInstance());
		USpawnManager* SpawnManager = MainGameInstance->GetSubsystem<USpawnManager>();

		// 캐릭터 선택
		if (KeyManager->GetMousePos().X > 735 && KeyManager->GetMousePos().X < 825 &&
			KeyManager->GetMousePos().Y > 125 && KeyManager->GetMousePos().Y < 185)
		{
			this->OnChangedCharacterSelect(UMainGameInstance::ECharacterType::Bazzi);
		}
		else if (KeyManager->GetMousePos().X > 838 && KeyManager->GetMousePos().X < 928 &&
			KeyManager->GetMousePos().Y > 125 && KeyManager->GetMousePos().Y < 185)
		{
			this->OnChangedCharacterSelect(UMainGameInstance::ECharacterType::Dao);
		}
		else if (KeyManager->GetMousePos().X > 941 && KeyManager->GetMousePos().X < 1031 &&
			KeyManager->GetMousePos().Y > 125 && KeyManager->GetMousePos().Y < 185)
		{
			this->OnChangedCharacterSelect(UMainGameInstance::ECharacterType::Cappi);
		}
		else if (KeyManager->GetMousePos().X > 1044 && KeyManager->GetMousePos().X < 1134 &&
			KeyManager->GetMousePos().Y > 125 && KeyManager->GetMousePos().Y < 185)
		{
			this->OnChangedCharacterSelect(UMainGameInstance::ECharacterType::Marid);
		}

		// 시작 버튼
		else if (KeyManager->GetMousePos().X > 773 && KeyManager->GetMousePos().X < 1053 &&
			KeyManager->GetMousePos().Y > 744 && KeyManager->GetMousePos().Y < 819)
		{
			this->OnStart();
		}
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
