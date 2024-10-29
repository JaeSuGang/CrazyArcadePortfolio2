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
	virtual void Tick(float fDeltaTime);
	virtual void BeginPlay();

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

		string ClassName = typeid(T).name();
		pair<string, UActorComponent> PairToInsert = { ClassName, Component };

		m_OwnedComponents.insert(PairToInsert);
	}

protected:
	unordered_map<string, UActorComponent*> m_OwnedComponents;

protected:
	FVector2D m_Position;
};

