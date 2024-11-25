#include "stdafx.h"
#include "BP_GameStage_Village_1.h"
#include "Tilemap.h"

BP_GameStage_Village_1::BP_GameStage_Village_1()
{
	m_Tilemap = new FTilemap{};
	m_Tilemap->Load("Resources\\TilemapData\\stage1.tilemap");

	SpawnLocations.push_back(FVector2D(420.0f, 330.0f));
	SpawnLocations.push_back(FVector2D(900.0f, 810.0f));
	SpawnLocations.push_back(FVector2D(60.0f, 150.0f));
	SpawnLocations.push_back(FVector2D(840.0f, 150.0f));
	SpawnLocations.push_back(FVector2D(120.0f, 750.0f));
	SpawnLocations.push_back(FVector2D(480.0f, 690.0f));
}
