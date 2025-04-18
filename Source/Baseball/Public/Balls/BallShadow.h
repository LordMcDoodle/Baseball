// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallShadow.generated.h"

UCLASS()
class BASEBALL_API ABallShadow : public AActor
{
	GENERATED_BODY()
	
public:	
	ABallShadow();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* mesh;


public:	
	virtual void Tick(float DeltaTime) override;

};
