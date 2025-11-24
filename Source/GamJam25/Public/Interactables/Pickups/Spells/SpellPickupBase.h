// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/Pickups/PickupBase.h"
#include "SpellPickupBase.generated.h"

UCLASS()
class GAMJAM25_API ASpellPickupBase : public APickupBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpellPickupBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnPickedUp_Implementation(AActor* PickingActor) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
