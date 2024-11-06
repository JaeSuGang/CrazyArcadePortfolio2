#pragma once
#include "KmEngine/ActorComponent.h"

class UClickableUIComponent : public UActorComponent
{
	typedef UActorComponent Super;

public:
	enum class EClickableUIType : unsigned short
	{
		GroundTilePaint,
		WallTilePaint
	};

public:
	void SetClickableUIType(EClickableUIType ClickableUIType);
	EClickableUIType GetClickableUIType();
	int GetValue();
	void SetValue(int nValue);

public:
	void BeginPlay() override;
	void TickComponent(float fDeltaTime) override;

private:
	EClickableUIType m_ClickableUIType;
	int m_nValue;
};

