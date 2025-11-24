// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/Pickups/Spells/SpellBase.h"

#include "C++Scripts/Enemies/ProjectileBase.h"


// Sets default values
ASpellBase::ASpellBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASpellBase::SpellCast_Implementation()
{
}

void ASpellBase::AltSpellCast_Implementation()
{
}

void ASpellBase::Charge_Implementation()
{
	uint8 ToReload = FMath::Clamp(CurrentReserve - (MaxAmmo - CurrentAmmo), 0, MaxAmmo);

	CurrentAmmo += ToReload;
	CurrentReserve -= ToReload;
}

void ASpellBase::SpawnProjectile_Implementation()
{
	FTransform SpawnTransform = GetProjectileTransform();

	AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnTransform.GetLocation(),
		SpawnTransform.GetRotation().Rotator());
	Projectile->SetIgnoredActors(this, GetOwner());
}

void ASpellBase::ModifyAmmo_Implementation(uint8 ToReduce)
{
	CurrentAmmo = FMath::Clamp(CurrentAmmo - ToReduce, 0, MaxAmmo);
}

void ASpellBase::HandleEmpty_Implementation()
{
	if (bAllowedAutoReload)
	{
		Charge();
	}
	else
	{
		{
			//tell player to reload or something
		}
	}
}

// Called when the game starts or when spawned
void ASpellBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = MaxAmmo;
	CurrentReserve = MaxReserve;
}

FTransform ASpellBase::GetProjectileTransform()
{
	return FTransform(GetActorRotation(), GetActorLocation());
}

// Called every frame
void ASpellBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

