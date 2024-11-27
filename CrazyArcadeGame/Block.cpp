#include "stdafx.h"
#include "Block.h"

#include "KmEngine/RenderComponent.h"
#include "KmEngine/RandomManager.h"
#include "AxisAlignedBoundingBox.h"
#include "BombManager.h"
#include "MovementManager.h"
#include "SpawnManager.h"
#include "AIManager.h"

void ABlock::BeginPlay()
{
	Super::BeginPlay();

	UMovementManager* MovementManager = GetGameInstance()->GetSubsystem<UMovementManager>();
	MovementManager->AddBlock(this);
	if (m_bIsHidable)
		MovementManager->AddHidableBlock(this);

	UBombManager* BombManager = GetGameInstance()->GetSubsystem<UBombManager>();
	BombManager->AddExplodable(this);
	BombManager->AddBlock(this);

	UAIManager* AIManager = GetGameInstance()->GetSubsystem<UAIManager>();
	AIManager->m_Blocks.insert(this);
}

void ABlock::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	if (m_bIsMoving)
	{
		FVector2D Direction = (m_DestinationPos - m_Position).GetNormalized();

		AddPosition(Direction * 100.0f * fDeltaTime);

		if ((m_DestinationPos - m_Position).GetLength() < 5.0f)
		{
			this->SetPosition(m_DestinationPos);
			m_bIsMoving = false;
		}
	}

	if (m_bIsAlreadyExploded)
		m_fElapsedTimeAfterExplosion += fDeltaTime;

	if (m_fElapsedTimeAfterExplosion > 0.4f)
	{
		if (m_bIsItemSpawnable)
		{

		}
		this->Destroy();
	}

	else if (m_fElapsedTimeAfterExplosion > 0.0f)
		this->PlayFadeAnimation();

	if (m_fAccumulatedPushedTime > 0.0f)
		m_fAccumulatedPushedTime -= fDeltaTime / 2;
}

void ABlock::LateTick(float fDeltaTime)
{
	Super::LateTick(fDeltaTime);

}

void ABlock::Release()
{
	UMovementManager* MovementManager = GetGameInstance()->GetSubsystem<UMovementManager>();
	MovementManager->m_Blocks.erase(this);
	MovementManager->m_HidableBlocks.erase(this);

	UBombManager* BombManager = GetGameInstance()->GetSubsystem<UBombManager>();
	BombManager->m_Blocks.erase(this);
	BombManager->m_Explodables.erase(this);

	UAIManager* AIManager = GetGameInstance()->GetSubsystem<UAIManager>();
	AIManager->m_Blocks.erase(this);

}

ABlock::~ABlock()
{
	this->Release();
}

ABlock::ABlock()
	:
	m_DestinationPos{},
	m_fAccumulatedPushedTime{},
	m_bIsBreakable{},
	m_bIsMoving{},
	m_bIsPassable{},
	m_bIsPushable{},
	m_bIsHidable{}
{
}

void ABlock::SpawnItem()
{
	USpawnManager* SpawnManager = GetGameInstance()->GetSubsystem<USpawnManager>();
	SpawnManager->SpawnRandomItem(GetPosition());
}

void ABlock::PlayFadeAnimation()
{
	int nFlicker = (int)(m_fElapsedTimeAfterExplosion / 0.02f);
	URenderComponent* RenderComponent = GetComponentByClass<URenderComponent>();

	if (nFlicker % 2 == 0)
		RenderComponent->SetIsHidden(true);
	else
		RenderComponent->SetIsHidden(false);
}

void ABlock::OnPushed(FVector2D Direction)
{
	if (m_bIsMoving || !m_bIsPushable)
		return;

	m_fAccumulatedPushedTime = 0.0f;

	FAxisAlignedBoundingBox PredictedAABB = { m_Position + Direction * 60.0f, TILE_WIDTH / 2, TILE_HEIGHT / 2 };
	UMovementManager* MovementManager = GetGameInstance()->GetSubsystem<UMovementManager>();
	if (MovementManager->GetMovableInAABB(PredictedAABB))
		return;

	ABlock* BehindBlockActor = MovementManager->GetBlockInAABB(PredictedAABB);

	if (BehindBlockActor && !BehindBlockActor->m_bIsPassable)
		return;

	if (BehindBlockActor && BehindBlockActor->m_bIsHidable)
		BehindBlockActor->Destroy();

	m_DestinationPos = PredictedAABB.m_Center;
	m_bIsMoving = true;
}

void ABlock::SetAccumulatedPushedTime(float fTime)
{
	m_fAccumulatedPushedTime = fTime;
}

void ABlock::SetPassable(bool bPassable)
{
	m_bIsPassable = bPassable;
}

void ABlock::SetHidable(bool bHidable)
{
	m_bIsHidable = bHidable;
}

void ABlock::SetBreakable(bool bBreakable)
{
	m_bIsBreakable = bBreakable;
}

void ABlock::SetPushable(bool bPushable)
{
	m_bIsPushable = bPushable;
}

void ABlock::SetItemSpawnable(bool bItemSpawnable)
{
	m_bIsItemSpawnable = bItemSpawnable;
}

bool ABlock::GetItemSpawnable() const
{
	return m_bIsItemSpawnable;
}

bool ABlock::GetPushable() const
{
	return m_bIsPushable;
}

bool ABlock::GetBreakable() const
{
	return m_bIsBreakable;
}

bool ABlock::GetHidable() const
{
	return m_bIsHidable;
}

float ABlock::GetAccumulatedPushedTime() const
{
	return m_fAccumulatedPushedTime;
}

bool ABlock::GetPassable() const
{
	return m_bIsPassable;
}

void ABlock::AddAccumulatedPushedTime(float fTime)
{
	m_fAccumulatedPushedTime += fTime;
}

void ABlock::OnExploded()
{
	if (m_bIsAlreadyExploded || !m_bIsBreakable)
		return;

	m_bIsAlreadyExploded = true;

	URandomManager* RandomManager = GEngine->GetEngineSubsystem<URandomManager>();
	int nRand = RandomManager->GenerateRandomNumber(0, 4);
	if (nRand > 0)
		this->SpawnItem();
}
