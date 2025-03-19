
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
	ABall* Ball = GetWorld()->SpawnActor<ABall>(BallClass, Location, GetActorRotation());

	Ball->mesh->AddImpulse(FVector(-(ThrowForce*1000),0,0),NAME_None,true);

	//CreateField();
}

void AThrower::CreateField()
{
	FVector Location = GetActorLocation() + (GetActorForwardVector() * 20.f);
	AThrowerFieldSystem* Field = GetWorld()->SpawnActorDeferred<AThrowerFieldSystem>(AThrowerFieldSystem::StaticClass(), GetTransform());
	Field->Force = ThrowForce;
	Field->FinishSpawning(GetTransform());

	Field->CreateForce();
}



