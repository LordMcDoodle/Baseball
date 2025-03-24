
#include "Managers/GameplayManager.h"
#include "Entities/Batter.h"
#include "Entities/Thrower.h"
#include "Entities/TargetWidget.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameMode.h"
#include "HUD/HUDWidget.h"
#include "HUD/ThrowForceBar.h"
#include "Balls/Ball.h"
#include "Camera/CameraComponent.h"

AGameplayManager::AGameplayManager()
{
	PrimaryActorTick.bCanEverTick = true;

	//HUDWidget = CreateDefaultSubobject<UHUDWidget>(TEXT("HUD Widget"));

	UWorld* TheWorld = GetWorld();

	BaseCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Base Camera"));
}

void AGameplayManager::BeginPlay()
{
	Super::BeginPlay(); 
	BaseCamera->SetActive(true);
	PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(GameplayMappingContext, 0);
		}
	}
}

void AGameplayManager::SlowmoFrame()
{
	GetWorldSettings()->SetTimeDilation(0.01f);
	GetWorldTimerManager().SetTimer(SlowmoTimer, this, &AGameplayManager::ResetWorldTimeDilation, 0.003f);
}

void AGameplayManager::ResetWorldTimeDilation()
{
	GetWorldSettings()->SetTimeDilation(1.f);
}

void AGameplayManager::FollowBall(bool active)
{
	if(active)
	{
		PlayerController->SetViewTarget(Ball);
	}
	else
	{
		PlayerController->SetViewTarget(this);
	}
}

void AGameplayManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsCalculatingThrowForce)
	{
		ThrowForceBarRunningTime += DeltaTime;
		float throwForce = FMath::Sin(ThrowForceBarRunningTime);
		throwForce = FMath::Clamp(throwForce, 0, 100);

		HUDWidget->SetThrowBarProgress(throwForce);
	}

	if (bIsCalculatingSwingForce)
	{
		SwingForceBarRunningTime += DeltaTime;
		float swingForce = FMath::Sin(SwingForceBarRunningTime);
		swingForce = FMath::Clamp(swingForce, 0, 100);

		HUDWidget->SetSwingBarProgress(swingForce);
	}
}

void AGameplayManager::MoveBat(const FInputActionValue& Value)
{
}

void AGameplayManager::ThrowBall(const FInputActionValue& Value)
{
	Ball = thrower->ThrowBall();
}

void AGameplayManager::SwingBat(const FInputActionValue& Value)
{
	if(Ball)
	{
		batter->SwingBat(BatToTargetVector, Ball);
		SlowmoFrame();
		//GetWorldTimerManager().ClearTimer(SlowmoTimer);
		FollowBall(true);
	}
}

void AGameplayManager::DetermineThrowForce(const FInputActionValue& Value)
{
	if (bIsCalculatingThrowForce)
	{
		thrower->ThrowForce = HUDWidget->GetThrowBarProgress();
	}

	ThrowForceBarRunningTime = 0.f;
	bIsCalculatingThrowForce = !bIsCalculatingThrowForce;

}

void AGameplayManager::DetermineSwingForce(const FInputActionValue& Value)
{
	if (bIsCalculatingSwingForce)
	{
		batter->SwingForce = HUDWidget->GetSwingBarProgress();
	}

	SwingForceBarRunningTime = 0.f;
	bIsCalculatingSwingForce = !bIsCalculatingSwingForce;

}

void AGameplayManager::TakeAim(const FInputActionValue&)
{
	if(!bTargetIsLocked)
	{
		FHitResult Hit;
		PlayerController->GetHitResultUnderCursor(ECC_WorldStatic, true, Hit);

		if (TargetWidget)
		{
			TargetWidget->SetActorLocation(Hit.Location);
		}

	}
}

void AGameplayManager::ConfirmTarget(const FInputActionValue&)
{
	bTargetIsLocked = true;

	FVector TargetVector = TargetWidget->GetActorLocation();
	FVector BatVector = batter->GetActorLocation();

	BatToTargetVector = FVector(TargetVector.X - BatVector.X, TargetVector.Y - BatVector.Y, TargetVector.Z - BatVector.Z);
}

void AGameplayManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveBatAction, ETriggerEvent::Triggered, this, &AGameplayManager::MoveBat);
		EnhancedInputComponent->BindAction(SwingBatAction, ETriggerEvent::Triggered, this, &AGameplayManager::SwingBat);
		EnhancedInputComponent->BindAction(ThrowBallAction, ETriggerEvent::Triggered, this, &AGameplayManager::ThrowBall);
		EnhancedInputComponent->BindAction(DetermineThrowForceAction, ETriggerEvent::Triggered, this, &AGameplayManager::DetermineThrowForce);
		EnhancedInputComponent->BindAction(DetermineSwingForceAction, ETriggerEvent::Triggered, this, &AGameplayManager::DetermineSwingForce);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Triggered, this, &AGameplayManager::TakeAim);
		EnhancedInputComponent->BindAction(ConfirmTargetAction, ETriggerEvent::Triggered, this, &AGameplayManager::ConfirmTarget);
		
	}
}

