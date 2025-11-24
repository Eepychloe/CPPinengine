// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/GRM_Subsystem.h"

void UGRM_Subsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UGRM_Subsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UGRM_Subsystem::NotifyCollection(ACollectablePickup* Collectible)
{
	Collectibles.Remove(Collectible);
	OnCollectionEvent.Broadcast();
}

void UGRM_Subsystem::RegisterCollectible(ACollectablePickup* Collectible)
{
	if (Collectible && !Collectibles.Contains(Collectible))
	{
		Collectibles.Add(Collectible);
	}
}

void UGRM_Subsystem::FinaliseRegistration()
{
	if (!bRegistrationComplete)
	{
		bRegistrationComplete = true;
		if (RegistrationComplete.IsBound())
			RegistrationComplete.Broadcast(Collectibles.Num());
	}
}