// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interactables/Pickups/Spells/SpellBase.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpellChanged);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAMJAM25_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<TSubclassOf<ASpellBase>>AvailableSpells;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	uint8 CurrentSpellIndex = 0;

	UPROPERTY(BlueprintAssignable, Category = "Inventory|Spells")
	FOnSpellChanged OnSpellChanged;

	void AddSpell(TSubclassOf<ASpellBase> NewSpell);
	void NextSpell();
	void PreviousSpell();

	TSubclassOf<ASpellBase> GetCurrentSpell() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
