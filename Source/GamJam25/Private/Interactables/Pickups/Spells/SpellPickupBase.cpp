// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/Pickups/Spells/SpellPickupBase.h"

#include "C++Scripts/PlayerCharacter/PlayerCharacterInterface.h"
#include "Interactables/Pickups/PickupDataAsset.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
ASpellPickupBase::ASpellPickupBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpellPickupBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpellPickupBase::OnPickedUp_Implementation(AActor* PickingActor)
{
	Super::OnPickedUp_Implementation(PickingActor);
	if (!PickupDA || !PickupDA->SpellClass)
		return;

	if (UKismetSystemLibrary::DoesImplementInterface(PickingActor, UPlayerCharacterInterface::StaticClass()))
		IPlayerCharacterInterface::Execute_AddSpellFromPickup(PickingActor, PickupDA->SpellClass);
}

// Called every frame
void ASpellPickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

