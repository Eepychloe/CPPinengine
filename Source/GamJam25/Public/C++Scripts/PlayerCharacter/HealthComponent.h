// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthInterface.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, NewHealth);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAMJAM25_API UHealthComponent : public UActorComponent, public IHealthInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void OnDamaged(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InsigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void AddHealth(float Health);

	UPROPERTY(EditDefaultsOnly, Category = Health)
	float MaxHealth = 100.0f;

	UPROPERTY(BlueprintReadOnly, Category = Health)
	float CurrentHealth = 0.0f;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Health)
	FOnDeathEvent OnDeath;

	UPROPERTY()
	FOnHealthChanged UpdateHealth;

	void BroadcastHealthChange() const;

	virtual float GetMaxHealth() const override{return MaxHealth;}
	virtual FOnHealthChanged& GetHealthChangedDelegate() override{ return UpdateHealth;}
};
