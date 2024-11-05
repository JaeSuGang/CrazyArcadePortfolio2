#include "stdafx.h"
#include "KmEngine/Engine.h"
#include "EditorManager.h"
#include "EditorGameInstance.h"
#include "EditorLevel.h"

void UEditorGameInstance::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);
}

void UEditorGameInstance::LateTick(float fDeltaTime)
{
	Super::LateTick(fDeltaTime);
}

void UEditorGameInstance::BeginPlay()
{
	Super::BeginPlay();

	UEditorManager* EditorManager = CreateGameInstanceSubsystem<UEditorManager>();

	OpenLevel<UEditorLevel>();
}
