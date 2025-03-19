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

UCLASS()
class BASEBALL_API AGameplayManager : public APawn
{
	GENERATED_BODY()
	
public:

	AGameplayManager();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//Entities
	UPROPERTY(EditAnywhere, Category = Entities)
	ABatter* batter;
	UPROPERTY(EditAnywhere, Category = Entities)
	AThrower* thrower;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = HUD)
	UHUDWidget* HUDWidget;


	//Input Callbacks
	void MoveBat(const FInputActionValue& Value);
	void ThrowBall(const FInputActionValue& Value);
	void SwingBat(const FInputActionValue& Value);
	void DetermineThrowForce(const FInputActionValue& Value);
	void DetermineSwingForce(const FInputActionValue& Value);

protected:
	virtual void BeginPlay() override;

	//Bools
	bool bIsCalculatingThrowForce = false;
	bool bIsCalculatingSwingForce = false;

	//Properties

	//These time properties are used to change the ThrowForceBar and SwingForceBar
	float ThrowForceBarRunningTime = 0.f;
	float SwingForceBarRunningTime = 0.f;
};
