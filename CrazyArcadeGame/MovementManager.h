#pragma once
#include "KmEngine/GameInstanceSubsystem.h"
#include "KmBase/Vector.h"

class ACharacter;

class UMovementManager : public UGameInstanceSubsystem
{
public:
	void Move(ACharacter* Character, FVector2D DirectionVector);
};

