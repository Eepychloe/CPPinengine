// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/Pickups/Spells/ElectricSpell.h"

#include "C++Scripts/Enemies/ProjectileBase.h"
#include "Components/ArrowComponent.h"


// Sets default values
AElectricSpell::AElectricSpell()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FirePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	SetRootComponent(FirePoint);
}

// Called when the game starts or when spawned
void AElectricSpell::BeginPlay()
{
	Super::BeginPlay();
	
}

void AElectricSpell::SpellCast_Implementation()
{
	Super::SpellCast_Implementation();
	if (CurrentAmmo > BurstCount)
	{
		SpawnProjectile();
	}
	else
	{
		HandleEmpty();
	}
}

void AElectricSpell::SpawnProjectile_Implementation()
{
	Super::SpawnProjectile_Implementation();
	
	ModifyAmmo(1);
	CurrentBurst++;
	if (CurrentBurst == BurstCount)
	{
		CurrentBurst = 0;
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(BurstTimer, this, &AElectricSpell::SpawnProjectile, 0.05f, false);
	}
}

FTransform AElectricSpell::GetProjectileTransform()
{
	if (FirePoint)
	{
		FVector location = FirePoint->GetComponentLocation();
		FRotator rotation = FirePoint->GetComponentRotation();
		return FTransform(rotation, location);
	}
	return Super::GetProjectileTransform();
}

// Called every frame
void AElectricSpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

