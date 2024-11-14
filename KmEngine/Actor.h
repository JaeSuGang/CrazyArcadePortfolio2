#pragma once
#include "stdafx.h"
#include "Object.h"
#include "ActorComponent.h"

class UActorComponent;

class AActor : public UObject
{
	friend class ULevel;
	friend class UEngine;
public:
	// 직접 호출 X. 물리 연산에서만 호출. 
	// AActor에게 이동 명령을 주고 싶다면 PhysicsComponent에서 호출
	void SetPosition(FVector2D NewPosition);
	void AddPosition(FVector2D PositionToAdd);
	FVector2D GetPosition() const;
	ULevel* GetLevel() const;
	UGameInstance* GetGameInstance() const;

public:
	// 기본 Component 추가 코드
	virtual void BeginPlay();
	virtual void Tick(float fDeltaTime);
	virtual void LateTick(float fDeltaTime);

public:
	void Destroy();

	template <typename T>
	T* GetComponentByClass()
	{
		static_assert(std::is_base_of<UActorComponent, T>::value);

		string ClassName = typeid(T).name();

		auto iter = m_OwnedComponents.find(ClassName);

		if (iter == m_OwnedComponents.end())
		{
			return nullptr;
		}

		T* Component = dynamic_cast<T*>((*iter).second);

		return Component;
	}

	template <typename T>
	T* AddComponent()
	{
		static_assert(std::is_base_of<UActorComponent, T>::value);

		if (T* ExistedComponent = GetComponentByClass<T>())
		{
			return ExistedComponent;
		}

		T* Component = new T{};
		Component->m_Owner = this;
		Component->BeginPlay();

		string ClassName = typeid(T).name();
		pair<string, UActorComponent*> PairToInsert = { ClassName, Component };

		m_OwnedComponents.insert(PairToInsert);

		return Component;
	}

	template <typename T>
	T* CreateDefaultSubobject()
	{
		static_assert(std::is_base_of<UActorComponent, T>::value);

		if (T* ExistedComponent = GetComponentByClass<T>())
		{
			return ExistedComponent;
		}

		T* Component = new T{};
		Component->m_Owner = this;

		string ClassName = typeid(T).name();
		pair<string, UActorComponent*> PairToInsert = { ClassName, Component };

		m_OwnedComponents.insert(PairToInsert);

		return Component;
	}

public:
	void Release();
	AActor();
	~AActor();

protected:
	ULevel* m_Level;
	unordered_map<string, UActorComponent*> m_OwnedComponents;
	FVector2D m_Position;
};

