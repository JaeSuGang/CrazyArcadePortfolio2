#include "stdafx.h"
#include "AIManager.h"
#include "Character.h"
#include "CharacterAIController.h"

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
		
		if (ACharacter* AICharacter = dynamic_cast<ACharacter*>(AIPawn))
		{
			ACharacterAIController* Controller = dynamic_cast<ACharacterAIController*>(AICharacter->GetController());
			AICharacter->Move(Controller->GetDirection());
			float fAccumulatedTime = Controller->GetAccumulatedTime();
			float fChangeDirectionTime = Controller->GetChangeDirectionTime();
			if (fAccumulatedTime > fChangeDirectionTime)
			{
				Controller->SetRandomDirection();
				Controller->SetAccumulatedTime(0.0f);
			}
		}

		++AIPawnIter;
	}
}
