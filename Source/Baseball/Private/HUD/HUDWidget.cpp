// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/HUDWidget.h"
#include "HUD/ThrowForceBar.h"
#include "HUD/SwingForceBar.h"
#include "Components/ProgressBar.h"

void UHUDWidget::BeginPlay()
{
	Super::BeginPlay();
}

void UHUDWidget::SetThrowBarProgress(float value)
{
	if (ThrowForceBarWidget == nullptr)
	{
		ThrowForceBarWidget = Cast<UThrowForceBar>(GetUserWidgetObject());
	}

	if (ThrowForceBarWidget && ThrowForceBarWidget->ThrowForceBar)
	{
		ThrowForceBarWidget->ThrowForceBar->SetPercent(value);
	}
}

float UHUDWidget::GetThrowBarProgress()
{
	if (ThrowForceBarWidget == nullptr)
	{
		ThrowForceBarWidget = Cast<UThrowForceBar>(GetUserWidgetObject());
	}

	if (ThrowForceBarWidget && ThrowForceBarWidget->ThrowForceBar)
	{
		return ThrowForceBarWidget->ThrowForceBar->GetPercent();
	}

	return 0.f;
}

void UHUDWidget::SetSwingBarProgress(float value)
{
	if (SwingForceBarWidget == nullptr)
	{
		SwingForceBarWidget = Cast<USwingForceBar>(GetUserWidgetObject());
	}

	if (SwingForceBarWidget && SwingForceBarWidget->SwingForceBar)
	{
		SwingForceBarWidget->SwingForceBar->SetPercent(value);
	}
}

float UHUDWidget::GetSwingBarProgress()
{
	if (SwingForceBarWidget == nullptr)
	{
		SwingForceBarWidget = Cast<USwingForceBar>(GetUserWidgetObject());
	}

	if (SwingForceBarWidget && SwingForceBarWidget->SwingForceBar)
	{
		return SwingForceBarWidget->SwingForceBar->GetPercent();
	}

	return 0.f;
}
