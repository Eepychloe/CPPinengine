// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Spells/SpellBase.h"
#include "PickupDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class GAMJAM25_API UPickupDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickupDataAsset")
	TObjectPtr<UStaticMesh> PickupMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickupDataAsset")
	TObjectPtr<USoundBase> PickupSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickupDataAsset")
	float PickupValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickupDataAsset")
	TSubclassOf<ASpellBase> SpellClass;
};
