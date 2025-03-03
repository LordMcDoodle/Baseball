
#include "Entities/Batter.h"
#include "FieldSystems/BatterFieldSystem.h"

ABatter::ABatter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABatter::SwingBat()
{
	CreateFields();
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
	GetWorld()->SpawnActor<ABatterFieldSystem>(BatterFieldSystemClass, Location, GetActorRotation());
}



