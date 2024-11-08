#include "stdafx.h"
#include "AxisAlignedBoundingBox.h"

void FAxisAlignedBoundingBox::SetCenter(FVector2D Center)
{
	float WidthRadius = (right - left) / 2;
	float HeightRadius = (bottom - top) / 2;
	
	left = Center.X - WidthRadius;
	right = Center.X + WidthRadius;
	top = Center.Y - HeightRadius;
	bottom = Center.Y - HeightRadius;
}

FVector2D FAxisAlignedBoundingBox::GetCenter() const
{
	FVector2D Center = { (right + left) / 2, (bottom + top) / 2 };
	return Center;
}

float FAxisAlignedBoundingBox::GetWidth() const
{
	return right - left;
}

float FAxisAlignedBoundingBox::GetHeight() const
{
	return bottom - top;
}

void FAxisAlignedBoundingBox::TryMove(
	const FAxisAlignedBoundingBox& StartAABB,
	const FAxisAlignedBoundingBox& FutureAABB,
	const FAxisAlignedBoundingBox& WallAABB)
{
	auto test = WallAABB.GetCenter().X;
	auto test2 = FutureAABB.GetCenter().X;
	float CenterXDiff = std::abs(WallAABB.GetCenter().X - FutureAABB.GetCenter().X);
	float CenterYDiffNotAbs = (WallAABB.GetCenter().Y - FutureAABB.GetCenter().Y);
	float XTotal = (WallAABB.GetWidth() + FutureAABB.GetWidth()) / 2;

	float OverlappedWidth = XTotal - CenterXDiff;

	FVector2D Direction = (FutureAABB.GetCenter() - StartAABB.GetCenter()).GetNormalized();
	FVector2D DifferenceVector{};
	if (Direction.X != 0)
	{
		DifferenceVector = { Direction.X / std::abs(Direction.X) * OverlappedWidth, Direction.Y / std::abs(Direction.X) * OverlappedWidth };
	}
	else
	{
		DifferenceVector = { 0.0f, CenterYDiffNotAbs};
	}

	this->SetCenter(this->GetCenter() - DifferenceVector);
}


void FAxisAlignedBoundingBox::DontOverlapWith(const FAxisAlignedBoundingBox& OtherBox)
{
	//FutureAABB = StartAABB.AddActorLocation(Dir * DeltaTime * Speed);
	//if (FutureAABB.X + FutureAABB.Scale.X.Half() > WallAABB.Pos.X - WallAABB.Scale.half())
	//	CorrectAABB.X = (WallAABB.Pos.X - WallAABB.Scale.half()) - (FutureAABB.X + FutureAABB.Scale.X.Half());
	if (left < OtherBox.right)
	{
		left = OtherBox.right;
		return;
	}
	if (right > OtherBox.left)
	{
		right = OtherBox.left;
		return;
	}
	if (top < OtherBox.bottom)
	{
		top = OtherBox.bottom;
		return;
	}
	if (bottom > OtherBox.top)
	{
		bottom = OtherBox.top;
		return;
	}
}

void FAxisAlignedBoundingBox::SetCoordinatesByActorAndSize(FVector2D ActorPos, FVector2D Size)
{
	left = ActorPos.X - Size.X;
	right = ActorPos.X + Size.X;
	top = ActorPos.Y - Size.Y;
	bottom = ActorPos.Y + Size.Y;
}

bool FAxisAlignedBoundingBox::CheckCollision(const FAxisAlignedBoundingBox& OtherBox) const
{
	if (left > OtherBox.right)
		return false;
	if (right < OtherBox.left)
		return false;
	if (top > OtherBox.bottom)
		return false;
	if (bottom < OtherBox.top)
		return false;

	return true;
}

FAxisAlignedBoundingBox::FAxisAlignedBoundingBox()
	:
	left{},
	top{},
	right{},
	bottom{}
{
}

FAxisAlignedBoundingBox::FAxisAlignedBoundingBox(float _left, float _top, float _right, float _bottom)
	:
	FAxisAlignedBoundingBox()
{
	left = _left;
	top = _top;
	right = _right;
	bottom = _bottom;
}