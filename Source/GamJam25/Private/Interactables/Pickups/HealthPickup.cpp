// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/Pickups/HealthPickup.h"

#include "C++Scripts/PlayerCharacter/PlayerCharacterInterface.h"
#include "Interactables/Pickups/PickupDataAsset.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AHealthPickup::AHealthPickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHealthPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHealthPickup::OnPickedUp_Implementation(AActor* PickingActor)
{
	Super::OnPickedUp_Implementation(PickingActor);

	if (!PickupDA)
		return;

	float HealthValue = PickupDA->PickupValue;

	if (UKismetSystemLibrary::DoesImplementInterface(PickingActor, UPlayerCharacterInterface::StaticClass()))
		IPlayerCharacterInterface::Execute_AddHealthFromPickup(PickingActor, HealthValue);
}

// Called every frame
void AHealthPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

