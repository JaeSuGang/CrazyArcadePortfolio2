#include "stdafx.h"
#include "Tilemap.h"

void FTilemap::Serialize(FArchive& Ar)
{
	for (int i = 0; i < 15 * 13; i++)
	{
		Ar << m_GroundTiles[i];
	}
	
	for (int i = 0; i < 15 * 13; i++)
	{
		Ar << m_WallTiles[i];
	}
}

void FTilemap::Save(string strFilePath)
{
	FArchive* File = new FArchive{};
	*File << *this;
	File->Save(strFilePath);
	delete File;
}

void FTilemap::Load(string strFilePath)
{
	FArchive* File = new FArchive{};
	File->Load(strFilePath);
	*File >> *this;
	delete File;
}

void FTilemap::Deserialize(FArchive& Ar)
{
	for (int i = 0; i < 15 * 13; i++)
	{
		Ar >> m_GroundTiles[i];
	}

	for (int i = 0; i < 15 * 13; i++)
	{
		Ar >> m_WallTiles[i];
	}
}

