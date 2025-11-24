// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/Pickups/PickupBase.h"

#include "Components/SphereComponent.h"
#include "Interactables/Pickups/PickupDataAsset.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APickupBase::APickupBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>("Collider");
	SetRootComponent(Collider);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	BaseMesh->SetupAttachment(Collider);

	Collider->OnComponentBeginOverlap.AddUniqueDynamic(this, &APickupBase::OnOverlapBegin);
}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickupBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (PickupDA)
	{
		if (PickupDA->PickupMesh)
		{
			BaseMesh->SetStaticMesh(PickupDA->PickupMesh);
		}
	}
}

void APickupBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		OnPickedUp(OtherActor);
		if (PickupDA && PickupDA->PickupSound)
			UGameplayStatics::PlaySoundAtLocation(this, PickupDA->PickupSound, GetActorLocation());

		Destroy();
	}
}

void APickupBase::OnPickedUp_Implementation(AActor* PickingActor)
{
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

