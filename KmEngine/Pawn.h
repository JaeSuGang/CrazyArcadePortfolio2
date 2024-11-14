#pragma once
#include "Actor.h"

class AController;

class APawn : public AActor
{
	typedef AActor Super;

public:
	AController* GetController();
	void SetController(AController* Controller);
	virtual void OnPlayerPossessed();
	virtual void OnPlayerUnpossessed();
	virtual void OnAIPossessed();
	virtual void OnAIUnpossessed();

public:
	void Tick(float fDeltaTime) override;
	void LateTick(float fDeltaTime) override;
	void BeginPlay() override;

public:
	void Release();
	~APawn();

protected:
	AController* m_Controller;
};

