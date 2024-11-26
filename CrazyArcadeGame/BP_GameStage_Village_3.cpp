#include "stdafx.h"
#include "BP_GameStage_Village_3.h"
#include "Tilemap.h"

BP_GameStage_Village_3::BP_GameStage_Village_3()
{
	m_Tilemap = new FTilemap{};
	m_Tilemap->Load("Resources\\TilemapData\\stage3.tilemap");

	SpawnLocations.push_back(FVector2D(60.0f, 270.0f));
	SpawnLocations.push_back(FVector2D(360.0f, 150.0f));
	SpawnLocations.push_back(FVector2D(600.0f, 150.0f));
	SpawnLocations.push_back(FVector2D(900.0f, 270.0f));
	SpawnLocations.push_back(FVector2D(60.0f, 630.0f));
	SpawnLocations.push_back(FVector2D(360.0f, 750.0f));
	SpawnLocations.push_back(FVector2D(600.0f, 750.0f));
	SpawnLocations.push_back(FVector2D(900.0f, 630.0f));

}
