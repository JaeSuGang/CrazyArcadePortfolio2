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
		// typeid�� unordered_map�� key������ Ž��
		// �����̳��� ��� ��ҵ��� ��ȯ�ϸ鼭 dynamic_cast�Ͽ� ã�°ͺ��� �ſ� ȿ����
		string ClassName = typeid(T).name();
		auto iter = m_Subsystems.find(ClassName);

		// #ifdef _DEBUG �� ���� ����� ��忡���� Ȯ���� �� �ִ� ���� ����
		// ������ ��忡���� ����ȭ�Ǿ�, ���� �ڵ尡 ��
		if (iter == m_Subsystems.end())
		{
			SHOW_ERROR(("�������� �ʴ� ���� ����ý����Դϴ� : " + ClassName).c_str());
		}

		// ĳ���� ������ ������ �� �ֱ� ������,
		// ���� ������带 ���̰��� dynamic_cast ��� static_cast ���
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

