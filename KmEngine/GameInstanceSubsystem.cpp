#include "stdafx.h"
#include "GameInstanceSubsystem.h"
#include "Engine.h"

ULevel* UGameInstanceSubsystem::GetActiveLevel()
{
    return GEngine->GetGameInstance()->GetActiveLevel();
}
