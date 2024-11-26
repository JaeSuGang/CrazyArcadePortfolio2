#include "stdafx.h"
#include "BP_GameStage_Village_2.h"
#include "Tilemap.h"

BP_GameStage_Village_2::BP_GameStage_Village_2()
{
	m_Tilemap = new FTilemap{};
	m_Tilemap->Load("Resources\\TilemapData\\stage2.tilemap");

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			SpawnLocations.push_back(FVector2D(60.0f + i * 2 * TILE_WIDTH, 90.0f + j * 2 * TILE_HEIGHT));
		}
	}
}

void BP_GameStage_Village_2::CheckGameFinished()
{
	if (LocalPlayerCharacter == nullptr)
		return;

	if (Characters.size() <= 5 && *Characters.begin() == LocalPlayerCharacter)
	{
		this->OnWin();
	}

	else if (Characters.find(LocalPlayerCharacter) == Characters.end())
	{
		this->OnLose();
	}
}
