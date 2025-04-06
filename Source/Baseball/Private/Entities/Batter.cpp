
#include "Entities/Batter.h"
#include "FieldSystems/BatterFieldSystem.h"
#include "Animation/AnimMontage.h"
#include "Balls/Ball.h"

ABatter::ABatter()
{
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Bat mesh"));
	SetRootComponent(mesh);
}

void ABatter::SwingBat(FVector BatToTargetVector, ABall* ball)
{
	PlayMontage();
	ball->mesh->AddImpulse(BatToTargetVector*(SwingForce*2), NAME_None, true);

	//CreateFields();
}

void ABatter::BeginPlay()
{
	Super::BeginPlay();
	
	AnimInstance = mesh->GetAnimInstance();
}

void ABatter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABatter::PlayMontage()
{
	if(AnimInstance && Montage)
	{
		AnimInstance->Montage_Play(Montage);
		AnimInstance->Montage_JumpToSection(FName("Swing"), Montage);
	}

	UE_LOG(LogExec, Warning, TEXT("PlayMontage() was called."));
}

void ABatter::CreateFields()
{
	FVector Location = GetActorLocation() + (GetActorForwardVector() * 20.f);
	ABatterFieldSystem* Fields = GetWorld()->SpawnActor<ABatterFieldSystem>(BatterFieldSystemClass, Location, GetActorRotation());
	Fields->Force = SwingForce;
}



