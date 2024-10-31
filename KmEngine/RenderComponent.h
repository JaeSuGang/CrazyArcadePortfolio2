#pragma once
#include "ActorComponent.h"

class UImage;

class URenderComponent : public UActorComponent
{
	typedef UActorComponent Super;

public:
	void SetStaticImage(UImage* Image);
	void SetStaticImage(string strKey);
	UImage* GetStaticImage();

public:
	// UActorComponent을(를) 통해 상속됨
	void Initialize() override;
	void BeginPlay() override;
	void TickComponent(float fDeltaTime) override;

public:


private:
	// ResourceManager가 삭제함. Release하지 말것
	int m_RenderOrder;
	UImage* m_StaticImage;
};

