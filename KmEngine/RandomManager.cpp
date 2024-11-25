#include "stdafx.h"
#include "RandomManager.h"

URandomManager::URandomManager()
{
	srand(time(0));

	std::random_device rd{};
	RandomEngine = new std::default_random_engine{};
	RandomEngine->seed(rd());
}

URandomManager::~URandomManager()
{
	SAFE_DELETE(RandomEngine);
}

void URandomManager::Initialize()
{

}

int URandomManager::GenerateRandomNumber(int nStart, int nEnd)
{
	int nDivisor = nEnd - nStart;

	return rand() % nDivisor + nStart;
}