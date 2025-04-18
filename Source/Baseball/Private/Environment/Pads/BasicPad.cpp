
#include "Environment/Pads/BasicPad.h"

ABasicPad::ABasicPad()
{
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pad Mesh"));
}

void ABasicPad::BeginPlay()
{
	Super::BeginPlay();

}

void ABasicPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

