
#include "Managers/GameplayManager.h"
#include "Entities/Batter.h"
#include "Entities/Thrower.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "HUD/ThrowForceBar.h"

AGameplayManager::AGameplayManager()
{
	PrimaryActorTick.bCanEverTick = true;

	ThrowForceBar = CreateDefaultSubobject<UThrowForceBar>(TEXT("Throw Force Bar"));
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
}

void AGameplayManager::MoveBat(const FInputActionValue& Value)
{
}

void AGameplayManager::ThrowBall(const FInputActionValue& Value)
{
	if(thrower)
	{
		thrower->ThrowBall();
	}
}

void AGameplayManager::SwingBat(const FInputActionValue& Value)
{
	if(batter)
	{
		batter->SwingBat();
	}
}

void AGameplayManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveBatAction, ETriggerEvent::Triggered, this, &AGameplayManager::MoveBat);
		EnhancedInputComponent->BindAction(SwingBatAction, ETriggerEvent::Triggered, this, &AGameplayManager::SwingBat);
		EnhancedInputComponent->BindAction(ThrowBallAction, ETriggerEvent::Triggered, this, &AGameplayManager::ThrowBall);
	}
}

