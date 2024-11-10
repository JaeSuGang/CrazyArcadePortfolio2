#include "stdafx.h"
#include "AxisAlignedBoundingBox.h"

void FAxisAlignedBoundingBox::SetToCorrectPos(FVector2D SourcePos, const FAxisAlignedBoundingBox& OtherBox)
{
	FVector2D CenterPositionDiff = (OtherBox.m_Center - this->m_Center);
	CenterPositionDiff.X = abs(CenterPositionDiff.X);
	CenterPositionDiff.Y = abs(CenterPositionDiff.Y);

	FVector2D RadiusSum = { this->m_WidthRadius + OtherBox.m_WidthRadius, this->m_HeightRadius + OtherBox.m_HeightRadius };

	float AbsoluteXToMove = RadiusSum.X > CenterPositionDiff.X ? RadiusSum.X - CenterPositionDiff.X : 0;
	float AbsoluteYToMove = RadiusSum.Y > CenterPositionDiff.Y ? RadiusSum.Y - CenterPositionDiff.Y : 0;

	// 우방향 이동일 때
	if (SourcePos.X < this->m_Center.X)
		this->m_Center.X -= AbsoluteXToMove;
	// 좌방향 이동일 때
	else
		this->m_Center.X += AbsoluteXToMove;
	// 하방향 이동일 때
	if (SourcePos.Y < this->m_Center.Y)
		this->m_Center.Y -= AbsoluteYToMove;
	else
		this->m_Center.Y += AbsoluteYToMove;
}

bool FAxisAlignedBoundingBox::GetIsCollidedWith(const FAxisAlignedBoundingBox& OtherBox) const
{
	FVector2D CenterPositionDiff = (OtherBox.m_Center - this->m_Center);
	CenterPositionDiff.X = abs(CenterPositionDiff.X);
	CenterPositionDiff.Y = abs(CenterPositionDiff.Y);

	FVector2D RadiusSum = {this->m_WidthRadius + OtherBox.m_WidthRadius, this->m_HeightRadius + OtherBox.m_HeightRadius};

	if (CenterPositionDiff.X < RadiusSum.X && CenterPositionDiff.Y < RadiusSum.Y)
		return true;

	return false;
}

FAxisAlignedBoundingBox::FAxisAlignedBoundingBox()
	:
	m_Center{},
	m_HeightRadius{},
	m_WidthRadius{}
{
}

FAxisAlignedBoundingBox::FAxisAlignedBoundingBox(FVector2D Center, float WidthRadius, float HeightRadius)
	:
	FAxisAlignedBoundingBox()
{
	m_Center = Center;
	m_WidthRadius = WidthRadius;
	m_HeightRadius = HeightRadius;
}
