#include "stdafx.h"
#include "Engine.h"
#include "RenderComponent.h"
#include "ResourceManager.h"

void URenderComponent::PlayAnimation(string strKey)
{

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

void URenderComponent::Initialize()
{
	Super::Initialize();


}

void URenderComponent::BeginPlay()
{
	Super::BeginPlay();


}

void URenderComponent::TickComponent(float fDeltaTime)
{
	Super::TickComponent(fDeltaTime);


}

URenderComponent::URenderComponent()
	:
	m_RenderOrder{},
	m_StaticImage{}
{
}
