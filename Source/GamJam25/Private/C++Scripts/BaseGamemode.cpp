// Fill out your copyright notice in the Description page of Project Settings.


#include "GamJam25/Public/C++Scripts/BaseGamemode.h"

#include "Managers/GRM_Subsystem.h"

ABaseGamemode::ABaseGamemode()
{
	
}

void ABaseGamemode::BeginPlay()
{
	Super::BeginPlay();
	if (GetWorld())
	{
		UGRM_Subsystem* Manager = GetWorld()->GetSubsystem<UGRM_Subsystem>();
		Manager->RegistrationComplete.AddUniqueDynamic(this, &ABaseGamemode::SetNumOfCoinsRequired);
		Manager->OnCollectionEvent.AddUniqueDynamic(this, &ABaseGamemode::LogCollectible);
	}
}

void ABaseGamemode::SetNumOfCoinsRequired(uint8 MaxCoins)
{
	NumberOfRequiredCoins = MaxCoins;
}

void ABaseGamemode::LogCollectible()
{
	CurrentNumOfCoins++;
	if (OnUpdateCollectibles.IsBound())
		OnUpdateCollectibles.Broadcast(CurrentNumOfCoins);

	if (CurrentNumOfCoins == NumberOfRequiredCoins)
		if (CollectibleRuleComplete.IsBound())
			CollectibleRuleComplete.Broadcast();
}
