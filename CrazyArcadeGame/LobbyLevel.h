#pragma once
#include "KmEngine/Level.h"

class ULobbyLevel : public ULevel
{
	typedef ULevel Super;

public:
	struct FLevelEvent
	{
		float m_fElapsedTime;
		std::function<void()> m_Function;
	};

	enum class ELevelState
	{
		Login,
		Lobby
	};

public:
	void ChangeLevelState(ELevelState LevelState);
	void AddLevelEvent(std::function<void()> Function, float fElapseTimeToTrigger);


public:
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
	void BeginPlay() override;

public:
	unordered_multiset<FLevelEvent> m_Events;
	ELevelState m_LevelState;
	float m_fElapsedTime;
		
};

