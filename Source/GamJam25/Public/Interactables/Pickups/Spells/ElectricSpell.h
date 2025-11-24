// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellBase.h"
#include "ElectricSpell.generated.h"

class UArrowComponent;

UCLASS()
class GAMJAM25_API AElectricSpell : public ASpellBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AElectricSpell();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spell Data")
	TObjectPtr<UArrowComponent> FirePoint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SpellCast_Implementation() override;
	virtual void SpawnProjectile_Implementation() override;

	virtual FTransform GetProjectileTransform() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell Data")
	uint8 BurstCount = 3;

private:
	uint8 CurrentBurst = 0;
	FTimerHandle BurstTimer;
};
