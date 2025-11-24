// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IAInterface.h"
#include "GameFramework/Character.h"
#include "Interactables/Pickups/Spells/SpellBase.h"
#include "PlayerCharacter/PlayerCharacterInterface.h"
#include "PlayerCharacter_Base.generated.h"


class UInventoryComponent;
class UHealthComponent;
class UCameraComponent;
class USpringArmComponent;


UCLASS()
class GAMJAM25_API APlayerCharacter_Base : public ACharacter, public IIAInterface, public IPlayerCharacterInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UHealthComponent> Health;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UInventoryComponent> InventoryComp;

	UPROPERTY(BlueprintReadWrite, Category = Speeds)
	float WalkSpeed = 400.0;

	UPROPERTY(BlueprintReadOnly, Category = Interaction)
	TObjectPtr<AActor> OverlappingActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Spell)
	TSubclassOf<ASpellBase> SpellWeapon;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Move_Implementation(const FInputActionInstance& Instance) override;

	virtual void Look_Implementation(const FInputActionInstance& Instance) override;

	virtual void Action_Implementation(const FInputActionInstance& Instance) override;

	virtual void JumpAction_Implementation(const FInputActionInstance& Instance) override;

	virtual void Fire_Implementation(const FInputActionInstance& Instance) override;

	virtual void Scroll_Implementation(const FInputActionInstance& Instance) override;

	virtual void SetOverlappedActor_Implementation(AActor* OverlappedActor) override;

	virtual void SpellCast_Implementation() override;

	virtual void EnableSpellCasting_Implementation(bool bEnableFire) override;

	virtual void AddHealthFromPickup_Implementation(float Value) override;

	virtual void AddSpellFromPickup_Implementation(TSubclassOf<ASpellBase> Spell) override;

	UFUNCTION()
	void PlayerDeath();

private:
	UFUNCTION()
	void AttachSpell();

	UPROPERTY()
	ASpellBase* EquippedSpell;

	UPROPERTY()  //Caches Spells instead of destroying and recreating when scrolled to
	TMap<TSubclassOf<ASpellBase>, ASpellBase*> SpawnedSpells;

	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UPROPERTY()
	TObjectPtr<UAnimInstance> AnimInstance;

	bool bCanFire = true;
};
