#pragma once
#include "KmEngine/GameInstanceSubsystem.h"

class AGameUI;

class UEditorManager : public UGameInstanceSubsystem
{
	typedef UGameInstanceSubsystem Super;

public:
	AGameUI* SpawnEditorUI(string strImagePath, FVector2D PositionVector);

public:
	void Tick(float fDeltaTime) override;
};

