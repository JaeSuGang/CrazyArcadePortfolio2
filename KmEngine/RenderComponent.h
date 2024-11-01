#pragma once
#include "stdafx.h"
#include "ActorComponent.h"

class UImage;

class UAnimation
{

};

class URenderComponent : public UActorComponent
{
	typedef UActorComponent Super;

public:
	void PlayAnimation(string strKey);
	// void CreateAnimation(string strAnimationKey, string strImageKey, );
	void SetStaticImage(UImage* Image);
	void SetStaticImage(string strKey);
	UImage* GetStaticImage();

public:
	// UActorComponent을(를) 통해 상속됨
	void Initialize() override;
	void BeginPlay() override;
	void TickComponent(float fDeltaTime) override;

public:
	URenderComponent();

private:
	// ResourceManager가 삭제함. Release하지 말것
	UAnimation* m_CurrentAnimation;
	unordered_map<string, UAnimation*> m_Animations;
	UImage* m_StaticImage;
	int m_RenderOrder;
};

