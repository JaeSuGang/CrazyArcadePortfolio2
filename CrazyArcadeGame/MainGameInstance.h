#pragma once
#include "KmEngine/GameInstance.h"

class UMainGameInstance : public UGameInstance
{
	typedef UGameInstance Super;

public:
	enum class ECharacterType
	{
		Bazzi,
		Dao,
		Cappi,
		Marid
	};

public:
	// Contructors and Overrides
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
	void BeginPlay() override;


public:
	ACCESSORS_ALL(ECharacterType, LocalPlayerCharacterType);

private:
	ECharacterType LocalPlayerCharacterType;
};

