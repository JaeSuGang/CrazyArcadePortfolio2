#pragma once
#include "KmEngine/Level.h"
#include "MainGameInstance.h"

class ACharacter;
class AGameUI;

class ULobbyLevel : public ULevel
{
	typedef ULevel Super;

public:
	struct FTimeEvent
	{
		bool operator==(const FTimeEvent& Other) const;

		float m_fElapsedTimeToTrigger;
		float m_nUUID;
		std::function<void()> m_Function;
	};

	struct FTimeEventHash
	{
		std::size_t operator()(const FTimeEvent& Event) const;
	};

	enum class ELevelState
	{
		Login,
		Lobby,
		Lobby_Tutorial,
		Room
	};

	enum class ESelectedGameStage
	{
		Village_1
	};



public:
	void OnStart();
	void OnChangedCharacterSelect(UMainGameInstance::ECharacterType CharacterType);
	void ChangeLevelState(ELevelState LevelState);
	void AddLevelTimeEvent(std::function<void()> Function, float fTime);
	void OnClicked();

public:
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
	void BeginPlay() override;

public:
	unordered_multiset<FTimeEvent, FTimeEventHash> m_TimeEvents;
	AGameUI* ShowingCheckActor;
	ACharacter* ShowingCharacterActor;

	float m_fElapseTime;
	ELevelState m_LevelState;
	ESelectedGameStage SelectedGameStage;
};

