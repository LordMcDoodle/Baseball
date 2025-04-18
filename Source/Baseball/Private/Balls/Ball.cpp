
#include "Balls/Ball.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Managers/GameplayManager.h"
#include "Bats/Bat.h"
#include "Balls/BallShadow.h"

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

	CreateShadow();
}

void ABall::CreateShadow()
{
	Shadow = GetWorld()->SpawnActor<ABallShadow>(ShadowClass, GetActorLocation(), FRotator::ZeroRotator);
}

void ABall::UpdateShadowLocation()
{
	if(Shadow)
	{
		FHitResult Hit;

		FVector Start = GetActorLocation();
		FVector End = FVector(Start.X, Start.Y, Start.Z - 1000.f);

		FCollisionQueryParams CollisionParams;

		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(this);

		UKismetSystemLibrary::LineTraceSingle(GetWorld(),Start, End, ETraceTypeQuery::TraceTypeQuery1,true,ActorsToIgnore, EDrawDebugTrace::None,Hit,true);

		FVector NewLocation = FVector(Hit.Location.X,Hit.Location.Y,Hit.Location.Z);

		Shadow->SetActorLocation(NewLocation);
	}
	
}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateShadowLocation();

}

void ABall::OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit by %s"), *OtherActor->GetName());

	if(GM && !BallAlreadyHitTarget && BallHasBeenSent)
	{

		if (Cast<ABat>(OtherActor)) return;

		GM->BallHitTarget();
		BallAlreadyHitTarget = true;
	}
}

void ABall::Equip(USceneComponent* InParent, FName InSocketName, AActor* NewOwner)
{
	SetOwner(NewOwner);

	AttachMeshToSocket(InParent, InSocketName);
}

void ABall::Unequip()
{
	SetOwner(nullptr);

	DetachMeshFromSocket();
}

void ABall::AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName)
{
	mesh->SetSimulatePhysics(false);
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	mesh->AttachToComponent(InParent, TransformRules, InSocketName);

}

void ABall::DetachMeshFromSocket()
{
	FDetachmentTransformRules TransformRules(FDetachmentTransformRules::KeepWorldTransform);
	mesh->DetachFromComponent(TransformRules);
}

