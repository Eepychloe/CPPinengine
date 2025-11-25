// Fill out your copyright notice in the Description page of Project Settings.


#include "GamJam25/Public/C++Scripts/PlayerCharacter/HealthComponent.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddUniqueDynamic(this, &UHealthComponent::OnDamaged);
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	//
}

void UHealthComponent::OnDamaged(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	class AController* InstigatedBy, AActor* DamageCauser)
{
	if (CurrentHealth > 0)
	{
		CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, MaxHealth);
		UE_LOG(LogTemp, Warning, TEXT( "Health: %f"), CurrentHealth);

		if (CurrentHealth <= 0.0)
		{
			if (OnDeath.IsBound())
				OnDeath.Broadcast();
		}

		BroadcastHealthChange();
	}
}

void UHealthComponent::AddHealth(float Health)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + Health, 0.0f, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), CurrentHealth);

	BroadcastHealthChange();
}

void UHealthComponent::BroadcastHealthChange() const
{
	if (UpdateHealth.IsBound())
		UpdateHealth.Broadcast(CurrentHealth);
}


