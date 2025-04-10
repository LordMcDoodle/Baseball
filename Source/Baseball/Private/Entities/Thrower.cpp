
#include "Entities/Thrower.h"
#include "Balls/Ball.h"
#include "FieldSystems/ThrowerFieldSystem.h"
#include "Balls/Ball.h"
#include "Managers/GameplayManager.h"

AThrower::AThrower()
{
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Thrower Mesh"));
	SetRootComponent(mesh);
}

void AThrower::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance = mesh->GetAnimInstance();

	if (BallInHand)
	{
		BallInHand->Equip(mesh, FName("BallSocket"), this);
	}
}


void AThrower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AThrower::PlayMontage()
{
	if (AnimInstance && Montage)
	{
		AnimInstance->Montage_Play(Montage);
		AnimInstance->Montage_JumpToSection(FName("Throw"), Montage);
	}
}

void AThrower::Pitch()
{
	PlayMontage();
}

void AThrower::ThrowBall()
{

	BallInHand->Unequip();
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AThrower::ApplyImpulse, 0.01f, false);

	//UE_LOG(LogTemp, Warning, TEXT("Ball Location is : %s"), *BallInHand->GetActorLocation().ToString());

}

void AThrower::SpawnNewBall()
{
	BallInHand = GetWorld()->SpawnActor<ABall>(BallClass, GetActorLocation(), GetActorRotation());
	BallInHand->Equip(mesh, FName("BallSocket"), this);
}

void AThrower::ApplyImpulse()
{
	if (ThrowTarget)
	{
		FVector TargetVector = ThrowTarget->GetActorLocation();
		FVector BallVector = BallInHand->mesh->GetComponentLocation();

		FVector BallToTargetVector = FVector(TargetVector.X - BallVector.X, TargetVector.Y - BallVector.Y, TargetVector.Z - BallVector.Z);

		//BallToTargetVector = FVector(BallToTargetVector.X * (ThrowForce * 3.f), BallToTargetVector.Y, BallToTargetVector.Z);

		BallInHand->mesh->SetEnableGravity(false);
		BallInHand->mesh->SetSimulatePhysics(true);
		BallInHand->mesh->AddVelocityChangeImpulseAtLocation(BallToTargetVector * (ThrowForce * 3.0f), BallInHand->GetActorLocation());
		//BallInHand->mesh->AddImpulse(BallToTargetVector*ThrowForce*3.f, NAME_None, true);
		//BallInHand->mesh->AddImpulseAtLocation(BallToTargetVector * ThrowForce * 3.f, BallVector, NAME_None);

		UE_LOG(LogTemp, Warning, TEXT("BallToTargetVector is : %s"), *BallToTargetVector.ToString());
	}

	SpawnNewBall();

}



