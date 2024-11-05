#pragma once
#include "KmEngine/Level.h"

class UEditorLevel : public ULevel
{
	typedef ULevel Super;

public:
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
	void BeginPlay() override;
};

