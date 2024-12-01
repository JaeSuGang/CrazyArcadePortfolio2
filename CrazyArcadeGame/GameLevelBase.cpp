#include "stdafx.h"
#include "Windows.h"
#include "GameLevelBase.h"
#include "Character.h"
#include "KmEngine/Engine.h"
#include "KmEngine/GameInstance.h"
#include "KmEngine/PlayerController.h"
#include "KmEngine/SoundManager.h"
#include "KmEngine/RandomManager.h"
#include "GameUI.h"
#include "SpawnManager.h"
#include "BombManager.h"
#include "MovementManager.h"
#include "CharacterAIController.h"
#include "Tilemap.h"
#include "TimeEventManager.h"
#include "MainGameInstance.h"
#include "RoomLevel.h"


void UGameLevelBase::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	this->ElapsedTime += fDeltaTime;

	CheckGameFinished();
}

void UGameLevelBase::LateTick(float fDeltaTime)
{
	Super::LateTick(fDeltaTime);
}

void UGameLevelBase::BeginPlay()
{
	Super::BeginPlay();

	UTimeEventManager* TimeEventManager = GetGameInstance()->GetSubsystem<UTimeEventManager>();
	URenderManager* RenderManager = GEngine->GetEngineSubsystem<URenderManager>();
	USpawnManager* SpawnManager = GetGameInstance()->GetSubsystem<USpawnManager>();
	UMovementManager* MovementManager = GetGameInstance()->GetSubsystem<UMovementManager>();
	APlayerController* PlayerController = SpawnManager->SpawnPlayerController();

	// 바닥타일 한번 렌더 허용
	RenderManager->SetbShouldGenerateFloorTiles(true);

	// UI 생성
	AGameUI* InGameUI = SpawnManager->SpawnGameUI("Resources\\UI\\InGameUI.bmp", FVector2D(600.0f, 450.0f));

	// 타일맵 생성
	SpawnManager->GenerateTilemap(m_Tilemap);

	UMainGameInstance* MainGameInstance = static_cast<UMainGameInstance*>(GetGameInstance());
	URandomManager* RandomManager = GEngine->GetEngineSubsystem<URandomManager>();
	RandomManager->ShuffleVector(SpawnLocations);

	
	ACharacter* SpawningCharacter{};
	AController* Controller{};

	for (int i = 0; i < SpawnLocations.size(); i++)
	{
		int nRandomNumber = RandomManager->GenerateRandomNumber((int)UMainGameInstance::ECharacterType::Bazzi, (int)UMainGameInstance::ECharacterType::End);

		UMainGameInstance::ECharacterType RandomCharacterType = (UMainGameInstance::ECharacterType)nRandomNumber;

		if (i == 0)
			RandomCharacterType = MainGameInstance->GetLocalPlayerCharacterType();

		switch (RandomCharacterType)
		{
		case UMainGameInstance::ECharacterType::Bazzi:
		{
			SpawningCharacter = SpawnManager->SpawnBazzi(SpawnLocations[i]);
			SpawningCharacter->SetDebugPen(CreatePen(PS_SOLID, 3, RGB(0, 255, 0)));
			break;
		}
		case UMainGameInstance::ECharacterType::Dao:
		{
			SpawningCharacter = SpawnManager->SpawnDao(SpawnLocations[i]);
			SpawningCharacter->SetDebugPen(CreatePen(PS_SOLID, 3, RGB(255, 127, 0)));
			break;
		}
		case UMainGameInstance::ECharacterType::Cappi:
		{
			SpawningCharacter = SpawnManager->SpawnCappi(SpawnLocations[i]);
			SpawningCharacter->SetDebugPen(CreatePen(PS_SOLID, 3, RGB(15, 180, 252)));
			break;
		}
		case UMainGameInstance::ECharacterType::Marid:
		{
			SpawningCharacter = SpawnManager->SpawnMarid(SpawnLocations[i]);
			SpawningCharacter->SetDebugPen(CreatePen(PS_SOLID, 3, RGB(255, 212, 0)));
			break;
		}
		}

		if (i == 0)
		{
			Controller = SpawnManager->SpawnPlayerController();
		}
		else
		{
			Controller = SpawnManager->SpawnCharacterAIController();
		}

		TimeEventManager->AddTimeEvent(std::bind(&AController::Possess, Controller, SpawningCharacter), 1.0f);
	}

	// 소리 재생
	USoundManager* SoundManager = GEngine->GetEngineSubsystem<USoundManager>();
	SoundManager->StopAllSounds();
	SoundManager->Play("Resources\\Sound\\game_start.wav");
	SoundManager->Play("Resources\\Sound\\gamebgm1.wav");

}

void UGameLevelBase::CheckGameFinished()
{
	if (LocalPlayerCharacter == nullptr || bIsGameFinished)
		return;

	if (Characters.size() == 1 && *Characters.begin() == LocalPlayerCharacter)
	{
		this->bIsGameFinished = true;
		this->OnWin();
	}

	else if (Characters.find(LocalPlayerCharacter) == Characters.end())
	{
		this->bIsGameFinished = true;
		this->OnLose();
	}
}

void UGameLevelBase::OnWin()
{
	UTimeEventManager* TimeEventManager = GetGameInstance()->GetSubsystem<UTimeEventManager>();
	UKeyManager* KeyManager = GEngine->GetEngineSubsystem<UKeyManager>();
	USoundManager* SoundManager = GEngine->GetEngineSubsystem<USoundManager>();

	SoundManager->Play("Resources\\Sound\\Win.wav");
	KeyManager->ClearBindKey();

	TimeEventManager->AddTimeEvent(std::bind(&UGameInstance::OpenLevel<URoomLevel>, GetGameInstance()), 5.0f);

	USpawnManager* SpawnManager = GetGameInstance()->GetSubsystem<USpawnManager>();
	SpawnManager->SpawnTopMostGameUI("Resources\\UI\\win.bmp", FVector2D(600.0f, 410.0f));
}

void UGameLevelBase::OnLose()
{
	UTimeEventManager* TimeEventManager = GetGameInstance()->GetSubsystem<UTimeEventManager>();
	UKeyManager* KeyManager = GEngine->GetEngineSubsystem<UKeyManager>();
	USoundManager* SoundManager = GEngine->GetEngineSubsystem<USoundManager>();

	SoundManager->Play("Resources\\Sound\\Lose.wav");

	KeyManager->ClearBindKey();

	TimeEventManager->AddTimeEvent(std::bind(&UGameInstance::OpenLevel<URoomLevel>, GetGameInstance()), 5.0f);
	USpawnManager* SpawnManager = GetGameInstance()->GetSubsystem<USpawnManager>();
	SpawnManager->SpawnTopMostGameUI("Resources\\UI\\lose.bmp", FVector2D(600.0f, 410.0f));
}

void UGameLevelBase::AddToCharacters(ACharacter* Character)
{
	Characters.insert(Character);
}

void UGameLevelBase::RemoveFromCharacters(ACharacter* Character)
{
	Characters.erase(Character);

}

void UGameLevelBase::Release()
{
	UKeyManager* KeyManager = GEngine->GetEngineSubsystem<UKeyManager>();
	KeyManager->ClearBindKey();
	UMovementManager* MovementManager = GetGameInstance()->GetSubsystem<UMovementManager>();
	MovementManager->Reset();
	SAFE_DELETE(m_Tilemap);
}

UGameLevelBase::~UGameLevelBase()
{
	this->Release();
}
