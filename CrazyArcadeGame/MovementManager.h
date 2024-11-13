#pragma once
#include "stdafx.h"
#include "KmEngine/GameInstanceSubsystem.h"
#include "KmBase/Vector.h"
#include "AxisAlignedBoundingBox.h"

class ACharacter;
class ABlock;
class UMovableComponent;
class UWallComponent;

struct FLerpEvent
{
public:
	FLerpEvent(FVector2D StartPos, FVector2D DestPos, float fTotalTime);

public:
	FVector2D m_StartPos;
	FVector2D m_DestPos;
	float m_fTotalTime;
	float m_fAccumulatedTime;

};

class UMovementManager : public UGameInstanceSubsystem
{
	typedef UGameInstanceSubsystem Super;

public:
	AActor* GetActorInAABB(FAxisAlignedBoundingBox AABB) const;
	ABlock* GetBlockInAABB(FAxisAlignedBoundingBox AABB) const;
	AActor* GetMovableInAABB(FAxisAlignedBoundingBox AABB) const;
	AActor* GetHidablePlaceInAABB(FAxisAlignedBoundingBox AABB) const;
	AActor* GetIsInHidable(AActor* ActorToCheck);
	void EnableDebugRender();
	void DebugRender();
	void Reset();
	void AddHidableBlock(ABlock* HidablePlaceActor);
	void AddCharacter(ACharacter* MovableActor);
	void AddBlock(ABlock* WallActor);

public:
	void Tick(float fDeltaTime) override;

public:
	UMovementManager();

public:
	unordered_set<ACharacter*> m_Characters;
	unordered_set<ABlock*> m_Blocks;
	unordered_set<ABlock*> m_HidableBlocks;
	vector<FLerpEvent> m_LerpEvents;

private:
	HPEN m_hPen;
	HBRUSH m_hBrush;

};

