#include "stdafx.h"
#include "EditorManager.h"
#include "KmEngine/Level.h"
#include "KmEngine/RenderComponent.h"
#include "CrazyArcadeGame/GameUI.h"

AGameUI* UEditorManager::SpawnEditorUI(string strImagePath, FVector2D PositionVector)
{
	AGameUI* GameUI = GetActiveLevel()->InitializeActorForPlay<AGameUI>();
	URenderComponent* RenderComponent = GameUI->CreateDefaultSubobject<URenderComponent>();
	RenderComponent->SetStaticImage(strImagePath);
	RenderComponent->SetRenderPriority(0);
	GameUI->SetPosition(PositionVector);
	return GameUI;
}

void UEditorManager::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);


}
