#include "stdafx.h"
#include "Archive.h"

FArchive* FArchive::operator<<(ISerializable* Serializable)
{
	Serializable->Serialize(this);

	return this;
}

void FArchive::Load(string strRelativePath)
{
}

void FArchive::Save(string strRelativePath)
{
}
