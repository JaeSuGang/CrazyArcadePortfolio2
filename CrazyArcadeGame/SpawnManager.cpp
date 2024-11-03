#include "stdafx.h"
#include "SpawnManager.h"
#include "KmEngine/Level.h"
#include "Character.h"
#include "KmEngine/PlayerController.h"

void USpawnManager::SpawnPlayer(string strCharacterName, FVector2D PositionVector)
{
	ACharacter* SpawnedCharacter = GetActiveLevel()->InitializeActorForPlay<ACharacter>();
	SpawnedCharacter->SetCharacterName(strCharacterName);
	SpawnedCharacter->SetPosition(PositionVector);
	SpawnedCharacter->BeginPlay();
}

void USpawnManager::SpawnPlayerController()
{
	APlayerController* PlayerController = GetActiveLevel()->InitializeActorForPlay<APlayerController>();
}
