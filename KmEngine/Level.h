#pragma once
#include "stdafx.h"
#include "Object.h"

class AActor;
class AGamemode;

class ULevel : public UObject
{
	friend class UEngine;
	friend class UGameInstance;
	friend class UTestGameInstance;
	friend class CLevelDeserializer;

public:
	// BeginPlay()가 없이 Actor를 m_Actors에 넣음
	// 원래는 UWorld::InitializeActorsForPlay
	template <typename T>
	T* InitializeActorForPlay()
	{
		static_assert(std::is_base_of<AActor, T>::value);

		T* NewActor = new T{};
		m_Actors.insert(NewActor);
		return NewActor;
	}

	template <typename T>
	void InitializeGamemodeForPlay()
	{
		static_assert(std::is_base_of<AGamemode, T>::value);

		AGamemode* NewGamemode = new T{};

		SAFE_DELETE(m_Gamemode);
		m_Gamemode = NewGamemode;
	}


public:
	virtual void Tick(float fDeltaTime) = 0;
	virtual void LateTick(float fDeltaTime) = 0;
	virtual void BeginPlay() = 0;
	virtual void Initialize() = 0;

public:
	void Release();
	ULevel();
	~ULevel();

// 차후수정
public:
	AGamemode* m_Gamemode;
	unordered_set<AActor*> m_Actors;
};

