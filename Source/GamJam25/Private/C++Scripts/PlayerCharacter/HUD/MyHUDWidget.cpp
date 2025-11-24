// Fill out your copyright notice in the Description page of Project Settings.


#include "C++Scripts/PlayerCharacter/HUD/MyHUDWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMyHUDWidget::OnHealthChanged(float NewHealth)
{
	if (HealthBar)
		HealthBar->SetPercent(NewHealth / MaxHealth);
}

void UMyHUDWidget::OnScoreChanged(uint8 NewScore)
{
	if (ScoreText)
	{
		FText Formatted = FText::Format(ScoreLabel, FText::AsNumber(NewScore));
		ScoreText->SetText(Formatted);
	}
}

void UMyHUDWidget::SetMaxHealth(float PlayerMaxHealth)
{
	MaxHealth = PlayerMaxHealth;
}
