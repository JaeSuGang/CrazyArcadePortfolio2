#include "stdafx.h"

int VectorToTileIndex(FVector2D Vector)
{
	int nX = (int)((Vector.X - 30.0f) / 60);
	int nY = (int)((Vector.Y - 60.0f) / 60);

	return nY * 15 + nX;
}

float VectorToRenderPriority(FVector2D Vector)
{
	int nY = (int)((Vector.Y - 60.0f) / 60.0f);

	return (float)(10 + nY);
}

FVector2D TileIndexToVector(int nTileIndex)
{
	int nX = nTileIndex % 15;
	int nY = nTileIndex / 15;

	FVector2D ReturnVector = { nX * 60.0f + 60.0f, nY * 60.0f + 90.0f};
	return ReturnVector;
}
