#include "stdafx.h"
#include "Archive.h"

void FArchive::ReserveMemory(int nSize)
{
	while (m_Data.size() + nSize > m_Data.capacity())
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

	char null = 0;
	SafeWriteMemory(&null, 1);

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
	void* MemoryAddressToStartWriting = m_Data.data() + m_Data.size();

	ReserveMemory(nSize);

	memcpy_s(MemoryAddressToStartWriting, nSize, pInput, nSize);
}

void FArchive::Load(string strRelativePath)
{
	FILE* pFile;
	errno_t err = fopen_s(&pFile, strRelativePath.data(), "rb");

	if (pFile)
	{
		fseek(pFile, 0, SEEK_END);
		long nFileSize = ftell(pFile);
		rewind(pFile);

		ReserveMemory(nFileSize);

		fread_s(m_Data.data(), nFileSize, 1, nFileSize, pFile);
	}
	else
	{
		SHOW_ERROR("fopen_s가 실패했습니다. errno_t를 확인하세요");
	}

	fclose(pFile);
}

void FArchive::Save(string strRelativePath)
{
	FILE* pFile;
	errno_t err = fopen_s(&pFile, strRelativePath.data(), "wb");

	if (pFile)
	{
		fwrite(m_Data.data(), 1, m_Data.size(), pFile);
	}
	else
	{
		SHOW_ERROR("fopen_s가 실패했습니다. errno_t를 확인하세요");
	}

	fclose(pFile);
}

FArchive::FArchive()
	:
	m_Data{}
{
	m_Data.reserve(1024);
}
