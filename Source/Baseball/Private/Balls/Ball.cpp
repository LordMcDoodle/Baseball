
#include "Balls/Ball.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball Mesh"));
	SetRootComponent(mesh);
	capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Ball Capsule"));
	capsule->SetupAttachment(GetRootComponent());

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
	
}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

