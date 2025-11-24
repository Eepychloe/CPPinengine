// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/Pickups/CollectablePickup.h"
#include "Subsystems/WorldSubsystem.h"
#include "GRM_Subsystem.generated.h"


/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCollectionEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAllCollectiblesRegistered, uint8, NumOfCollectibles);

UCLASS()
class GAMJAM25_API UGRM_Subsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	UPROPERTY(BlueprintAssignable)
	FOnCollectionEvent OnCollectionEvent;

	UPROPERTY(BlueprintAssignable)
	FOnAllCollectiblesRegistered RegistrationComplete;

	void NotifyCollection(ACollectablePickup* Collectible);

	void RegisterCollectible(ACollectablePickup* Collectible);

	void FinaliseRegistration();

private:
	UPROPERTY()
	TArray<TWeakObjectPtr<ACollectablePickup>> Collectibles;

	bool bRegistrationComplete = false;
};
