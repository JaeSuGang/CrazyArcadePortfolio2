#pragma once
#include "stdafx.h"
#include "ActorComponent.h"

class UImage;

class UAnimation
{
public:
	void Initialize();

public:
	vector<UImage*> m_Images;
	float m_fFrameDuration;
	bool m_bIsLoop;
};

class URenderComponent : public UActorComponent
{
	typedef UActorComponent Super;

public:
	void SetRenderPriority(int nPriority);
	int GetRenderPriority();
	void SetOffset(FVector2D OffsetVector);
	FVector2D GetOffset();
	void PlayAnimation(string strKey);
	void CreateAnimation(string strAnimationKey, string strImageBaseKey, int nFileCount, float fDuration, bool bIsLoop);
	void SetStaticImage(UImage* Image);
	void SetStaticImage(string strKey);
	UImage* GetStaticImage();

public:
	void BeginPlay() override;
	void TickComponent(float fDeltaTime) override;

public:
	void Release();
	~URenderComponent();
	URenderComponent();
	float m_fRenderPriority;

protected:
	// ResourceManager가 삭제함. Release하지 말것
	UAnimation* m_CurrentAnimation;
	unordered_map<string, UAnimation*> m_Animations;
	UImage* m_StaticImage;
	FVector2D m_ImageOffset;
	float m_fAccumulatedTime;
	int m_nAnimationFrameIndex;
};

