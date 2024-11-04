#pragma once

/*
	friend operator<<(param1, param2) �� 
	FArchive�� << �ϴ� ���� �ܺο��� �����ε� ����� ��
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

