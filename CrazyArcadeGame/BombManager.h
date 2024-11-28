#pragma once
#include "stdafx.h"
#include "Explodable.h"
#include "KmEngine/GameInstanceSubsystem.h"

class ABomb;
class AActor;
class ABlock;
class ACharacter;
class AExplosion;

class UBombManager : public UGameInstanceSubsystem
{
	typedef UGameInstanceSubsystem Super;

public:
	void AddBlock(ABlock* BlockActor);
	void AddExplodable(IExplodable* Explodable);
	void AddCharacter(ACharacter* CharacterActor);
	void AddExplosion(AExplosion* ExplosionActor);
	void RemoveExplosion(AExplosion* ExplosionActor);
	bool TryPutBomb(int nTileIndex, ACharacter* Spawner);
	void ForcePutBomb(int nTileIndex, ACharacter* Spawner);
	void Explode(int nTileIndex, int nRange);
	void ExpoldeAllCharacters();


public:
	void Tick(float fDeltaTime) override;

public:
	unordered_set<AExplosion*> m_Explosions;
	unordered_set<ACharacter*> m_Characters;
	unordered_set<ABlock*> m_Blocks;
	unordered_set<ABomb*> m_Bombs;
	unordered_set<IExplodable*> m_Explodables;

private:
	float m_fAccumulatedDeltaTime;
};

