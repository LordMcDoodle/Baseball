
#include "Balls/Ball.h"
#include "Components/CapsuleComponent.h"
ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball Mesh"));
	SetRootComponent(mesh);
	capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Ball Capsule"));
	capsule->SetupAttachment(GetRootComponent());

}

void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

