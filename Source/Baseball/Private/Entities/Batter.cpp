
#include "Entities/Batter.h"
#include "FieldSystems/BatterFieldSystem.h"
#include "Animation/AnimMontage.h"
#include "Math/UnrealMathUtility.h"
#include "Bats/Bat.h"
#include "Balls/Ball.h"
#include "Managers/GameplayManager.h"
		

ABatter::ABatter()
{
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Batter mesh"));
	SetRootComponent(mesh);
}

void ABatter::SwingBat()
{
	PlayMontage();
}

void ABatter::MoveBat(FVector MovementVector)
{

}

void ABatter::BeginPlay()
{
	Super::BeginPlay();
	
	AnimInstance = mesh->GetAnimInstance();

	if(bat)
	{
		bat->Equip(mesh, FName("BatSocket"), this, this);
	}
}

void ABatter::HitBall(ABall* ball)
{
	if(TargetToHit)
	{
		FVector TargetVector = TargetToHit->GetActorLocation();
		FVector BatVector = GetActorLocation();

		FVector BatToTargetVector = FVector(TargetVector.X - BatVector.X, TargetVector.Y - BatVector.Y, TargetVector.Z - BatVector.Z);

		ball->mesh->AddImpulse(BatToTargetVector * (SwingForce*0.5f), NAME_None, true);
	}

	if(ball && !ball->BallHasBeenSent)
	{
		GM->BallIsHit(ball);
	}
	
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
}



