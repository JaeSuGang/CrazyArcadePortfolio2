#pragma once
#include "FMod/fmod.hpp"
#include "EngineSubsystem.h"

class USoundManager : public UEngineSubsystem
{
public:
	void Play(string strKey);

public:
	void Tick(float fDeltaTime);
	void Initialize();

public:
	FMOD::System* m_FModSystem;
};

