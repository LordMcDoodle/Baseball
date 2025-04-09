// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/ThrowerAnimInstance.h"
#include "Entities/Thrower.h"

void UThrowerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Thrower = Cast<AThrower>(GetOwningActor());
}

void UThrowerAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
}
