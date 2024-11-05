#pragma once
#include "KmEngine/GameInstanceSubsystem.h"

__interface ISerializable
{
	virtual void Serialize() = 0;
	virtual void Deserialize() = 0;
};

class USerializeManager : public UGameInstanceSubsystem
{
	typedef UGameInstanceSubsystem Super;

public:


public:
	void Tick(float fDeltaTime) override;
};

