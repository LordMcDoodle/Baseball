// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Field/FieldSystemActor.h"
#include "ThrowerFieldSystem.generated.h"

/**
 * 
 */
UCLASS()
class BASEBALL_API AThrowerFieldSystem : public AFieldSystemActor 
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	float Force;

	UFUNCTION(BlueprintImplementableEvent)
	void CreateForce();

};
