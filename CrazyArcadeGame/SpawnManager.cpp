#include "stdafx.h"
#include "SpawnManager.h"
#include "KmEngine/Level.h"
#include "Character.h"
#include "KmEngine/PlayerController.h"

ACharacter* USpawnManager::SpawnCharacter(string strCharacterName, FVector2D PositionVector)
{
	ACharacter* SpawnedCharacter = GetActiveLevel()->InitializeActorForPlay<ACharacter>();
	SpawnedCharacter->SetCharacterName(strCharacterName);
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
