#include "stdafx.h"
#include "Vector.h"

FVector2D::FVector2D(float _X, float _Y)
{
	X = _X;
	Y = _Y;
}

FVector2D::FVector2D(const FVector2D& Other)
{
	X = Other.X;
	Y = Other.Y;
}

FVector2D& FVector2D::operator=(const FVector2D& Other)
{
	X = Other.X;
	Y = Other.Y;

	return *this;
}
