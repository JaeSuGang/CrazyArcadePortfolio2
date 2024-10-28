#pragma once
#include "Object.h"

using std::unordered_map;

class UEngineSubsystem;

class UEngine : public UObject
{
public:
	void Tick();

public:
	template <typename T>
	T* GetEngineSubsystem()
	{
		// typeid를 unordered_map의 key값으로 탐색
		// 컨테이너의 모든 요소들을 순환하면서 dynamic_cast하여 찾는것보다 매우 효율적
		string ClassName = typeid(T).name();
		auto iter = m_Subsystems.find(ClassName);

		// #ifdef _DEBUG 를 통해 디버그 모드에서만 확인할 수 있는 에러 정보
		// 릴리즈 모드에서는 최적화되어, 없는 코드가 됨
		if (iter == m_Subsystems.end())
		{
			SHOW_ERROR(("존재하지 않는 엔진 서브시스템입니다 : " + ClassName).c_str());
		}

		// 캐스팅 성공을 보장할 수 있기 때문에,
		// 성능 오버헤드를 줄이고자 dynamic_cast 대신 static_cast 사용
		T* Casted = static_cast<T*>((*iter).second);

		return Casted;
	}

	void CreateWindowManager();

public:
	~UEngine();
private:
	void Release();

private:
	unordered_map<string, UEngineSubsystem*> m_Subsystems;

};

extern UEngine* GEngine;

