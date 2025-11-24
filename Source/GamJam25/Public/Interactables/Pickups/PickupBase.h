// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupBase.generated.h"

class UPickupDataAsset;
class USphereComponent;

UCLASS(Abstract)
class GAMJAM25_API APickupBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickupBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PickupData)
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PickupData)
	TObjectPtr<USphereComponent> Collider;

	UPROPERTY(EditAnywhere, Category = PickupData)
	TObjectPtr<UPickupDataAsset> PickupDA;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = PickupData)
	void OnPickedUp(AActor* PickingActor);
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
