#include "stdafx.h"
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

	OpenLevel<UEditorLevel>();
}
