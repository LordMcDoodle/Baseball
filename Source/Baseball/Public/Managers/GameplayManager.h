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
class UThrowForceBar;

UCLASS()
class BASEBALL_API AGameplayManager : public APawn
{
	GENERATED_BODY()
	
public:

	AGameplayManager();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//HUD
	UThrowForceBar* ThrowForceBar;

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


	//Input Callbacks
	void MoveBat(const FInputActionValue& Value);
	void ThrowBall(const FInputActionValue& Value);
	void SwingBat(const FInputActionValue& Value);

protected:
	virtual void BeginPlay() override;

	//Functions
	float DetermineForce(float minForce, float maxForce);


};
