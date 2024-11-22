#pragma once
#include "KmEngine/Object.h"
#include "KmEngine/ActorComponent.h"

class UFSMComponent;

/*
* FSM을 쓰려는 게임 클래스에서 구체적 State를 구현해야 함
*/
class UBaseState abstract
{
public:
	virtual void OnStateEnter() = 0;
	virtual void OnStateUpdate(float fDeltaTime) = 0;
	virtual void OnStateExit() = 0;

	void SetOwner(AActor* OwnerToSet);
	void SetFSM(UFSMComponent* FSMToSet);

protected:
	AActor* Owner;
	UFSMComponent* FSM;
};

/*
* 게임 클래스가 UFSM 객체를 Composition 하도록 함.
*/
class UFSMComponent : public UActorComponent
{
public:
	// 생성자와 오버라이드
	UFSMComponent();
	~UFSMComponent();
	void BeginPlay() override;
	void TickComponent(float fDeltaTime) override;

	// 함수
	UBaseState* GetCurrentState() const;

	template <typename T>
	void ChangeState()
	{
		T* NewState = GetState<T>();

		if (!NewState)
			SHOW_ERROR("존재하지 않는 State를 사용함");

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
		NewState->SetFSM(this);
		std::pair<string, UBaseState*> PairToInsert{ typeid(T).name(), NewState };
		m_States.insert(PairToInsert);

		return NewState;
	}

private:
	UBaseState* m_CurrentState;
	unordered_map<string, UBaseState*> m_States;

};

