// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyHUDWidget.generated.h"

class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class GAMJAM25_API UMyHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void OnHealthChanged(float NewHealth);

	UFUNCTION()
	void OnScoreChanged(uint8 NewScore); // Max of 255, may need to change later

	UFUNCTION()
	void SetMaxHealth(float PlayerMaxHealth);

protected:

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> HealthBar;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> ScoreText;

	float MaxHealth = 100;

	FText ScoreLabel = FText::FromString("Score: {0}");
};
