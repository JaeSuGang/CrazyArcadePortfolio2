#include "stdafx.h"
#include "AIManager.h"
#include "Character.h"
#include "CharacterAIController.h"
#include "AxisAlignedBoundingBox.h"
#include "SpawnManager.h"
#include "Block.h"
#include "Bomb.h"
#include "BombManager.h"
#include "KmEngine/Level.h"

void UAIManager::FetchDangerousAABBRange(std::vector<FAxisAlignedBoundingBox>& VectorToFetch)
{
}

bool UAIManager::CheckPositionWhetherSafeToPutBomb(const ACharacter* AICharacter, FVector2D Position, FVector2D& EscapeDest)
{
	Position = VectorToRefinedVector(Position);
	std::list<FVector2D> TempPath;

	for (int i = -2; i < 3; i++)
	{
		for (int j = -2; j < 3; j++)
		{
			if (i == 0 || j == 0)
				continue;

			FVector2D CheckDest = Position + FVector2D::Right * 60.0f * i + FVector2D::Down * 60.0f * j;

			bool bHasValidPath = this->FindPath(AICharacter->GetPosition(), CheckDest, TempPath);

			if (!bHasValidPath)
				continue;

			EscapeDest = CheckDest;
			return true;
		}
	}

	return false;
}

void UAIManager::GetAdjacentTilePos(FVector2D CenterPos, std::vector<FVector2D>& ListToContainAdjacentTiles)
{
	ListToContainAdjacentTiles.push_back(CenterPos+ FVector2D::Up * TILE_HEIGHT);
	ListToContainAdjacentTiles.push_back(CenterPos + FVector2D::Left * TILE_WIDTH);
	ListToContainAdjacentTiles.push_back(CenterPos + FVector2D::Right * TILE_WIDTH);
	ListToContainAdjacentTiles.push_back(CenterPos + FVector2D::Down * TILE_HEIGHT);
}

bool UAIManager::FindPath(FVector2D StartPos, FVector2D DestinationPos, std::list<FVector2D>& ListToContainPath)
{
	std::multiset<shared_ptr<FPathNode>, CompareFunctionForOpenList> OpenList{};
	unordered_set<shared_ptr<FPathNode>> ClosedList{};

	StartPos = TileIndexToVector(VectorToTileIndex(StartPos));
	DestinationPos = TileIndexToVector(VectorToTileIndex(DestinationPos));

	shared_ptr<FPathNode> StartNode{ new FPathNode{ nullptr, StartPos} };
	OpenList.insert(StartNode);

	while (OpenList.size() > 0 )
	{
		shared_ptr<FPathNode> CenterNode = *OpenList.begin();

		OpenList.erase(OpenList.begin());
		ClosedList.insert(CenterNode);

		if (CenterNode->m_Position == DestinationPos)
		{
			ListToContainPath.clear();
			shared_ptr<FPathNode> NodeToLoop{ CenterNode };
			while (NodeToLoop.get() != nullptr)
			{
				ListToContainPath.push_front(NodeToLoop->m_Position);
				NodeToLoop = NodeToLoop->m_ParentNode;
			}
			return true;
		}

		vector<FVector2D> AdjacentTiles{};
		UAIManager::GetAdjacentTilePos(CenterNode->m_Position, AdjacentTiles);

		for (FVector2D Pos : AdjacentTiles)
		{
			bool bIsInvalidPath{};

			// ClosedList에 존재하는 중복 위치일시 스킵
			for (shared_ptr<FPathNode> Node : ClosedList)
			{
				if (Pos == Node->m_Position)
				{
					bIsInvalidPath = true;
					break;
				}
			}
			if (bIsInvalidPath)
				continue;

			// Block으로 막힌 위치일시 스킵
			for (ABlock* Block : m_Blocks)
			{
				if (Pos == Block->GetPosition() && !Block->GetPassable())
				{
					bIsInvalidPath = true;
					break;
				}
			}

			if (bIsInvalidPath)
				continue;

			// OpenList에 존재하는 중복 위치일시 g값 비교후 부모노드 변경할지 결정
			for (shared_ptr<FPathNode> Node : OpenList)
			{
				if (Pos != Node->m_Position)
					continue;

				if (Node->m_fGScore < abs(Pos.X - StartPos.X) + abs(Pos.Y - StartPos.Y))
					CenterNode->m_ParentNode = Node;
			}

			if (bIsInvalidPath)
				continue;

			shared_ptr<FPathNode> AdjacentNode{ new FPathNode{CenterNode, Pos} };
			AdjacentNode->m_ParentNode = CenterNode;
			// 맨해튼 거리법
			AdjacentNode->m_fGScore = abs(StartPos.X - Pos.X) + abs(StartPos.Y - Pos.Y);
			AdjacentNode->m_fHScore = abs(DestinationPos.X - Pos.X) + abs(DestinationPos.Y - Pos.Y);
			OpenList.insert(AdjacentNode);
		}


	}

	ListToContainPath.clear();
	return false;
}

void UAIManager::AddAIPawn(APawn* Pawn)
{
	auto AIPawnIter = m_AIPawns.find(Pawn);
	if (AIPawnIter == m_AIPawns.end())
	{
		m_AIPawns.insert(Pawn);
	}

}

void UAIManager::RemoveAIPawn(APawn* Pawn)
{
	auto AIPawnIter = m_AIPawns.find(Pawn);

	if (AIPawnIter != m_AIPawns.end())
	{
		m_AIPawns.erase(AIPawnIter);
	}
}

void UAIManager::ClearAIPawns()
{
	m_AIPawns.clear();
}

void UAIManager::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	auto AIPawnIter = m_AIPawns.begin();
	while (AIPawnIter != m_AIPawns.end())
	{
		APawn* AIPawn = *AIPawnIter;
		
		//if (ACharacter* AICharacter = dynamic_cast<ACharacter*>(AIPawn))
		//{
		//	ACharacterAIController* Controller = dynamic_cast<ACharacterAIController*>(AICharacter->GetController());
		//	AICharacter->Move(Controller->GetDirection());
		//	float fAccumulatedTime = Controller->GetAccumulatedTime();
		//	float fChangeDirectionTime = Controller->GetChangeDirectionTime();
		//	if (fAccumulatedTime > fChangeDirectionTime)
		//	{
		//		Controller->SetRandomDirection();
		//		Controller->SetAccumulatedTime(0.0f);
		//	}
		//}

		++AIPawnIter;
	}
}

float FPathNode::GetFScore() const
{
	return m_fGScore + m_fHScore;
}

FPathNode::FPathNode(std::shared_ptr<FPathNode> ParentNode, FVector2D Position)
	:
	m_ParentNode{ParentNode},
	m_Position{Position},
	m_fGScore{},
	m_fHScore{}
{

}

bool CompareFunctionForOpenList::operator()(const shared_ptr<FPathNode> Left, const shared_ptr<FPathNode> Right) const
{
	return Left->GetFScore() < Right->GetFScore();
}
