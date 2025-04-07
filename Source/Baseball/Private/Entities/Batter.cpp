
#include "Entities/Batter.h"
#include "FieldSystems/BatterFieldSystem.h"
#include "Animation/AnimMontage.h"
#include "Math/UnrealMathUtility.h"
#include "Bats/Bat.h"
#include "Balls/Ball.h"

ABatter::ABatter()
{
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Batter mesh"));
	SetRootComponent(mesh);
}

void ABatter::SwingBat(FVector BatToTargetVector, ABall* ball)
{
	PlayMontage();
	if(ball)
	{
		ball->mesh->AddImpulse(BatToTargetVector*(SwingForce*2), NAME_None, true);
	}
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



