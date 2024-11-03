#pragma once
#include "stdafx.h"
#include "Object.h"

class AActor;
class AGamemode;
class APlayerController;
class UGameInstance;
class UGameInstanceSubsystem;

class ULevel : public UObject
{
	friend class UGameInstance;

public:
	APlayerController* GetPlayerController() const;
	UGameInstance* GetGameInstance() const;

	//template <typename T>
	//T* GetGameInstanceSubsystem()
	//{
	//	return GetGameInstance()->GetGameInstanceSubsystem<T>();
	//}

public:
	// BeginPlay()�� ���� Actor�� m_Actors�� ����
	// ������ UWorld::InitializeActorsForPlay
	template <typename T>
	T* InitializeActorForPlay()
	{
		static_assert(std::is_base_of<AActor, T>::value);

		T* NewActor = new T{};
		m_Actors.insert(NewActor);
		return NewActor;
	}

public:
	virtual void Tick(float fDeltaTime) = 0;
	virtual void LateTick(float fDeltaTime) = 0;
	virtual void BeginPlay() = 0;

public:
	void Release();
	ULevel();
	~ULevel();

// ���ļ���
public:
	UGameInstance* m_GameInstance;
	unordered_set<AActor*> m_Actors;
	APlayerController* m_PlayerController;
};

