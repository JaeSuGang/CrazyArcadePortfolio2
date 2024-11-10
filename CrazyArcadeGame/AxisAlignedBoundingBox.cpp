#include "stdafx.h"
#include "AxisAlignedBoundingBox.h"

FAxisAlignedBoundingBox FAxisAlignedBoundingBox::CalculateCorrectPos(FVector2D SourcePos, const FAxisAlignedBoundingBox& OtherBox)
{
	FAxisAlignedBoundingBox CorrectAABB = *this;

	FVector2D CenterPositionDiff = (OtherBox.m_Center - this->m_Center);
	CenterPositionDiff.X = abs(CenterPositionDiff.X);
	CenterPositionDiff.Y = abs(CenterPositionDiff.Y);

	FVector2D RadiusSum = { this->m_WidthRadius + OtherBox.m_WidthRadius, this->m_HeightRadius + OtherBox.m_HeightRadius };

	float AbsoluteXToMove = RadiusSum.X > CenterPositionDiff.X ? RadiusSum.X - CenterPositionDiff.X : 0;
	float AbsoluteYToMove = RadiusSum.Y > CenterPositionDiff.Y ? RadiusSum.Y - CenterPositionDiff.Y : 0;

	// 가로 이동일때
	if (SourcePos.Y == CorrectAABB.m_Center.Y)
	{
		// 우측 이동
		if (SourcePos.X < this->m_Center.X)
			CorrectAABB.m_Center.X -= AbsoluteXToMove;

		// 좌측 이동
		else if (SourcePos.X > this->m_Center.X)
			CorrectAABB.m_Center.X += AbsoluteXToMove;

		// 위나 아래쪽에 가까운 경우 자동 이동
		if (this->m_Center.Y < OtherBox.m_Center.Y - OtherBox.m_HeightRadius)
		{
			CorrectAABB.m_Center.Y -= AbsoluteXToMove;
			if (CorrectAABB.m_Center.Y < OtherBox.m_Center.Y - OtherBox.m_HeightRadius - CorrectAABB.m_HeightRadius)
			{
				CorrectAABB.m_Center.Y = OtherBox.m_Center.Y - OtherBox.m_HeightRadius - CorrectAABB.m_HeightRadius;
			}
		}
		else if (this->m_Center.Y > OtherBox.m_Center.Y + OtherBox.m_HeightRadius)
		{
			CorrectAABB.m_Center.Y += AbsoluteXToMove;
			if (CorrectAABB.m_Center.Y > OtherBox.m_Center.Y + OtherBox.m_HeightRadius + CorrectAABB.m_HeightRadius)
			{
				CorrectAABB.m_Center.Y = OtherBox.m_Center.Y + OtherBox.m_HeightRadius + CorrectAABB.m_HeightRadius;
			}
		}
	}

	// 세로 이동 일때
	else if (SourcePos.X == this->m_Center.X)
	{
		// 하방향 이동
		if (SourcePos.Y < this->m_Center.Y)
		{
			CorrectAABB.m_Center.Y -= AbsoluteYToMove;
		}
		// 상방향 이동
		else if (SourcePos.Y > this->m_Center.Y)
		{
			CorrectAABB.m_Center.Y += AbsoluteYToMove;
		}

		// 좌나 우에 가까운 경우 자동 이동
		if (this->m_Center.X < OtherBox.m_Center.X - OtherBox.m_WidthRadius)
		{
			CorrectAABB.m_Center.X -= AbsoluteYToMove;
			if (CorrectAABB.m_Center.X < OtherBox.m_Center.X - OtherBox.m_WidthRadius - CorrectAABB.m_WidthRadius)
			{
				CorrectAABB.m_Center.X = OtherBox.m_Center.X - OtherBox.m_WidthRadius - CorrectAABB.m_WidthRadius;
			}
		}
		else if (this->m_Center.X > OtherBox.m_Center.X + OtherBox.m_WidthRadius)
		{
			CorrectAABB.m_Center.X += AbsoluteYToMove;
			if (CorrectAABB.m_Center.X > OtherBox.m_Center.X + OtherBox.m_WidthRadius + CorrectAABB.m_WidthRadius)
			{
				CorrectAABB.m_Center.X = OtherBox.m_Center.X + OtherBox.m_WidthRadius + CorrectAABB.m_WidthRadius;
			}
		}
	}

	return CorrectAABB;
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
