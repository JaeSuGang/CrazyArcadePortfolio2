#pragma once
#include "stdafx.h"
#include "KmEngine/GameInstanceSubsystem.h"
#include "KmBase/Vector.h"
#include "AxisAlignedBoundingBox.h"

class ACharacter;
class UMovableComponent;
class UWallComponent;

class UMovementManager : public UGameInstanceSubsystem
{
	typedef UGameInstanceSubsystem Super;

public:
	void SetMapRange(RECT Range);
	void EnableDebugRender();
	void DebugRender();
	void Reset();
	void AddMovable(UMovableComponent* MovableComponent);
	void AddWall(UWallComponent* WallComponent);
	unordered_set<UWallComponent*>& GetWalls();

public:
	void Tick(float fDeltaTime) override;

public:
	UMovementManager();

public:

private:
	HPEN m_hPen;
	HBRUSH m_hBrush;
	FAxisAlignedBoundingBox m_MapRange;
	unordered_set<UMovableComponent*> m_Movables;
	unordered_set<UWallComponent*> m_Walls;

};

