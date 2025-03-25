// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InputActionValue.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameplayManager.generated.h"

class AThrower;
class ABatter;
class UInputMappingContext;
class UInputAction;
class USceneComponent;
class UHUDWidget;
class APlayerController;
class ATargetWidget;
class ABall;
class UCameraComponent;

UCLASS()
class BASEBALL_API AGameplayManager : public APawn
{
	GENERATED_BODY()
	
public:

	AGameplayManager();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BallHitTarget();


	//Entities
	UPROPERTY(EditAnywhere, Category = Entities)
	ABatter* batter;
	UPROPERTY(EditAnywhere, Category = Entities)
	AThrower* thrower;
	UPROPERTY(EditAnywhere, Category = Entities)
	ATargetWidget* TargetWidget;
	UPROPERTY()
	ABall* Ball = nullptr;

	//Input Mapping Contexts
	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputMappingContext* GameplayMappingContext;
	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* MoveBatAction;
	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* SwingBatAction;
	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* ThrowBallAction;
	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* DetermineThrowForceAction;
	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* DetermineSwingForceAction;
	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* AimAction;
	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* ConfirmTargetAction;

	//Components
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = HUD)
	UHUDWidget* HUDWidget;
	UPROPERTY(EditAnywhere, Category = Cameras)
	UCameraComponent* BaseCamera;



	//Input Callbacks
	void MoveBat(const FInputActionValue& Value);
	void ThrowBall(const FInputActionValue& Value);
	void SwingBat(const FInputActionValue& Value);
	void DetermineThrowForce(const FInputActionValue& Value);
	void DetermineSwingForce(const FInputActionValue& Value);
	void TakeAim(const FInputActionValue&);
	void ConfirmTarget(const FInputActionValue&);

	FVector BatToTargetVector = FVector::Zero();

protected:
	//Functions
	virtual void BeginPlay() override;
	virtual void SlowmoFrame();
	virtual void ResetWorldTimeDilation();
	virtual void FollowBall(bool active);

	//Bools
	bool bIsCalculatingThrowForce = false;
	bool bIsCalculatingSwingForce = false;
	bool bTargetIsLocked = false;

	//Properties
	APlayerController* PlayerController;
	FTimerHandle SlowmoTimer;

	//These time properties are used to change the ThrowForceBar and SwingForceBar
	float ThrowForceBarRunningTime = 0.f;
	float SwingForceBarRunningTime = 0.f;

};
