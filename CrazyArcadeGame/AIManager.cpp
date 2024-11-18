#include "stdafx.h"
#include "AIManager.h"
#include "Character.h"
#include "CharacterAIController.h"
#include "AxisAlignedBoundingBox.h"
#include "Block.h"

void UAIManager::GetAdjacentTilePos(FVector2D CenterPos, std::vector<FVector2D>& ListToContainAdjacentTiles)
{
	ListToContainAdjacentTiles.push_back(CenterPos+ FVector2D::Up * TILE_HEIGHT);
	ListToContainAdjacentTiles.push_back(CenterPos + FVector2D::Left * TILE_WIDTH);
	ListToContainAdjacentTiles.push_back(CenterPos + FVector2D::Right * TILE_WIDTH);
	ListToContainAdjacentTiles.push_back(CenterPos + FVector2D::Down * TILE_HEIGHT);
}

bool UAIManager::FindPath(FVector2D StartPos, FVector2D DestinationPos, std::list<FVector2D>& ListToContainPath)
{
	std::set<shared_ptr<FPathNode>, CompareFunctionForOpenList> OpenList{};
	unordered_set<shared_ptr<FPathNode>> ClosedList{};

	shared_ptr<FPathNode> StartNode{ new FPathNode{ nullptr, StartPos } };
	StartNode->m_fHeuristicScore = 0.0f;
	OpenList.insert(StartNode);

	while (OpenList.size() <= 0 )
	{
		shared_ptr<FPathNode> CenterNode = *OpenList.begin();

		vector<FVector2D> AdjacentTiles{};
		UAIManager::GetAdjacentTilePos(CenterNode->m_Position, AdjacentTiles);

		for (FVector2D Pos : AdjacentTiles)
		{
			bool bIsInvalidPath{};

			// OpenList에 존재하는 중복 위치일시 스킵
			for (shared_ptr<FPathNode> Node : OpenList)
			{
				if (Pos == Node->m_Position)
				{
					bIsInvalidPath = true;
					break;
				}
			}

			// ClosedList에 존재하는 중복 위치일시 스킵
			for (shared_ptr<FPathNode> Node : ClosedList)
			{
				if (Pos == Node->m_Position)
				{
					bIsInvalidPath = true;
					break;
				}
			}

			// Block으로 막힌 위치일시 스킵
			for (ABlock* Block : m_Blocks)
			{
				if (Pos == Block->GetPosition())
				{
					bIsInvalidPath = true;
					break;
				}
			}

			if (bIsInvalidPath)
				continue;

			shared_ptr<FPathNode> AdjacentNode{ new FPathNode{CenterNode, Pos} };
			AdjacentNode->m_ParentNode = CenterNode;
			OpenList.insert(AdjacentNode);
		}

		OpenList.erase(OpenList.begin());
		ClosedList.insert(CenterNode);
	}
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

FPathNode::FPathNode(std::shared_ptr<FPathNode> ParentNode, FVector2D Position)
	:
	m_ParentNode{ParentNode},
	m_Position{Position},
	m_fHeuristicScore{}
{

}

bool CompareFunctionForOpenList::operator()(const FPathNode* Left, const FPathNode* Right)
{
	return Left->m_fHeuristicScore < Right->m_fHeuristicScore;
}
