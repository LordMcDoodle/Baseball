// Fill out your copyright notice in the Description page of Project Settings.


#include "Bats/Bat.h"
#include "Components/BoxComponent.h"
#include "Balls/Ball.h"
#include "Entities/Batter.h"
#include <Kismet/KismetSystemLibrary.h>

// Sets default values
ABat::ABat()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bat Mesh"));
	mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = mesh;

	//HitBoxes and Traces
	SweetSpotBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Sweet Spot Box"));
	SweetSpotBox->SetupAttachment(GetRootComponent());
	SweetSpotTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Sweet Spot Trace Start"));
	SweetSpotTraceStart->SetupAttachment(GetRootComponent());
	SweetSpotTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Sweet Spot Trace End"));
	SweetSpotTraceEnd->SetupAttachment(GetRootComponent());

	WonkyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Wonky Box"));
	WonkyBox->SetupAttachment(GetRootComponent());
	WonkyBoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Wonky Trace Start"));
	WonkyBoxTraceStart->SetupAttachment(GetRootComponent());
	WonkyBoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Wonky Trace End"));
	WonkyBoxTraceEnd->SetupAttachment(GetRootComponent());

	SlowBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Slow Box"));
	SlowBox->SetupAttachment(GetRootComponent());
	SlowBoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Slow Trace Start"));
	SlowBoxTraceStart->SetupAttachment(GetRootComponent());
	SlowBoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Slow Trace End"));
	SlowBoxTraceEnd->SetupAttachment(GetRootComponent());

	SweetSpotBox->OnComponentHit.AddDynamic(this, &ABat::OnHit);
	SlowBox->OnComponentHit.AddDynamic(this, &ABat::OnHit);
	WonkyBox->OnComponentHit.AddDynamic(this, &ABat::OnHit);

}

// Called when the game starts or when spawned
void ABat::BeginPlay()
{
	Super::BeginPlay();
}

void ABat::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(ABall* ball = Cast<ABall>(OtherActor))
	{
		if(ABatter* batter = Cast<ABatter>(Owner))
		{
			batter->HitBall(ball);
			ball->BallHasBeenSent = true;
		}
	}
}


// Called every frame
void ABat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABat::Equip(USceneComponent* InParent, FName InSocketName, AActor* NewOwner, APawn* NewInstigator)
{

	SetInstigator(NewInstigator);
	SetOwner(NewOwner);

	AttachMeshToSocket(InParent, InSocketName);
}

void ABat::AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName)
{
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	mesh->AttachToComponent(InParent, TransformRules, InSocketName);
}

