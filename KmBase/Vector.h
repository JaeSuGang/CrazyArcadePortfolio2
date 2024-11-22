#pragma once
#include "stdafx.h"

struct FVector2D
{
public:
	float GetLength() const;
	FVector2D GetNormalized() const;

public:
	static const vector<FVector2D> Directions;
	static const FVector2D Zero;
	static const FVector2D Up;
	static const FVector2D Down;
	static const FVector2D Left;
	static const FVector2D Right;

public:
	FVector2D() = default;
	FVector2D(float _X, float _Y);
	FVector2D(const FVector2D& Other);
	FVector2D& operator=(const FVector2D& Other);
	FVector2D& operator+=(const FVector2D& Other);
	bool operator==(const FVector2D& Other) const;
	FVector2D operator+(FVector2D Other) const;
	FVector2D operator-(FVector2D Other) const;
	FVector2D operator*(float fValue) const;
	FVector2D operator/(float fValue) const;

public:
	float X;
	float Y;
};
