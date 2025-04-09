
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
	BallInHand->mesh->SetSimulatePhysics(true);

	if(ThrowTarget)
	{
		FVector TargetVector = ThrowTarget->GetActorLocation();
		FVector BallVector = BallInHand->GetActorLocation();

		FVector BallToTargetVector = FVector(TargetVector.X - BallVector.X, TargetVector.Y - BallVector.Y, TargetVector.Z - BallVector.Z);

		BallInHand->mesh->AddImpulse(BallToTargetVector * (ThrowForce * 3.0f), NAME_None, true);
	}

}



