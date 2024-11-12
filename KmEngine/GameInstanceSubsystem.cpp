#include "stdafx.h"
#include "GameInstanceSubsystem.h"
#include "Engine.h"

ULevel* UGameInstanceSubsystem::GetActiveLevel() const
{
    return GEngine->GetGameInstance()->GetActiveLevel();
}

void UGameInstanceSubsystem::Tick(float fDeltaTime)
{

}
