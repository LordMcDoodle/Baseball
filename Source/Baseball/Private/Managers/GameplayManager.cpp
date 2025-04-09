
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
	HitCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Hit Camera"));

}

void AGameplayManager::BeginPlay()
{
	Super::BeginPlay(); 


	if(Ball)
	{
		Ball->SetGameplayManager(this);
	}
	if(batter)
	{
		batter->SetGameplayManager(this);
	}
	if(thrower)
	{
		thrower->SetGameplayManager(this);
	}

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
	GetWorldTimerManager().SetTimer(SlowmoTimer, this, &AGameplayManager::ResetWorldTimeDilation, 0.004f);
}

void AGameplayManager::ResetWorldTimeDilation()
{
	GetWorldSettings()->SetTimeDilation(1.f);
	GetWorldTimerManager().ClearTimer(SlowmoTimer);
}

void AGameplayManager::ResetToBaseCamera()
{
	HitCamera->SetActive(false);
	BaseCamera->SetActive(true);
}

void AGameplayManager::FollowBall(bool active, ABall* ball)
{
	if(active)
	{
		PlayerController->SetViewTarget(ball);
	}
	else
	{
		PlayerController->SetViewTarget(this);
	}
}

void AGameplayManager::BallIsHit(ABall* ball)
{
	UE_LOG(LogTemp, Warning, TEXT("HIT"));
	SlowmoFrame();
	FollowBall(true,ball);
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
	if(bTargetIsLocked)
	{
		FVector2D MovementVector = Value.Get<FVector2D>();
		FVector MovementVector3D = FVector(0,MovementVector.X*5, MovementVector.Y*5);

		batter->MoveBat(MovementVector3D);
	}
}

void AGameplayManager::ThrowBall(const FInputActionValue& Value)
{
	thrower->Pitch();
}

void AGameplayManager::SwingBat(const FInputActionValue& Value)
{
	batter->SwingBat();
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
	batter->TargetToHit = TargetWidget;
}

void AGameplayManager::ResetTarget(const FInputActionValue&)
{
	bTargetIsLocked = false;
	batter->TargetToHit = nullptr;
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
		EnhancedInputComponent->BindAction(ResetTargetAction, ETriggerEvent::Triggered, this, &AGameplayManager::ResetTarget);
		
	}
}

void AGameplayManager::BallHitTarget()
{
	SlowmoFrame();
	FollowBall(false);
	HitCamera->SetRelativeTransform(Ball->FollowCamera->GetComponentTransform());
	BaseCamera->SetActive(false);
	HitCamera->SetActive(true);
	GetWorldTimerManager().SetTimer(HitCameraTimer, this, &AGameplayManager::ResetToBaseCamera, 2.f);
}

