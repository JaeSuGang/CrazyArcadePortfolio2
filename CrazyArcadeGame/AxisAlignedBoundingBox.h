#pragma once

struct FAxisAlignedBoundingBox
{
public:
	FAxisAlignedBoundingBox CalculateCorrectPos(FVector2D SourcePos, const FAxisAlignedBoundingBox& OtherBox);
	bool GetIsCollidedWith(const FAxisAlignedBoundingBox& OtherBox) const;

public:
	FAxisAlignedBoundingBox();
	FAxisAlignedBoundingBox(FVector2D Center, float WidthRadius, float HeightRadius);

public:
	FVector2D m_Center;
	float m_WidthRadius;
	float m_HeightRadius;
};

