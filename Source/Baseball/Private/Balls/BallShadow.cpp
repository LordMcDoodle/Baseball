
#include "Balls/BallShadow.h"

ABallShadow::ABallShadow()
{
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shadow Mesh"));
	SetRootComponent(mesh);
}

void ABallShadow::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABallShadow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

