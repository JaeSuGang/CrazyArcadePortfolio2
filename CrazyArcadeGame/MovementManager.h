#pragma once
#include "KmEngine/GameInstanceSubsystem.h"
#include "KmBase/Vector.h"
#include "stdafx.h"

class ACharacter;
class UMovableComponent;
class UWallComponent;

struct FMapLocation
{
	float Up;
	float Down;
	float Left;
	float Right;
};

class UMovementManager : public UGameInstanceSubsystem
{
	typedef UGameInstanceSubsystem Super;

public:
	void EnableDebugRender();
	void DebugRender();
	void Reset();
	void AddMovable(UMovableComponent* MovableComponent);

public:
	void Tick(float fDeltaTime) override;

public:
	UMovementManager();

public:
	FMapLocation m_MapLocation;

private:
	unordered_set<UMovableComponent*> m_Movables;
	unordered_set<UWallComponent*> m_Walls;

};

