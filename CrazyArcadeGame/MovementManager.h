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
	void AddMovable(AActor* MovableActor);
	void AddWall(AActor* WallActor);
	void AddExplosion(AActor* ExplosionActor);

public:
	void Tick(float fDeltaTime) override;

public:
	UMovementManager();

public:
	unordered_set<AActor*> m_Movables;
	unordered_set<AActor*> m_Walls;
	unordered_set<AActor*> m_Explosions;

private:
	HPEN m_hPen;
	HBRUSH m_hBrush;

};

