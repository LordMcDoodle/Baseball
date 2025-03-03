
#include "Entities/Thrower.h"
#include "Balls/Ball.h"
#include "FieldSystems/ThrowerFieldSystem.h"

AThrower::AThrower()
{
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Thrower Mesh"));
	SetRootComponent(mesh);
}

void AThrower::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(ThrowTimer,this,&AThrower::ThrowBall,10.f);
}


void AThrower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AThrower::ThrowBall()
{
	FVector Location = GetActorLocation() + (GetActorForwardVector() * 50.f);
	GetWorld()->SpawnActor<ABall>(BallClass, Location, GetActorRotation());

	CreateField();
}

void AThrower::CreateField()
{
	FVector Location = GetActorLocation() + (GetActorForwardVector() * 20.f);
	GetWorld()->SpawnActor<AThrowerFieldSystem>(ThrowerFieldSystemClass, Location, GetActorRotation());
}



