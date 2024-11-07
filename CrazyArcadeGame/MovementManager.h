#pragma once
#include "KmEngine/GameInstanceSubsystem.h"
#include "KmBase/Vector.h"
#include "stdafx.h"

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

public:
	void Tick(float fDeltaTime) override;

public:
	UMovementManager();

public:

private:
	RECT m_MapRange;
	unordered_set<UMovableComponent*> m_Movables;
	unordered_set<UWallComponent*> m_Walls;

};

