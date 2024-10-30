#pragma once
#include "stdafx.h"
#include "Object.h"

class AActor;
class AGamemode;

class ULevel final : public UObject
{
	friend class UEngine;
	friend class UGameInstance;
	friend class UTestGameInstance;
	friend class CLevelDeserializer;

public:
	// BeginPlay()�� ���� Actor�� m_Actors�� ����
	template <typename T>
	void EmplaceActor()
	{
		static_assert(std::is_base_of<AActor, T>::value);

		AActor* NewActor = new T{};
		NewActor->Initialize();
		m_Actors.insert(NewActor);
	}

	template <typename T>
	void SpawnActor()
	{
		static_assert(std::is_base_of<AActor, T>::value);

		AActor* NewActor = new T{};
		NewActor->Initialize();
		NewActor->BeginPlay();

		m_Actors.insert(NewActor);
	}

	template <typename T>
	void EmplaceGamemode()
	{
		static_assert(std::is_base_of<AGamemode, T>::value);

		AGamemode* NewGamemode = new T{};
		NewGamemode->Initialize();

		SAFE_DELETE(m_Gamemode);
		m_Gamemode = NewGamemode;
	}


public:
	void Release();
	ULevel();
	~ULevel();

private:
	void Tick(float fDeltaTime);
	void BeginPlay();

// ���ļ���
public:
	AGamemode* m_Gamemode;
	unordered_set<AActor*> m_Actors;
};

