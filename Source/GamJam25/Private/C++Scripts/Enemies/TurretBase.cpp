// Fill out your copyright notice in the Description page of Project Settings.


#include "GamJam25/Public/C++Scripts/Enemies/TurretBase.h"

#include "C++Scripts/Enemies/ProjectileBase.h"
#include "Components/ArrowComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/TurretWorldManager.h"


// Sets default values
ATurretBase::ATurretBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComponent"));
	SetRootComponent(BaseMeshComponent);

	BarrelMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrelMeshComponent"));
	BarrelMeshComponent->SetupAttachment(BaseMeshComponent);
	BarrelMeshComponent->SetRelativeLocation(FVector(60.0f, 0.0f, 0.0f));
	BarrelMeshComponent->SetRelativeScale3D(FVector(0.5f));

	FirePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePoint"));
	FirePoint->SetupAttachment(BarrelMeshComponent);
	FirePoint->SetRelativeLocation(FVector(280.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void ATurretBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (UWorld* World = GetWorld())
	{
		if (UTurretWorldManager* Manager = World->GetSubsystem<UTurretWorldManager>())
		{
			Manager->RegisterTurret(this);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("UTurretWorldManager subsystem is not loaded"));
		}
	}

	GetWorldTimerManager().SetTimer(FireTimer, this, &ATurretBase::Fire, FireSpeed, true);
}

void ATurretBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UWorld* World = GetWorld())
	{
		if (UTurretWorldManager* Manager = World->GetSubsystem<UTurretWorldManager>())
		{
			Manager->UnRegisterTurret(this);
		}
	}
	
	Super::EndPlay(EndPlayReason);
}

void ATurretBase::Fire_Implementation()
{
	const FVector Location = FirePoint->GetComponentLocation();
	const FRotator Rotation = FirePoint->GetComponentRotation();

	AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, Location, Rotation);
	Projectile->BaseDamage = ProjectileDamageOverride; //Allows Turret to set damage instead of creating new projectiles
	Projectile->SetIgnoredActors(this, GetOwner());

	if (FireSound)
		UGameplayStatics::PlaySound2D(GetWorld(), FireSound, FireAudioVolume);

	if (FireFX)
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FireFX, Location, Rotation);

	UE_LOG(LogTemp, Error, TEXT("Turret FIre"));
}

void ATurretBase::SetTurretEnabled(bool bEnabled)
{
	bTurretIsEnabled = bEnabled;
	if (!bTurretIsEnabled)
	{
		GetWorldTimerManager().ClearTimer(FireTimer);
	}
	else
	{
		GetWorldTimerManager().SetTimer(FireTimer, this, &ATurretBase::Fire, FireSpeed, true);
	}
}

// Called every frame
void ATurretBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

