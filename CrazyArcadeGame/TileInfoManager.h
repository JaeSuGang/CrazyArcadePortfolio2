#pragma once
#include "KmEngine/GameInstanceSubsystem.h"
#include "KmBase/Archive.h"

class AActor;

class FTilemapInfo : public ISerializable, public IDeserializable
{
public:
	void Deserialize(FArchive& Ar) override;
	void Serialize(FArchive& Ar) override;
	void Save(string strFilePath);
	void Load(string strFilePath);

public:
	vector<AActor*> m_ActorsOnTile[15 * 13];
	unsigned short m_WallTiles[15 * 13];
	unsigned short m_GroundTiles[15 * 13];

};

class UTileInfoManager : public UGameInstanceSubsystem
{
	typedef UGameInstanceSubsystem Super;

public:
	void Tick(float fDeltaTime) override;

private:
	FTilemapInfo* m_CurrentGameTileInfo;
};

