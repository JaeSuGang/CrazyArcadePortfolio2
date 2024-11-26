#pragma once
#include "KmEngine/Level.h"
#include "MainGameInstance.h"

class ACharacter;
class AGameUI;

class URoomLevel : public ULevel
{
	typedef ULevel Super;

public:

	enum class ESelectedGameStage
	{
		None,
		Village_1,
		Village_2,
		Village_3,
		Village_4,
		End
	};



public:
	void OnStart();
	void OnChangedCharacterSelect(UMainGameInstance::ECharacterType CharacterType);
	void OnChangedStage(ESelectedGameStage StageType);
	void OnClickedNextMap();
	void OnClicked();

public:
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
	void BeginPlay() override;

public:
	AGameUI* ShowingStageActor;
	AGameUI* ShowingCheckActor;
	ACharacter* ShowingCharacterActor;

	float m_fElapseTime;
	ESelectedGameStage SelectedGameStage;
};

