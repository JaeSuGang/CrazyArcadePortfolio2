#pragma once
#include "stdafx.h"
#include "Object.h"
#include "ActorComponent.h"

class UActorComponent;

class AActor : public UObject
{
	friend class ULevel;
	friend class UEngine;

protected:
	// 기본 Component 추가 코드
	virtual void Initialize() = 0;
	virtual void Tick(float fDeltaTime) = 0;
	virtual void BeginPlay() = 0;

protected:
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

		T* Component = static_cast<T*>((*iter).second);

		return Component;
	}

	template <typename T>
	void AddComponent()
	{
		static_assert(std::is_base_of<UActorComponent, T>::value);

		if (GetComponentByClass<T>())
		{
			return nullptr;
		}

		UActorComponent* Component = new T{};
		Component->m_Owner = this;
		Component->Initialize();
		Component->BeginPlay();

		string ClassName = typeid(T).name();
		pair<string, UActorComponent> PairToInsert = { ClassName, Component };

		m_OwnedComponents.insert(PairToInsert);
	}

	template <typename T>
	void EmplaceComponent()
	{
		static_assert(std::is_base_of<UActorComponent, T>::value);

		if (GetComponentByClass<T>())
		{
			return nullptr;
		}

		UActorComponent* Component = new T{};
		Component->m_Owner = this;
		Component->Initialize();

		string ClassName = typeid(T).name();
		pair<string, UActorComponent> PairToInsert = { ClassName, Component };

		m_OwnedComponents.insert(PairToInsert);
	}

protected:
	unordered_map<string, UActorComponent*> m_OwnedComponents;

protected:
	FVector2D m_Position;
};

