#pragma once

/*
	friend operator<<(param1, param2) �� 
	FArchive�� << �ϴ� ���� �ܺο��� �����ε� ���ְų�,

	FArchive�� << ���� �� �ִ� �̹� �˷��� �ڷ����� �ֵ���
	Serialize(FArchive* Ar)�� �������̵� ���־�� ��.
*/

/*
	�𸮾��� ���, UObject�� Serialize(FArchive& Ar)��
	�̹� ���� �Լ��� ����Ǿ� �ִ�.
	���� Ŭ�������� Super::Serialize(Ar) ���� ���� ȣ������ ��
	Ar << MyData1;
	Ar << MyData2; ���ش�
*/

class FArchive;

__interface ISerializable
{
	virtual void Serialize(FArchive& Ar) = 0;
};

class FArchive
{
public:
	FArchive& operator<<(ISerializable* Serializable);
	FArchive& operator<<(string strData);
	FArchive& operator<<(unsigned char InputData);
	FArchive& operator<<(int nData);
	void SafeWriteMemory(void* pInput, int nSize);
	void ReserveMemory(int nSize);
	void Load(string strRelativePath);
	void Save(string strRelativePath);

public:
	FArchive();

public:
	vector<unsigned char> m_Data;
};

