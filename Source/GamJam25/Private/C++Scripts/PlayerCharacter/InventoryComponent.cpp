// Fill out your copyright notice in the Description page of Project Settings.


#include "C++Scripts/PlayerCharacter/InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInventoryComponent::AddSpell(TSubclassOf<ASpellBase> NewSpell)
{
	if (!AvailableSpells.Contains(NewSpell))
	{
		AvailableSpells.Add(NewSpell);
		if (AvailableSpells.Num() == 1)
		{
			CurrentSpellIndex = 0;
			OnSpellChanged.Broadcast();
		}
	}
}

void UInventoryComponent::NextSpell()
{
	if (AvailableSpells.Num() == 0)
		return;

	CurrentSpellIndex = (CurrentSpellIndex + 1) % AvailableSpells.Num();
	OnSpellChanged.Broadcast();
}

void UInventoryComponent::PreviousSpell()
{
	if (AvailableSpells.Num() == 0)
		return;

	CurrentSpellIndex = (CurrentSpellIndex - 1 + AvailableSpells.Num()) % AvailableSpells.Num();
	OnSpellChanged.Broadcast();
}

TSubclassOf<ASpellBase> UInventoryComponent::GetCurrentSpell() const
{
	if (AvailableSpells.IsValidIndex(CurrentSpellIndex))
		return AvailableSpells[CurrentSpellIndex];

	return nullptr;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

