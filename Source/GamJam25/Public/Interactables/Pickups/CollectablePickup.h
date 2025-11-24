// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollectablePickup.generated.h"

class USphereComponent;

UCLASS()
class GAMJAM25_API ACollectablePickup : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACollectablePickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = PickupData)
	TObjectPtr<USphereComponent> Collider;

	UPROPERTY(VisibleAnywhere, Category = PickupData)
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(EditDefaultsOnly, Category = PickupData)
	TObjectPtr<USoundBase> PickupSound;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
