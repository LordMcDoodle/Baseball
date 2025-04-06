
#include "Entities/Batter.h"
#include "FieldSystems/BatterFieldSystem.h"
#include "Animation/AnimMontage.h"
#include "Math/UnrealMathUtility.h"
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
	if(ball)
	{
		ball->mesh->AddImpulse(BatToTargetVector*(SwingForce*2), NAME_None, true);
	}
}

void ABatter::MoveBat(FVector MovementVector)
{
	FVector NewLocation = GetActorLocation() + MovementVector;
	
	//Limiting the batter to it's boundaries
	NewLocation.Y = FMath::Clamp(NewLocation.Y, LocationYMin, LocationYMax);
	NewLocation.Z = FMath::Clamp(NewLocation.Z, LocationZMin, LocationZMax);

	SetActorLocation(NewLocation);
}

void ABatter::BeginPlay()
{
	Super::BeginPlay();
	
	AnimInstance = mesh->GetAnimInstance();

	//Setting Location Boundaries
	LocationYMax = GetActorLocation().Y + 700.f;
	LocationYMin = GetActorLocation().Y - 700.f;
	LocationZMax = GetActorLocation().Z + 500.f;
	LocationZMin = GetActorLocation().Z - 50.f;
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



