#include "stdafx.h"
#include "Archive.h"

void FArchive::ReserveMemory(int nSize)
{
	if (m_Data.size() + nSize > m_Data.capacity())
	{
		m_Data.reserve(m_Data.capacity() * 2);
	}
	m_Data.resize(m_Data.size() + nSize);
}

FArchive& FArchive::operator<<(ISerializable* Serializable)
{
	Serializable->Serialize(*this);

	return *this;
}

FArchive& FArchive::operator<<(string strData)
{
	int nStringSize = (int)strData.size();
	SafeWriteMemory(&nStringSize, sizeof(nStringSize));

	for (char c : strData)
	{
		SafeWriteMemory(&c, sizeof(c));
	}

	return *this;
}

FArchive& FArchive::operator<<(unsigned char InputData)
{
	SafeWriteMemory(&InputData, sizeof(InputData));
	return *this;
}

FArchive& FArchive::operator<<(int InputData)
{
	SafeWriteMemory(&InputData, sizeof(InputData));
	return *this;
}

void FArchive::SafeWriteMemory(void* pInput, int nSize)
{
	void* MemoryAddressToStartWriting = &m_Data[m_Data.size()-1] + 1;

	ReserveMemory(nSize);

	memcpy_s(MemoryAddressToStartWriting, nSize, pInput, nSize);
}

void FArchive::Load(string strRelativePath)
{
}

void FArchive::Save(string strRelativePath)
{
	FILE* pFile;
	errno_t err = fopen_s(&pFile, strRelativePath.data(), "wb");

	if (pFile)
	{
		fwrite(&m_Data[0], 1, m_Data.size(), pFile);
	}
	else
	{
		SHOW_ERROR("fopen_s가 실패했습니다. errno_t를 확인하세요");
	}
}

FArchive::FArchive()
	:
	m_Data{}
{
	m_Data.reserve(1024);
	m_Data.push_back(0);
}
