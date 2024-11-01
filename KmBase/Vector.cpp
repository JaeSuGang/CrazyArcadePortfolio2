#include "stdafx.h"
#include "Vector.h"

const FVector2D FVector2D::Zero = FVector2D{ 0.0f, 0.0f };
const FVector2D FVector2D::Up = FVector2D{ 0.0f, -1.0f };
const FVector2D FVector2D::Down = FVector2D{ 0.0f, 1.0f };
const FVector2D FVector2D::Left = FVector2D{ -1.0f, 0.0f };
const FVector2D FVector2D::Right = FVector2D{ 1.0f, 0.0f };

float FVector2D::GetLength()
{
	return std::sqrt(X * X + Y * Y);
}

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

FVector2D& FVector2D::operator+=(const FVector2D& Other)
{
	X += Other.X;
	Y += Other.Y;

	return *this;
}

FVector2D FVector2D::operator+(FVector2D Other)
{
	FVector2D NewVector{};
	NewVector.X = X + Other.X;
	NewVector.Y = Y + Other.Y;
	return NewVector;
}

FVector2D FVector2D::operator-(FVector2D Other)
{
	FVector2D NewVector{};
	NewVector.X = X - Other.X;
	NewVector.Y = Y - Other.Y;
	return NewVector;
}


FVector2D FVector2D::operator*(float fValue)
{
	FVector2D NewVector{};
	NewVector.X = X * fValue;
	NewVector.Y = Y * fValue;
	return NewVector;
}

FVector2D FVector2D::operator/(float fValue)
{
	FVector2D NewVector{};
	NewVector.X = X / fValue;
	NewVector.Y = Y / fValue;
	return NewVector;
}
