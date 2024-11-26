#include "stdafx.h"
#include "RoomLevel.h"
#include "GameUI.h"
#include "KmEngine/Engine.h"
#include "KmEngine/RenderComponent.h"
#include "KmEngine/SoundManager.h"
#include "KmEngine/KeyManager.h"
#include "MainGameInstance.h"
#include "SpawnManager.h"
#include "Character.h"
#include "BP_GameStage_Village_1.h"
#include "BP_GameStage_Village_2.h"
#include "BP_GameStage_Village_3.h"
#include "BP_GameStage_Village_4.h"

void URoomLevel::OnGameStart()
{
	UKeyManager* KeyManager = GEngine->GetEngineSubsystem<UKeyManager>();
	KeyManager->ClearBindKey();

	switch (SelectedGameStage)
	{
	case URoomLevel::ESelectedGameStage::Village_1:
		GetGameInstance()->OpenLevel<BP_GameStage_Village_1>();
		break;
	case URoomLevel::ESelectedGameStage::Village_2:
		GetGameInstance()->OpenLevel<BP_GameStage_Village_2>();
		break;
	case URoomLevel::ESelectedGameStage::Village_3:
		GetGameInstance()->OpenLevel<BP_GameStage_Village_3>();
		break;
	case URoomLevel::ESelectedGameStage::Village_4:
		GetGameInstance()->OpenLevel<BP_GameStage_Village_4>();
		break;
	default:
		break;
	}

}

void URoomLevel::OnChangedCharacterSelect(UMainGameInstance::ECharacterType CharacterType)
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

void URoomLevel::OnChangedStage(ESelectedGameStage StageType)
{
	USpawnManager* SpawnManager = GetGameInstance()->GetSubsystem<USpawnManager>();

	if (SelectedGameStage != StageType)
	{
		if (ShowingStageActor)
			ShowingStageActor->Destroy();
		
		string strStagePath{};

		switch (StageType)
		{
		case URoomLevel::ESelectedGameStage::Village_1:
			strStagePath = "Resources\\UI\\map01.bmp";
			break;
		case URoomLevel::ESelectedGameStage::Village_2:
			strStagePath = "Resources\\UI\\map02.bmp";
			break;
		case URoomLevel::ESelectedGameStage::Village_3:
			strStagePath = "Resources\\UI\\map03.bmp";
			break;
		case URoomLevel::ESelectedGameStage::Village_4:
			strStagePath = "Resources\\UI\\map04.bmp";
			break;
		default:
			break;
		}

		ShowingStageActor = SpawnManager->SpawnGameUI(strStagePath, FVector2D(950.0f, 615.0f), 3.0f);
	}

	SelectedGameStage = StageType;
}

void URoomLevel::OnClickedNextMap()
{
	ESelectedGameStage NextStageEnum = (ESelectedGameStage)((int)SelectedGameStage + 1);
	if (NextStageEnum == ESelectedGameStage::End || NextStageEnum == ESelectedGameStage::None)
		NextStageEnum = ESelectedGameStage::Village_1;

	OnChangedStage(NextStageEnum);
}

void URoomLevel::OnClicked()
{
	UKeyManager* KeyManager = GEngine->GetEngineSubsystem<UKeyManager>();

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

	// 맵 변경 버튼
	else if (KeyManager->GetMousePos().X > 975 && KeyManager->GetMousePos().X < 1160 &&
		KeyManager->GetMousePos().Y > 640 && KeyManager->GetMousePos().Y < 710)
	{
		this->OnClickedNextMap();
	}

	// 시작 버튼
	else if (KeyManager->GetMousePos().X > 773 && KeyManager->GetMousePos().X < 1053 &&
		KeyManager->GetMousePos().Y > 744 && KeyManager->GetMousePos().Y < 819)
	{
		this->OnGameStart();
	}

}

void URoomLevel::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	m_fElapseTime += fDeltaTime;
}

void URoomLevel::LateTick(float fDeltaTime)
{
	Super::LateTick(fDeltaTime);

}

void URoomLevel::BeginPlay()
{
	Super::BeginPlay();

	UKeyManager* KeyManager = GEngine->GetEngineSubsystem<UKeyManager>();
	KeyManager->ClearBindKey();

	KeyManager->BindKey(VK_LBUTTON, UKeyManager::EKeyState::KeyDown, std::bind(&URoomLevel::OnClicked, this));

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

	this->OnChangedStage(ESelectedGameStage::Village_1);
	
}
