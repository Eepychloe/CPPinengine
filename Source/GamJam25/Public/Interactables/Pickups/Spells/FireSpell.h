// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellBase.h"
#include "FireSpell.generated.h"

class UArrowComponent;

UCLASS()
class GAMJAM25_API AFireSpell : public ASpellBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFireSpell();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spell Data")
	TObjectPtr<UArrowComponent> FirePoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spell Data")
	TObjectPtr<UArrowComponent> FirePoint2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spell Data")
	TObjectPtr<UArrowComponent> FirePoint3;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SpellCast_Implementation() override;
	virtual void SpawnProjectile_Implementation() override;

	virtual FTransform GetProjectileTransform() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	TArray<TObjectPtr<UArrowComponent>> FirePoints;
	uint8 ActiveFirePoint = 0;
};
