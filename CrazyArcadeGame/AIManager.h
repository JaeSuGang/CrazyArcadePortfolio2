#pragma once
#include "KmEngine/GameInstanceSubsystem.h"
#include "stdafx.h"

class APawn;
class ABlock;

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
	static void GetAdjacentTilePos(FVector2D CenterPos, std::vector<FVector2D>& ListToContainAdjacentTiles);
	bool FindPath(FVector2D StartPos, FVector2D DestinationPos, std::list<FVector2D>& ListToContainPath);

public:
	void AddAIPawn(APawn* Pawn);
	void RemoveAIPawn(APawn* Pawn);
	void ClearAIPawns();

public:
	void Tick(float fDeltaTime) override;

public:
	unordered_set<APawn*> m_AIPawns;
	unordered_set<ABlock*> m_Blocks;
};

