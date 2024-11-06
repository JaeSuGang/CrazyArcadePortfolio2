#include "stdafx.h"
#include "Engine.h"
#include "RenderManager.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "TimeManager.h"

void URenderComponent::SetRenderPriority(float fPriority)
{
	m_fRenderPriority = fPriority;
}

float URenderComponent::GetRenderPriority()
{
	return m_fRenderPriority;
}

void URenderComponent::SetStaticImageOffset(FVector2D OffsetVector)
{
	m_StaticImageOffset = OffsetVector;
}

FVector2D URenderComponent::GetStaticImageOffset()
{
	return m_StaticImageOffset;
}

void URenderComponent::SetShadowImageOffset(FVector2D OffsetVector)
{
	m_ShadowImageOffset = OffsetVector;
}

FVector2D URenderComponent::GetShadowImageOffset()
{
	return m_ShadowImageOffset;
}

void URenderComponent::PlayAnimation(string strKey)
{
	LOWER_STRING(strKey);

	auto AnimationIter = m_Animations.find(strKey);

	if (AnimationIter == m_Animations.end())
	{
		SHOW_ERROR(("URenderComponent::PlayAnimation, 존재하지 않는 Key입니다, " + strKey).data());
	}

	UAnimation* Animation = AnimationIter->second;

	if (m_CurrentAnimation != Animation)
	{
		m_CurrentAnimation = Animation;
		m_nAnimationFrameIndex = 0;
		m_fAccumulatedTime = 0.0f;
	}

	m_StaticImage = m_CurrentAnimation->m_Images[m_nAnimationFrameIndex];
	m_fAccumulatedTime += GEngine->GetEngineSubsystem<UTimeManager>()->GetDeltaTime();
	if (m_fAccumulatedTime > m_CurrentAnimation->m_fFrameDuration)
	{
		if (m_nAnimationFrameIndex < m_CurrentAnimation->m_Images.size() - 1)
		{
			m_nAnimationFrameIndex++;
		}
		else
		{
			m_nAnimationFrameIndex = 0;
		}
		m_fAccumulatedTime = 0.0f;
	}
}

void URenderComponent::CreateAnimation(string strAnimationKey, string strImageBaseKey, int nFileCount, float fDuration, bool bIsLoop = true)
{
	LOWER_STRING(strAnimationKey);
	LOWER_STRING(strImageBaseKey);

	UAnimation* NewAnimation = new UAnimation{};
	NewAnimation->m_bIsLoop = bIsLoop;
	NewAnimation->m_fFrameDuration = fDuration;
	for (int i = 0; i < nFileCount; i++)
	{
		UResourceManager* ResourceManager = GEngine->GetEngineSubsystem<UResourceManager>();
		string path = strImageBaseKey + "_" + std::to_string(i) + ".bmp";
		UImage* OneImage = ResourceManager->GetImage(path);
		NewAnimation->m_Images.push_back(OneImage);
	}

	m_Animations.insert({ strAnimationKey, NewAnimation });
}

void URenderComponent::SetStaticImage(UImage* Image)
{
	m_StaticImage = Image;
}

void URenderComponent::SetStaticImage(string strKey)
{
	m_StaticImage = GEngine->GetEngineSubsystem<UResourceManager>()->GetImage(strKey);
}

UImage* URenderComponent::GetStaticImage()
{
	return m_StaticImage;
}

void URenderComponent::SetShadowImage(UImage* Image)
{
	m_ShadowImage = Image;
}

void URenderComponent::SetShadowImage(string strKey)
{
	m_ShadowImage = GEngine->GetEngineSubsystem<UResourceManager>()->GetImage(strKey);
}

UImage* URenderComponent::GetShadowImage()
{
	return m_ShadowImage;
}

void URenderComponent::BeginPlay()
{
	Super::BeginPlay();

	URenderManager* RenderManager = GEngine->GetEngineSubsystem<URenderManager>();
	RenderManager->AddRender(this);
}

void URenderComponent::TickComponent(float fDeltaTime)
{
	Super::TickComponent(fDeltaTime);
	
}

void URenderComponent::Release()
{
	auto AnimationIter = m_Animations.begin();
	while (AnimationIter != m_Animations.end())
	{
		SAFE_DELETE((AnimationIter->second));
		++AnimationIter;
	}

	URenderManager* RenderManager = GEngine->GetEngineSubsystem<URenderManager>();
	RenderManager->RemoveRender(this);
}

URenderComponent::~URenderComponent()
{
	this->Release();
}

URenderComponent::URenderComponent()
	:
	m_fRenderPriority{},
	m_StaticImage{},
	m_ShadowImage{},
	m_nAnimationFrameIndex{},
	m_CurrentAnimation{},
	m_fAccumulatedTime{},
	m_StaticImageOffset{},
	m_ShadowImageOffset{}
{
}

void UAnimation::Initialize()
{
	m_Images.reserve(50);
}
