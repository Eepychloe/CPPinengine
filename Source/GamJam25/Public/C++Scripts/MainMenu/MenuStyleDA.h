// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MenuStyleDA.generated.h"

/**
 * 
 */
UCLASS()
class GAMJAM25_API UMenuStyleDA : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MenuStyleSheet|Colours")
	FLinearColor ButtonColor = FLinearColor(0.1f, 0.1f, 0.1f, 1.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MenuStyleSheet|Colours")
	FLinearColor ButtonHoverColor = FLinearColor(0.15f, 0.15f, 0.15f, 1.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MenuStyleSheet|Colours")
	FLinearColor TextColor = FLinearColor::White;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MenuStyleSheet|Font")
	FSlateFontInfo ButtonFont;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MenuStyleSheet|Layout")
	FVector2D ButtonSize = FVector2D(300.0f, 80.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MenuStyleSheet|Flow")
	TSoftObjectPtr<UWorld> GameplayLevel;
};
