#pragma once
#include "KmEngine/GameInstanceSubsystem.h"
#include "stdafx.h"
#include "AxisAlignedBoundingBox.h"

class APawn;
class ABlock;
class ACharacter;
class ACharacterAIController;

struct FPathNode : public std::enable_shared_from_this<FPathNode>
{
public:
	float GetFScore() const;

public:
	FPathNode(shared_ptr<FPathNode> ParentNode, FVector2D Position);

public:
	shared_ptr<FPathNode> m_ParentNode;
	FVector2D m_Position;
	float m_fGScore;
	float m_fHScore;
};

struct CompareFunctionForOpenList
{
public:
	bool operator()(const shared_ptr<FPathNode> Left, const shared_ptr<FPathNode> Right) const;


};

class UAIManager : public UGameInstanceSubsystem
{
	typedef UGameInstanceSubsystem Super;

public:
	bool GetIsDangerousPosition(FVector2D PositionToCheck);

	bool GetRandomPlaceToPutBombNextToBreakable(const FVector2D& CenterToSearch, FVector2D& Output);

	bool GetRandomPlaceToPutBomb(const FVector2D& CenterToSearch, FVector2D& Output);

	bool GetRandomPlaceToGo(const FVector2D& CenterToSearch, FVector2D& Output);

	bool CheckPositionWhetherSafeToPutBomb(const ACharacter* AICharacter, FVector2D PositionToPutBomb) const;

	bool FindPath(FVector2D StartPos, FVector2D DestinationPos, std::list<FVector2D>& ListToContainPath) const;

	static void GetAdjacentTilePos(FVector2D CenterPos, std::vector<FVector2D>& ListToContainAdjacentTiles);

	void SetCharacterRandomPositionToGo(ACharacterAIController* AIController) const;

public:
	void AddAIPawn(APawn* Pawn);
	void RemoveAIPawn(APawn* Pawn);
	void ClearAIPawns();

public:
	UAIManager();
	~UAIManager();
	void Tick(float fDeltaTime) override;

public:
	std::default_random_engine* RandomEngine;
	std::random_device RandomDevice;
	unordered_set<APawn*> m_AIPawns;
	unordered_set<ABlock*> m_Blocks;
};

