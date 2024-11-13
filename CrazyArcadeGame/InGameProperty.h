#pragma once
struct FInGameProperty
{
public:
	FVector2D m_CollisionSize = { 60.0f, 60.0f };
	FVector2D m_Velocity;
	float m_fElapsedTimeAfterExplosion;

	bool m_bIsMoving;
	bool m_bIsAlreadyExploded;
};

