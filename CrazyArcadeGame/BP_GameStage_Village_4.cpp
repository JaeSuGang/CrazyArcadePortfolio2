#include "stdafx.h"
#include "BP_GameStage_Village_4.h"
#include "Tilemap.h"

BP_GameStage_Village_4::BP_GameStage_Village_4()
{
	m_Tilemap = new FTilemap{};
	m_Tilemap->Load("Resources\\TilemapData\\stage4.tilemap");

	SpawnLocations.push_back(FVector2D(60.0f, 90.0f));
	SpawnLocations.push_back(FVector2D(480.0f, 90.0f));
	SpawnLocations.push_back(FVector2D(900, 90.0f));
	SpawnLocations.push_back(FVector2D(60.0f, 450.0f));
	SpawnLocations.push_back(FVector2D(900, 450.0f));
	SpawnLocations.push_back(FVector2D(60.0f, 810.0f));
	SpawnLocations.push_back(FVector2D(480.0f, 810.0f));
	SpawnLocations.push_back(FVector2D(900, 810.0f));

}