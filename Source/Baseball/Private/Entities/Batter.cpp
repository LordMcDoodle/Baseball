
#include "Entities/Batter.h"
#include "FieldSystems/BatterFieldSystem.h"
#include "Balls/Ball.h"

ABatter::ABatter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABatter::SwingBat(FVector BatToTargetVector, ABall* ball)
{
	ball->mesh->AddImpulse(BatToTargetVector*(SwingForce*2), NAME_None, true);

	//CreateFields();
}

void ABatter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABatter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABatter::CreateFields()
{
	FVector Location = GetActorLocation() + (GetActorForwardVector() * 20.f);
	ABatterFieldSystem* Fields = GetWorld()->SpawnActor<ABatterFieldSystem>(BatterFieldSystemClass, Location, GetActorRotation());
	Fields->Force = SwingForce;
}



