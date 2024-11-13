#pragma once
#include "stdafx.h"
#include "KmEngine/GameInstanceSubsystem.h"
#include "KmBase/Vector.h"
#include "AxisAlignedBoundingBox.h"

class ABlock;
class ACharacter;
class APowerUpItem;

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
	void AddPowerUpItem(APowerUpItem* Item);

public:
	void Tick(float fDeltaTime) override;

public:
	UMovementManager();

public:
	unordered_set<ACharacter*> m_Characters;
	unordered_set<ABlock*> m_Blocks;
	unordered_set<ABlock*> m_HidableBlocks;
	unordered_set<APowerUpItem*> m_PowerUpItems;

private:
	HPEN m_hPen;
	HBRUSH m_hBrush;

};

