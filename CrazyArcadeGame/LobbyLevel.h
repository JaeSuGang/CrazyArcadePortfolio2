#pragma once
#include "KmEngine/Level.h"

class ULobbyLevel : public ULevel
{
	typedef ULevel Super;

public:
	struct FLevelEvent
	{
		bool operator==(const FLevelEvent& Other) const;

		float m_fElapsedTimeToTrigger;
		float m_nUUID;
		std::function<void()> m_Function;
	};

	struct FLevelEventHash
	{
		std::size_t operator()(const FLevelEvent& Event) const;
	};

	enum class ELevelState
	{
		Login,
		Lobby,
		Lobby_Tutorial
	};



public:
	void ChangeLevelState(ELevelState LevelState);
	void AddLevelEvent(std::function<void()> Function, float fTime);

public:
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
	void BeginPlay() override;

public:
	unordered_multiset<FLevelEvent, FLevelEventHash> m_Events;
	ELevelState m_LevelState;
	float m_fElapseTime;
		
};

