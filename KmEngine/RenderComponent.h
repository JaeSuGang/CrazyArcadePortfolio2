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
	// UActorComponent��(��) ���� ��ӵ�
	void Initialize() override;
	void BeginPlay() override;
	void TickComponent(float fDeltaTime) override;

public:
	URenderComponent();

private:
	// ResourceManager�� ������. Release���� ����
	UAnimation* m_CurrentAnimation;
	unordered_map<string, UAnimation*> m_Animations;
	UImage* m_StaticImage;
	int m_RenderOrder;
};

