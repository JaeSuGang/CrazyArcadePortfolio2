#include "stdafx.h"
#include "GameInstanceSubsystem.h"
#include "Engine.h"

UGameInstance* UGameInstanceSubsystem::GetGameInstance() const
{
    return GEngine->GetGameInstance();
}

ULevel* UGameInstanceSubsystem::GetActiveLevel() const
{
    return GEngine->GetGameInstance()->GetActiveLevel();
}

void UGameInstanceSubsystem::Tick(float fDeltaTime)
{

}
