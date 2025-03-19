
#include "Managers/GameplayManager.h"
#include "Entities/Batter.h"
#include "Entities/Thrower.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameMode.h"
#include "HUD/HUDWidget.h"
#include "HUD/ThrowForceBar.h"


AGameplayManager::AGameplayManager()
{
	PrimaryActorTick.bCanEverTick = true;

	//HUDWidget = CreateDefaultSubobject<UHUDWidget>(TEXT("HUD Widget"));

	UWorld* TheWorld = GetWorld();
}

void AGameplayManager::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(GameplayMappingContext, 0);
		}
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
	thrower->ThrowBall();
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
	}
}

