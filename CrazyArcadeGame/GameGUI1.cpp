#include "stdafx.h"
#include "GameGUI1.h"
#include "KmEngine/RenderComponent.h"

void AGameGUI1::Initialize()
{
	Super::Initialize();

	URenderComponent* RenderComponent = InitializeComponentForPlay<URenderComponent>();
	RenderComponent->SetStaticImage("Resources\\GUI\\InGameScreenEdge.bmp");
	m_Position = FVector2D(300.0f, 300.0f);
}

void AGameGUI1::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);


}

void AGameGUI1::LateTick(float fDeltaTime)
{
	Super::LateTick(fDeltaTime);


}

void AGameGUI1::BeginPlay()
{
	Super::BeginPlay();

}
