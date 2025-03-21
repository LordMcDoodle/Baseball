
#include "Entities/TargetWidget.h"

ATargetWidget::ATargetWidget()
{
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Target Mesh"));
	SetRootComponent(mesh);
}

void ATargetWidget::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATargetWidget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

