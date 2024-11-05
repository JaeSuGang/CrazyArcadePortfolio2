#include "stdafx.h"
#include "Character.h"
#include "KmEngine/Level.h"
#include "KmEngine/PlayerController.h"
#include "CharacterAIController.h"
#include "KmEngine/RenderComponent.h"
#include "GameUI.h"
#include "MovableComponent.h"
#include "SpawnManager.h"


AGameUI* USpawnManager::SpawnGameUI(string strImagePath, FVector2D PositionVector)
{
	AGameUI* GameUI = GetActiveLevel()->InitializeActorForPlay<AGameUI>();
	URenderComponent* RenderComponent = GameUI->CreateDefaultSubobject<URenderComponent>();
	RenderComponent->SetStaticImage(strImagePath);
	RenderComponent->SetRenderPriority(0);
	RenderComponent->BeginPlay();
	GameUI->SetPosition(PositionVector);
	return GameUI;
}

ACharacter* USpawnManager::SpawnBazzi(FVector2D PositionVector)
{
	string strCharacterName = "Bazzi";
	ACharacter* SpawnedCharacter = GetActiveLevel()->InitializeActorForPlay<ACharacter>();
	SpawnedCharacter->SetCharacterName(strCharacterName);
	URenderComponent* RenderComponent = SpawnedCharacter->CreateDefaultSubobject<URenderComponent>();
	RenderComponent->SetOffset(FVector2D(0.0f, -12.0f));
	RenderComponent->SetStaticImage("Resources\\" + strCharacterName + "\\" + "DownIdle.bmp");
	RenderComponent->SetRenderPriority(1);
	RenderComponent->CreateAnimation(strCharacterName + "DownWalk", "Resources\\" + strCharacterName + "\\DownWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(strCharacterName + "LeftWalk", "Resources\\" + strCharacterName + "\\LeftWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(strCharacterName + "RightWalk", "Resources\\" + strCharacterName + "\\RightWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(strCharacterName + "UpWalk", "Resources\\" + strCharacterName + "\\UpWalk", 4, 0.1f, true);
	RenderComponent->BeginPlay();
	UMovableComponent* MovableComponent = SpawnedCharacter->CreateDefaultSubobject<UMovableComponent>();
	MovableComponent->RegisterAtMovementManager();
	MovableComponent->SetMaxSpeed(300.0f);
	MovableComponent->SetRadius(30.0f);

	SpawnedCharacter->SetPosition(PositionVector);
	SpawnedCharacter->BeginPlay();
	return SpawnedCharacter;
}

ACharacter* USpawnManager::SpawnDao(FVector2D PositionVector)
{
	string strCharacterName = "Dao";
	ACharacter* SpawnedCharacter = GetActiveLevel()->InitializeActorForPlay<ACharacter>();
	SpawnedCharacter->SetCharacterName(strCharacterName);
	URenderComponent* RenderComponent = SpawnedCharacter->CreateDefaultSubobject<URenderComponent>();
	RenderComponent->SetOffset(FVector2D(0.0f, -13.0f));
	RenderComponent->SetStaticImage("Resources\\" + strCharacterName + "\\" + "DownIdle.bmp");
	RenderComponent->SetRenderPriority(1);
	RenderComponent->CreateAnimation(strCharacterName + "DownWalk", "Resources\\" + strCharacterName + "\\DownWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(strCharacterName + "LeftWalk", "Resources\\" + strCharacterName + "\\LeftWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(strCharacterName + "RightWalk", "Resources\\" + strCharacterName + "\\RightWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(strCharacterName + "UpWalk", "Resources\\" + strCharacterName + "\\UpWalk", 4, 0.1f, true);
	RenderComponent->BeginPlay();
	UMovableComponent* MovableComponent = SpawnedCharacter->CreateDefaultSubobject<UMovableComponent>();
	MovableComponent->RegisterAtMovementManager();
	MovableComponent->SetMaxSpeed(300.0f);
	MovableComponent->SetRadius(30.0f);

	SpawnedCharacter->SetPosition(PositionVector);
	SpawnedCharacter->BeginPlay();
	return SpawnedCharacter;
}

ACharacter* USpawnManager::SpawnCappi(FVector2D PositionVector)
{
	string strCharacterName = "Cappi";
	ACharacter* SpawnedCharacter = GetActiveLevel()->InitializeActorForPlay<ACharacter>();
	SpawnedCharacter->SetCharacterName(strCharacterName);
	URenderComponent* RenderComponent = SpawnedCharacter->CreateDefaultSubobject<URenderComponent>();
	RenderComponent->SetOffset(FVector2D(0.0f, -12.0f));
	RenderComponent->SetStaticImage("Resources\\" + strCharacterName + "\\" + "DownIdle.bmp");
	RenderComponent->SetRenderPriority(1);
	RenderComponent->CreateAnimation(strCharacterName + "DownWalk", "Resources\\" + strCharacterName + "\\DownWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(strCharacterName + "LeftWalk", "Resources\\" + strCharacterName + "\\LeftWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(strCharacterName + "RightWalk", "Resources\\" + strCharacterName + "\\RightWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(strCharacterName + "UpWalk", "Resources\\" + strCharacterName + "\\UpWalk", 4, 0.1f, true);
	RenderComponent->BeginPlay();
	UMovableComponent* MovableComponent = SpawnedCharacter->CreateDefaultSubobject<UMovableComponent>();
	MovableComponent->RegisterAtMovementManager();
	MovableComponent->SetMaxSpeed(300.0f);
	MovableComponent->SetRadius(30.0f);

	SpawnedCharacter->SetPosition(PositionVector);
	SpawnedCharacter->BeginPlay();
	return SpawnedCharacter;
}

ACharacter* USpawnManager::SpawnMarid(FVector2D PositionVector)
{
	string strCharacterName = "Marid";
	ACharacter* SpawnedCharacter = GetActiveLevel()->InitializeActorForPlay<ACharacter>();
	SpawnedCharacter->SetCharacterName(strCharacterName);
	URenderComponent* RenderComponent = SpawnedCharacter->CreateDefaultSubobject<URenderComponent>();
	RenderComponent->SetOffset(FVector2D(0.0f, -12.0f));
	RenderComponent->SetStaticImage("Resources\\" + strCharacterName + "\\" + "DownIdle.bmp");
	RenderComponent->SetRenderPriority(1);
	RenderComponent->CreateAnimation(strCharacterName + "DownWalk", "Resources\\" + strCharacterName + "\\DownWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(strCharacterName + "LeftWalk", "Resources\\" + strCharacterName + "\\LeftWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(strCharacterName + "RightWalk", "Resources\\" + strCharacterName + "\\RightWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(strCharacterName + "UpWalk", "Resources\\" + strCharacterName + "\\UpWalk", 4, 0.1f, true);
	RenderComponent->BeginPlay();
	UMovableComponent* MovableComponent = SpawnedCharacter->CreateDefaultSubobject<UMovableComponent>();
	MovableComponent->RegisterAtMovementManager();
	MovableComponent->SetMaxSpeed(300.0f);
	MovableComponent->SetRadius(30.0f);

	SpawnedCharacter->SetPosition(PositionVector);
	SpawnedCharacter->BeginPlay();
	return SpawnedCharacter;
}

APlayerController* USpawnManager::SpawnPlayerController()
{
	APlayerController* PlayerController = GetActiveLevel()->InitializeActorForPlay<APlayerController>();
	PlayerController->BeginPlay();
	return PlayerController;
}

AAIController* USpawnManager::SpawnCharacterAIController()
{
	ACharacterAIController* AIController = GetActiveLevel()->InitializeActorForPlay<ACharacterAIController>();
	AIController->BeginPlay();
	return AIController;
}

void USpawnManager::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);


}
