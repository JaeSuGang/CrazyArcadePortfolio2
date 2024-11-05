#pragma once

/*
	friend operator<<(param1, param2) 로 
	FArchive에 << 하는 것을 외부에서 오버로딩 해주거나,

	FArchive에 << 넣을 수 있는 이미 알려진 자료형을 넣도록
	Serialize(FArchive* Ar)를 오버라이드 해주어야 함.
*/

/*
	언리얼의 경우, UObject는 Serialize(FArchive& Ar)이
	이미 가상 함수로 선언되어 있다.
	하위 클래스들은 Super::Serialize(Ar) 까지 같이 호출해준 뒤
	Ar << MyData1;
	Ar << MyData2; 해준다
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

