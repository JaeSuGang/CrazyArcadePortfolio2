#pragma once
#include "stdafx.h"
#include "EngineSubsystem.h"

class URandomManager : public UEngineSubsystem
{
public:
	// Consturctors and Overrides
	URandomManager();
	~URandomManager();

	void Initialize();

	int GenerateRandomNumber(int nStart, int nEnd);

	template <typename T>
	//typedef vector<int> T;
	void ShuffleVector(T& Vector)
	{
		std::shuffle(Vector.begin(), Vector.end(), *RandomEngine);
	}

public:
	std::default_random_engine* RandomEngine;
	std::random_device RandomDevice;
};

