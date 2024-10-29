#pragma once

class FVector2D
{
public:
	FVector2D() = default;
	FVector2D(float _X, float _Y);
	FVector2D(const FVector2D& Other);
	FVector2D& operator=(const FVector2D& Other);

public:
	float X;
	float Y;
};

class FVector3D
{
public:
	float X;
	float Y;
	float Z;
};
