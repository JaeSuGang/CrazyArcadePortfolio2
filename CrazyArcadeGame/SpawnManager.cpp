#include "stdafx.h"
#include "Character.h"
#include "KmEngine/Level.h"
#include "KmEngine/PlayerController.h"
#include "KmEngine/RenderComponent.h"
#include "GameUI.h"
#include "MovableComponent.h"
#include "SpawnManager.h"

AGameUI* USpawnManager::SpawnGameUI(string strImagePath, FVector2D PositionVector)
{
	AGameUI* GameUI = GetActiveLevel()->InitializeActorForPlay<AGameUI>();
	URenderComponent* RenderComponent = GameUI->CreateDefaultSubobject<URenderComponent>();
	RenderComponent->SetStaticImage(strImagePath);
	GameUI->SetPosition(PositionVector);
	return GameUI;
}

ACharacter* USpawnManager::SpawnCharacter(string strCharacterName, FVector2D PositionVector)
{
	ACharacter* SpawnedCharacter = GetActiveLevel()->InitializeActorForPlay<ACharacter>();
	SpawnedCharacter->SetCharacterName(strCharacterName);
	URenderComponent* RenderComponent = SpawnedCharacter->CreateDefaultSubobject<URenderComponent>();
	RenderComponent->SetOffset(FVector2D(0.0f, -12.0f));
	RenderComponent->SetStaticImage("Resources\\" + strCharacterName + "\\" + "DownIdle.bmp");
	RenderComponent->CreateAnimation(strCharacterName + "DownWalk", "Resources\\" + strCharacterName + "\\DownWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(strCharacterName + "LeftWalk", "Resources\\" + strCharacterName + "\\LeftWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(strCharacterName + "RightWalk", "Resources\\" + strCharacterName + "\\RightWalk", 4, 0.1f, true);
	RenderComponent->CreateAnimation(strCharacterName + "UpWalk", "Resources\\" + strCharacterName + "\\UpWalk", 4, 0.1f, true);
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

void USpawnManager::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);


}
