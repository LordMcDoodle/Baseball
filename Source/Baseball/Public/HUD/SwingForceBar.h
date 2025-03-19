// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SwingForceBar.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class BASEBALL_API USwingForceBar : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* SwingForceBar;
};
