#include "stdafx.h"
#include "AIManager.h"
#include "Character.h"
#include "CharacterAIController.h"
#include "AxisAlignedBoundingBox.h"
#include "SpawnManager.h"
#include "Block.h"
#include "Bomb.h"
#include "BombManager.h"
#include "MovementManager.h"
#include "KmEngine/Level.h"

void UAIManager::SetCharacterRandomPositionToGo(ACharacterAIController* AIController) const
{
	UBombManager* BombManager = GetGameInstance()->GetSubsystem<UBombManager>();

	FVector2D Position = VectorToRefinedVector(AIController->m_Character->GetPosition());
	std::list<FVector2D> TempPath;

	vector<int> Width{};
	vector<int> Height{};
	for (int i = -2; i < 3; i++)
	{
		Width.push_back(i);
		Height.push_back(i);
	}
	std::shuffle(Width.begin(), Width.end(), *RandomEngine);
	std::shuffle(Height.begin(), Height.end(), *RandomEngine);

	for (int i : Width)
	{
		for (int j : Height)
		{
			FVector2D CheckDest = Position + FVector2D::Right * 60.0f * (float)i + FVector2D::Down * 60.0f * (float)j;

			bool bIsUnsafePlace{};

			for (ABomb* Bomb : BombManager->m_Bombs)
			{
				FAxisAlignedBoundingBox ExpectedExplosionAABB1{};
				ExpectedExplosionAABB1.m_Center = Bomb->GetPosition();
				ExpectedExplosionAABB1.m_WidthRadius = Bomb->GetBombRange() * TILE_WIDTH - TILE_WIDTH / 2;
				ExpectedExplosionAABB1.m_HeightRadius = TILE_HEIGHT / 2;

				if (ExpectedExplosionAABB1.GetIsCollidedWith(CheckDest))
					bIsUnsafePlace = true;

				FAxisAlignedBoundingBox ExpectedExplosionAABB2{};
				ExpectedExplosionAABB2.m_Center = Bomb->GetPosition();
				ExpectedExplosionAABB2.m_WidthRadius = TILE_WIDTH / 2;
				ExpectedExplosionAABB2.m_HeightRadius = Bomb->GetBombRange() * TILE_HEIGHT - TILE_HEIGHT / 2;

				if (ExpectedExplosionAABB2.GetIsCollidedWith(CheckDest))
					bIsUnsafePlace = true;
			}
			if (bIsUnsafePlace)
				continue;

			bool bHasValidPath = this->FindPath(Position, CheckDest, TempPath);

			if (!bHasValidPath)
				continue;

			this->FindPath(Position, CheckDest, AIController->Path);
			return;
		}
	}

}

bool UAIManager::CheckPositionWhetherSafeToPutBomb(const ACharacter* AICharacter, FVector2D PositionToPutBomb) const
{
	UMovementManager* MovementManager = GetGameInstance()->GetSubsystem<UMovementManager>();

	PositionToPutBomb = VectorToRefinedVector(PositionToPutBomb);
	std::list<FVector2D> TempPath;

	vector<int> Width{};
	vector<int> Height{};
	for (int i = -3; i < 4; i++)
	{
		Width.push_back(i);
		Height.push_back(i);
	}
	std::random_device rd{};
	std::shuffle(Width.begin(), Width.end(), *RandomEngine);
	std::shuffle(Height.begin(), Height.end(), *RandomEngine);

	for (int i : Width)
	{
		for (int j : Height)
		{
			FVector2D PositionToHide = VectorToRefinedVector(AICharacter->GetPosition()) + FVector2D::Right * 60.0f * (float)i + FVector2D::Down * 60.0f * (float)j;

			if (GetIsOutOfMap(PositionToHide))
				continue;

			FAxisAlignedBoundingBox HideAABB{ PositionToHide, TILE_WIDTH / 2, TILE_HEIGHT / 2 };

			bool bIsInvalidPositionToHide{};
			for (ABlock* BlockToCheck : MovementManager->m_Blocks)
			{
				if (HideAABB.GetIsCollidedWith(BlockToCheck->GetPosition()))
				{
					bIsInvalidPositionToHide = true;
					break;
				}
			}
			if (bIsInvalidPositionToHide)
				continue;

			if (PositionToHide.X == PositionToPutBomb.X || PositionToHide.Y == PositionToPutBomb.Y)
				continue;

			bool bHasValidPath = this->FindPath(PositionToHide, PositionToPutBomb, TempPath);

			if (!bHasValidPath)
				continue;

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

bool UAIManager::GetIsDangerousPosition(FVector2D PositionToCheck)
{
	PositionToCheck = VectorToRefinedVector(PositionToCheck);

	UBombManager* BombManager = GetGameInstance()->GetSubsystem<UBombManager>();

	for (ABomb* BombToCheck : BombManager->m_Bombs)
	{
		FAxisAlignedBoundingBox DangerousAABB1{
			VectorToRefinedVector(BombToCheck->GetPosition()),
			BombToCheck->GetBombRange() * TILE_WIDTH + TILE_WIDTH / 2,
			TILE_HEIGHT / 2
		};
		FAxisAlignedBoundingBox DangerousAABB2{
			VectorToRefinedVector(BombToCheck->GetPosition()),
			TILE_WIDTH / 2,
			BombToCheck->GetBombRange() * TILE_HEIGHT + TILE_HEIGHT / 2
		};

		if (DangerousAABB1.GetIsCollidedWith(PositionToCheck) || DangerousAABB2.GetIsCollidedWith(PositionToCheck))
		{
			return true;
		}
	}

	return false;
}

bool UAIManager::GetRandomPlaceToPutBombNextToBreakable(const FVector2D& CenterToSearch, FVector2D& Output)
{
	UMovementManager* MoveManager = GetGameInstance()->GetSubsystem<UMovementManager>();

	FVector2D SearchingPosition{};
	FAxisAlignedBoundingBox CheckAABB{ SearchingPosition, TILE_WIDTH / 2, TILE_HEIGHT / 2 };

	vector<int> Width{};
	vector<int> Height{};
	for (int i = -3; i < 4; i++)
	{
		Width.push_back(i);
		Height.push_back(i);
	}
	std::shuffle(Width.begin(), Width.end(), *RandomEngine);
	std::shuffle(Height.begin(), Height.end(), *RandomEngine);

	for (int i : Width)
	{
		for (int j : Height)
		{
			SearchingPosition = VectorToRefinedVector(CenterToSearch) + FVector2D::Right * 60.0f * (float)i + FVector2D::Down * 60.0f * (float)j;

			if (GetIsOutOfMap(SearchingPosition))
				continue;

			CheckAABB.m_Center = SearchingPosition;

			bool bIsInvalid{};
			for (ABlock* Block : MoveManager->m_Blocks)
			{
				if (CheckAABB.GetIsCollidedWith(Block->GetPosition()))
				{
					bIsInvalid = true;
					break;
				}
			}

			if (!bIsInvalid)
			{
				Output = SearchingPosition;
				return true;
			}
		}
	}

	return false;
}

bool UAIManager::GetRandomPlaceToGo(const FVector2D& CenterToSearch, FVector2D& Output)
{
	UMovementManager* MoveManager = GetGameInstance()->GetSubsystem<UMovementManager>();

	FVector2D SearchingPosition{};
	FAxisAlignedBoundingBox CheckAABB{ SearchingPosition, TILE_WIDTH / 2, TILE_HEIGHT / 2 };

	vector<int> Width{};
	vector<int> Height{};
	for (int i = -3; i < 4; i++)
	{
		Width.push_back(i);
		Height.push_back(i);
	}
	std::random_device rd{};
	std::shuffle(Width.begin(), Width.end(), *RandomEngine);
	std::shuffle(Height.begin(), Height.end(), *RandomEngine);

	for (int i : Width)
	{
		for (int j : Height)
		{
			SearchingPosition = VectorToRefinedVector(CenterToSearch) + FVector2D::Right * 60.0f * (float)i + FVector2D::Down * 60.0f * (float)j;

			if (GetIsOutOfMap(SearchingPosition))
				continue;

			CheckAABB.m_Center = SearchingPosition;

			bool bIsInvalid{};
			for (ABlock* Block : MoveManager->m_Blocks)
			{
				if (CheckAABB.GetIsCollidedWith(Block->GetPosition()))
				{
					bIsInvalid = true;
					break;
				}
			}

			if (!bIsInvalid)
			{
				Output = SearchingPosition;
				return true;
			}
		}
	}

	return false;
}

bool UAIManager::GetRandomPlaceToPutBomb(const FVector2D& CenterToSearch, FVector2D& Output)
{
	UMovementManager* MoveManager = GetGameInstance()->GetSubsystem<UMovementManager>();

	FVector2D SearchingPosition{};
	FAxisAlignedBoundingBox CheckAABB{ SearchingPosition, TILE_WIDTH / 2, TILE_HEIGHT / 2 };

	vector<int> Width{};
	vector<int> Height{};
	for (int i = -3; i < 4; i++)
	{
		Width.push_back(i);
		Height.push_back(i);
	}
	std::random_device rd{};
	std::shuffle(Width.begin(), Width.end(), *RandomEngine);
	std::shuffle(Height.begin(), Height.end(), *RandomEngine);

	for (int i : Width)
	{
		for (int j : Height)
		{
			SearchingPosition = VectorToRefinedVector(CenterToSearch) + FVector2D::Right * 60.0f * (float)i + FVector2D::Down * 60.0f * (float)j;

			if (GetIsOutOfMap(SearchingPosition))
				continue;

			CheckAABB.m_Center = SearchingPosition;

			bool bIsInvalid{};
			for (ABlock* Block : MoveManager->m_Blocks)
			{
				if (CheckAABB.GetIsCollidedWith(Block->GetPosition()))
				{
					bIsInvalid = true;
					break;
				}
			}

			if (!bIsInvalid)
			{
				Output = SearchingPosition;
				return true;
			}
		}
	}

	return false;
}

bool UAIManager::FindPath(FVector2D StartPos, FVector2D DestinationPos, std::list<FVector2D>& ListToContainPath) const
{
	std::multiset<shared_ptr<FPathNode>, CompareFunctionForOpenList> OpenList{};
	unordered_set<shared_ptr<FPathNode>> ClosedList{};

	StartPos = TileIndexToVector(VectorToTileIndex(StartPos));
	DestinationPos = TileIndexToVector(VectorToTileIndex(DestinationPos));

	shared_ptr<FPathNode> StartNode{ new FPathNode{ nullptr, StartPos} };
	OpenList.insert(StartNode);

	while (OpenList.size() > 0 && OpenList.size() < 50)
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

UAIManager::UAIManager()
{
	std::random_device rd{};
	RandomEngine = new std::default_random_engine{};
	RandomEngine->seed(rd());
}

UAIManager::~UAIManager()
{
	SAFE_DELETE(RandomEngine);
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
