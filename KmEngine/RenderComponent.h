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
	// UActorComponent��(��) ���� ��ӵ�
	void Initialize() override;
	void BeginPlay() override;
	void TickComponent(float fDeltaTime) override;

public:


private:
	// ResourceManager�� ������. Release���� ����
	int m_RenderOrder;
	UImage* m_StaticImage;
};

