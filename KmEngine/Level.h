#pragma once
#include "stdafx.h"
#include "Object.h"

class AActor;
class APlayerController;
class UGameInstance;
class UGameInstanceSubsystem;

class ULevel : public UObject
{
	friend class UGameInstance;

public:
	APlayerController* GetPlayerController() const;
	UGameInstance* GetGameInstance() const;

public:
	template <typename T>
	T* InitializeActorForPlay()
	{
		static_assert(std::is_base_of<AActor, T>::value);

		T* NewActor = new T{};
		NewActor->m_Level = this;
		m_Actors.insert(NewActor);
		return NewActor;
	}
	void InitiateDestroy();

public:
	virtual void Tick(float fDeltaTime) = 0;
	virtual void LateTick(float fDeltaTime) = 0;
	virtual void BeginPlay() = 0;

public:
	void Release();
	ULevel();
	~ULevel();

// 차후수정
public:
	UGameInstance* m_GameInstance;
	unordered_set<AActor*> m_Actors;
	vector<AActor*> m_ActorsToDestroy;
	APlayerController* m_PlayerController;
};

