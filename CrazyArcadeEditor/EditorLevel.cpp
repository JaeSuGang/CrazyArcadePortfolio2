#include "stdafx.h"
#include "EditorLevel.h"
#include "CrazyArcadeGame/GameUI.h"

void UEditorLevel::Tick(float fDeltaTime)
{
}

void UEditorLevel::LateTick(float fDeltaTime)
{
}

void UEditorLevel::BeginPlay()
{
	AGameUI* UI1 = InitializeActorForPlay<AGameUI>();
	UI1->SetPosition(FVector2D(600.0f, 400.0f));
}
