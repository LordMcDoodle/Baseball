// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HUDWidget.generated.h"

class UThrowForceBar;
class USwingForceBar;
/**
* 
 * 
 */
UCLASS()
class BASEBALL_API UHUDWidget : public UWidgetComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	void SetThrowBarProgress(float value);
	float GetThrowBarProgress();

	void SetSwingBarProgress(float value);
	float GetSwingBarProgress();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UThrowForceBar* ThrowForceBarWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USwingForceBar* SwingForceBarWidget;

private:

};
