#include "stdafx.h"
#include "TileInfoManager.h"

void UTileInfoManager::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);


}

void FTilemapInfo::Serialize(FArchive& Ar)
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

void FTilemapInfo::Save(string strFilePath)
{
	FArchive* File = new FArchive{};
	*File << *this;
	File->Save(strFilePath);
	delete File;
}

void FTilemapInfo::Load(string strFilePath)
{
	FArchive* File = new FArchive{};
	File->Load(strFilePath);
	*File >> *this;
	delete File;
}

void FTilemapInfo::Deserialize(FArchive& Ar)
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

