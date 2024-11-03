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
	void Reset();
	void AddMovable(UMovableComponent* MovableComponent);

public:
	void Tick(float fDeltaTime) override;

private:
	unordered_set<UMovableComponent*> m_Movables;
	unordered_set<UWallComponent*> m_Walls;

};

