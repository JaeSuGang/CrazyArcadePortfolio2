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
	void EnableDebugRender();
	void DebugRender();
	void Reset();
	void AddMovable(AActor* MovableComponent);
	void AddWall(AActor* WallComponent);

public:
	void Tick(float fDeltaTime) override;

public:
	UMovementManager();

public:
	unordered_set<AActor*> m_Movables;
	unordered_set<AActor*> m_Walls;

private:
	HPEN m_hPen;
	HBRUSH m_hBrush;

};

