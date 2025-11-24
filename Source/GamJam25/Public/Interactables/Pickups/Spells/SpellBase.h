// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpellBase.generated.h"

class AProjectileBase;

UCLASS(Abstract, Blueprintable) //Abstract means cant be used, only children of the class.
class GAMJAM25_API ASpellBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpellBase();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spell Base Data")
	void SpellCast();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spell Base Data")
	void AltSpellCast();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spell Base Data")
	void Charge();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, Category = "Spell Base Data")
	uint8 CurrentAmmo = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Spell Base Data")
	uint8 CurrentReserve = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell Base Data")
	uint8 MaxAmmo = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell Base Data")
	uint8 MaxReserve = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell Base Data")
	bool bAllowedAutoReload = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell Base Data")
	TSubclassOf<AProjectileBase> ProjectileClass;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spell Base Data")
	void SpawnProjectile();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spell Base Data")
	void ModifyAmmo(uint8 ToReduce);

	UFUNCTION(BlueprintCallable, Category = "Spell Base Data")
	bool HasAmmo();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spell Base Data")
	void HandleEmpty();

	virtual FTransform GetProjectileTransform();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

inline bool ASpellBase::HasAmmo()
{
	return CurrentAmmo > 0;
}
