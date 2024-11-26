#pragma once
#include "KmEngine/Level.h"

class ULobbyLevel : public ULevel
{
	typedef ULevel Super;

public:
	enum class ELevelState
	{
		Login,
		Lobby,
		Lobby_Tutorial
	};

public:
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
	void BeginPlay() override;

	void OnClicked();

	void ChangeLevelState(ELevelState LevelState);


private:
	ELevelState m_LevelState;
};

