#pragma once

struct FAxisAlignedBoundingBox
{
public:
	void SetCenter(FVector2D Center);
	FVector2D GetCenter() const;
	float GetWidth() const;
	float GetHeight() const;

	void TryMove(
		const FAxisAlignedBoundingBox& StartAABB,
		const FAxisAlignedBoundingBox& FutureAABB,
		const FAxisAlignedBoundingBox& WallAABB);

	void DontOverlapWith(const FAxisAlignedBoundingBox& OtherBox);
	void SetCoordinatesByActorAndSize(FVector2D ActorPos, FVector2D Size);
	bool CheckCollision(const FAxisAlignedBoundingBox& OtherBox) const;
	
	// bool CheckCollision(FVector2D OtherCirclePos, float OtherCircleRadius);

public:
	FAxisAlignedBoundingBox();
	FAxisAlignedBoundingBox(float left, float top, float right, float bottom);

public:
	float left;
	float top;
	float right;
	float bottom;
};

