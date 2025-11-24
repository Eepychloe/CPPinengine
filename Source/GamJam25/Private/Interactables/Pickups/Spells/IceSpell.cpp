// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/Pickups/Spells/IceSpell.h"

#include "C++Scripts/Enemies/ProjectileBase.h"
#include "Components/ArrowComponent.h"


// Sets default values
AIceSpell::AIceSpell()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FirePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	SetRootComponent(FirePoint);
}

// Called when the game starts or when spawned
void AIceSpell::BeginPlay()
{
	Super::BeginPlay();
	
}

void AIceSpell::SpellCast_Implementation()
{
	Super::SpellCast_Implementation();
	if (HasAmmo())
	{
		SpawnProjectile();
		ModifyAmmo(1);
	}
	else
	{
		{
			HandleEmpty();
		}
	}
}

void AIceSpell::SpawnProjectile_Implementation()
{
	Super::SpawnProjectile_Implementation();

}

FTransform AIceSpell::GetProjectileTransform()
{
	if (FirePoint)
	{
		FVector location = FirePoint->GetComponentLocation();
		FRotator Rotation = FirePoint->GetComponentRotation();
		return FTransform(Rotation, location);
	}
	
	return Super::GetProjectileTransform();
}

// Called every frame
void AIceSpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

