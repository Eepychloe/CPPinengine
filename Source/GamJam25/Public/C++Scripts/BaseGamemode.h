// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseGamemode.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateCollectibles, uint8, Score);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCollectibleRuleComplete);

UCLASS()
class GAMJAM25_API ABaseGamemode : public AGameModeBase
{
	GENERATED_BODY()

	ABaseGamemode();

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameRules")
	uint8 NumberOfRequiredCoins;

	UPROPERTY(BlueprintAssignable)
	FOnUpdateCollectibles OnUpdateCollectibles;

	UPROPERTY(BlueprintAssignable)
	FOnCollectibleRuleComplete CollectibleRuleComplete;

private:
	UFUNCTION()
	void SetNumOfCoinsRequired(uint8 MaxCoins);

	UFUNCTION()
	void LogCollectible();

	uint8 CurrentNumOfCoins;
};
