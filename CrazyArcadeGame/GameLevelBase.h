#pragma once
#include "KmEngine/Level.h"

class FTilemap;
class ACharacter;

class UGameLevelBase : public ULevel
{
	typedef ULevel Super;

public:
	// Constructors and Overrides
	~UGameLevelBase();
	void Release();
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
	void BeginPlay() override;
	virtual void CheckGameFinished();
	virtual void OnWin();
	virtual void OnLose();



	void AddToCharacters(ACharacter* Character);

	void RemoveFromCharacters(ACharacter* Character);

public:
	ACCESSORS_ALL(ACharacter*, LocalPlayerCharacter);
	ACCESSORS_ALL(float, ElapsedTime);
	ACCESSORS_ALL(bool, bIsGameStarted);

protected:
	ACharacter* LocalPlayerCharacter;
	unordered_set<ACharacter*> Characters;
	vector<FVector2D> SpawnLocations;
	FTilemap* m_Tilemap;
	bool bIsGameStarted;
	bool bIsGameFinished;
	float ElapsedTime;
};

