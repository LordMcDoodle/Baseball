
#include "Balls/Ball.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/GameplayManager.h"

ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball Mesh"));
	SetRootComponent(mesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Ball Camera"));
	FollowCamera->SetupAttachment(SpringArm);
}

void ABall::BeginPlay()
{
	Super::BeginPlay();
	mesh->OnComponentHit.AddDynamic(this, &ABall::OnComponentHit);
}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABall::OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(GM && !BallAlreadyHitTarget && OtherActor != this)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor's name is %s"), *OtherActor->GetName());
		
		GM->BallHitTarget();
		BallAlreadyHitTarget = true;
	}
}

