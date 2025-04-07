// Fill out your copyright notice in the Description page of Project Settings.


#include "Bats/Bat.h"
#include "Components/BoxComponent.h"

// Sets default values
ABat::ABat()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bat Mesh"));
	SetRootComponent(mesh);

	//HitBoxes and Traces
	SweetSpotBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Sweet Spot Box"));
	SweetSpotBox->SetupAttachment(GetRootComponent());
	SweetSpotBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SweetSpotBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SweetSpotBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	SweetSpotTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Sweet Spot Trace Start"));
	SweetSpotTraceStart->SetupAttachment(GetRootComponent());
	SweetSpotTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Sweet Spot Trace End"));
	SweetSpotTraceEnd->SetupAttachment(GetRootComponent());

	WonkyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Wonky Box"));
	WonkyBox->SetupAttachment(GetRootComponent());
	WonkyBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WonkyBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	WonkyBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	WonkyBoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Wonky Trace Start"));
	WonkyBoxTraceStart->SetupAttachment(GetRootComponent());
	WonkyBoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Wonky Trace End"));
	WonkyBoxTraceEnd->SetupAttachment(GetRootComponent());

	SlowBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Slow Box"));
	SlowBox->SetupAttachment(GetRootComponent());
	SlowBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SlowBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SlowBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	SlowBoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Slow Trace Start"));
	SlowBoxTraceStart->SetupAttachment(GetRootComponent());
	SlowBoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Slow Trace End"));
	SlowBoxTraceEnd->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ABat::BeginPlay()
{
	Super::BeginPlay();
	
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

