#include "stdafx.h"
#include "LevelDeserializer.h"
#include "KmEngine/Level.h"
#include "KmEngine/TestPlayer.h"
#include "KmEngine/TestGamemode.h"


ULevel* CLevelDeserializer::Deserialize(FLevelData* pLevelData)
{
	ULevel* NewLevel = new ULevel{};

	EmplaceGamemode(NewLevel, pLevelData->GamemodeType);

	int ActorCount = pLevelData->ActorCount;
	for (int i = 0; i < ActorCount; i++)
	{
		EmplaceActor(NewLevel, pLevelData->ActorDatas[i].ActorType);
	}

	return NewLevel;
}

// 추후 일일히 수정. 테스트용으로 막 만듬.
void CLevelDeserializer::EmplaceActor(ULevel* Level, EActorType ActorType)
{
	switch (ActorType)
	{
	case EActorType::Player:
		Level->InitializeActorForPlay<ATestPlayer>();
		break;

	default:
		break;
	}
}

void CLevelDeserializer::EmplaceGamemode(ULevel* Level, EGamemodeType GamemodeType)
{
	switch (GamemodeType)
	{
	case EGamemodeType::Test:
		Level->InitializeGamemodeForPlay<ATestGamemode>();
		break;

	default:
		break;
	}
}
