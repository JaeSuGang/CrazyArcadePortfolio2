#pragma once
#include "FMod/fmod.hpp"
#include "EngineSubsystem.h"

class USoundManager : public UEngineSubsystem
{
public:
	void Initialize();

public:
	FMOD::System* m_FModSystem;
};

