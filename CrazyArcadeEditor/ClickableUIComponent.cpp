#include "stdafx.h"
#include "ClickableUIComponent.h"

void UClickableUIComponent::SetClickableUIType(EClickableUIType ClickableUIType)
{
	m_ClickableUIType = ClickableUIType;
}

UClickableUIComponent::EClickableUIType UClickableUIComponent::GetClickableUIType()
{
	return m_ClickableUIType;
}

int UClickableUIComponent::GetValue()
{
	return m_nValue;
}

void UClickableUIComponent::SetValue(int nValue)
{
	m_nValue = nValue;
}

void UClickableUIComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UClickableUIComponent::TickComponent(float fDeltaTime)
{
	Super::TickComponent(fDeltaTime);
}

UClickableUIComponent::UClickableUIComponent()
	:
	m_ClickableUIType{},
	m_nValue{}
{

}
