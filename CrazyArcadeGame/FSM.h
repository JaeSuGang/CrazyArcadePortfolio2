#pragma once
#include "KmEngine/Object.h"
#include "KmEngine/ActorComponent.h"

/*
* FSM�� ������ ���� Ŭ�������� ��ü�� State�� �����ؾ� ��
*/
class UBaseState abstract
{
public:
	virtual void OnStateEnter() = 0;
	virtual void OnStateUpdate(float fDeltaTime) = 0;
	virtual void OnStateExit() = 0;

	void SetOwner(AActor* Actor);

protected:
	AActor* m_Owner;
};

/*
* ���� Ŭ������ UFSM ��ü�� Composition �ϵ��� ��.
*/
class UFSMComponent : public UActorComponent
{
public:
	// �����ڿ� �������̵�
	UFSMComponent();
	~UFSMComponent();
	void BeginPlay() override;
	void TickComponent(float fDeltaTime) override;

	// �Լ�
	
	template <typename T>
	void ChangeState()
	{
		T* NewState = GetState<T>();

		if (!NewState)
			SHOW_ERROR("�������� �ʴ� State�� �����");

		if (m_CurrentState)
			m_CurrentState->OnStateExit();

		m_CurrentState = NewState;
		m_CurrentState->OnStateEnter();
	}

	template <typename T>
	T* GetState()
	{
		auto Iter = m_States.find(typeid(T).name());

		if (Iter == m_States.end())
			return nullptr;

		T* FoundState = static_cast<T*>(Iter->second);
		return FoundState;
	}

	template <typename T>
	T* CreateState()
	{
		static_assert(std::is_base_of<UBaseState, T>::value);

		T* NewState = new T{};
		NewState->SetOwner(m_Owner);
		std::pair<string, UBaseState*> PairToInsert{ typeid(T).name(), NewState };
		m_States.insert(PairToInsert);

		return NewState;
	}

private:
	UBaseState* m_CurrentState;
	unordered_map<string, UBaseState*> m_States;

};

