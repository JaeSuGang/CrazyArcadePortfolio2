#pragma once
#include "KmEngine/GameInstanceSubsystem.h"
#include "KmBase/Archive.h"

class AActor;

class FTilemap : public ISerializable, public IDeserializable
{
public:
	void Deserialize(FArchive& Ar) override;
	void Serialize(FArchive& Ar) override;
	void Save(string strFilePath);
	void Load(string strFilePath);

public:
	FTilemap();

public:
	unsigned short m_WallTiles[15 * 13];
	unsigned short m_GroundTiles[15 * 13];

};

