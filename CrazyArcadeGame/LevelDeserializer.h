#pragma once
#include "KmBase/Vector.h"

class ULevel;

enum class EActorType
{
	None = 0,
	Player = 1
};

enum class EGamemodeType
{
	None = 0,
	Test = 1
};

struct FActorData
{
	EActorType ActorType;
	FVector2D ActorPosition;
};

struct FLevelData
{
	int ActorCount;
	FActorData ActorDatas[1000];
	EGamemodeType GamemodeType;
};

class CLevelDeserializer
{
public:
	// ���� ���� ��θ� �޴� Deserialize �Լ� �����ε� �ϱ�
	static ULevel* Deserialize(FLevelData* pLevelData);

	static void EmplaceActor(ULevel* Level, EActorType ActorType);

	static void EmplaceGamemode(ULevel* Level, EGamemodeType GamemodeType);
};

