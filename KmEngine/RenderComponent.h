#pragma once
#include "stdafx.h"
#include "ActorComponent.h"

class UImage;

enum class ERenderType : unsigned short
{
	Tile,
	ShadowObject,
	NonShadowObject,
	UI
};

class FImageDataset
{
public:
	UImage* StaticImage;
	UImage* ShadowImage;
	FVector2D StaticImageOffset;
	FVector2D ShadowImageOffset;
};

class UAnimation
{
public:
	void Initialize();

public:
	vector<UImage*> m_Images;
	float m_fFrameDuration;
	float m_fStartDelay;
	bool m_bIsLoop;
};

class URenderComponent : public UActorComponent
{
	typedef UActorComponent Super;

public:
	enum class ERenderType : unsigned short
	{
		FloorTile,
		ShadowObject,
		NonShadowObject,
		UI
	};

public:
	ERenderType GetRenderType() const;
	void SetRenderType(ERenderType RenderType);
	void SetRenderPriority(float fPriority);
	float GetRenderPriority();
	void SetImageDataset(FImageDataset ImageDataset);
	void SetStaticImageOffset(FVector2D OffsetVector);
	void SetShadowImageOffset(FVector2D OffsetVector);
	void PlayAnimation(string strKey);
	void PlayAnimation();
	void CreateAnimation(string strAnimationKey, string strImageBaseKey, int nFileCount, float fDuration, bool bIsLoop);
	void CreateAnimation(string strAnimationKey, string strImageBaseKey, int nFileCount, float fDuration, float fStartDelay, bool bIsLoop);
	void SetStaticImage(UImage* Image);
	void SetStaticImage(string strKey);
	void SetShadowImage(UImage* Image);
	void SetShadowImage(string strKey);
	bool GetIsHidden() const;
	void SetIsHidden(bool bValue);
	FVector2D GetStaticImageOffset() const;
	FVector2D GetShadowImageOffset() const;
	UImage* GetStaticImage() const;
	UImage* GetShadowImage() const;

public:
	void BeginPlay() override;
	void TickComponent(float fDeltaTime) override;

public:
	void Release();
	~URenderComponent();
	URenderComponent();
	float m_fRenderPriority;

public:
	unordered_map<string, UAnimation*> m_Animations;

protected:
	// ResourceManager가 삭제함. Release하지 말것
	UAnimation* m_CurrentAnimation;
	ERenderType m_RenderType;
	FImageDataset m_ImageDataset;
	float m_fAccumulatedTime;
	int m_nAnimationFrameIndex;
	bool m_bIsHidden;
};

