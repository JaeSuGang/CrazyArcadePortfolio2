#pragma once

/*
	friend operator<<(param1, param2) 로 
	FArchive에 << 하는 것을 외부에서 오버로딩 해줘야 함
*/

class FArchive;

__interface ISerializable
{
	virtual void Serialize(FArchive* Ar) = 0;
	virtual void Deserialize(FArchive* Ar) = 0;
};

class FArchive
{
public:
	FArchive* operator<<(ISerializable* Serializable);
	void Load(string strRelativePath);
	void Save(string strRelativePath);
};

