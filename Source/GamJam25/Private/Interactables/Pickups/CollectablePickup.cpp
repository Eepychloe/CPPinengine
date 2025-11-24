// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/Pickups/CollectablePickup.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Managers/GRM_Subsystem.h"
#include "C++Scripts/PlayerCharacter/PlayerCharacterInterface.h"


// Sets default values
ACollectablePickup::ACollectablePickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>("Collider");
	SetRootComponent(Collider);
	Collider->SetSphereRadius(75.0f);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	BaseMesh->SetupAttachment(Collider);

	Collider->OnComponentBeginOverlap.AddUniqueDynamic(this, &ACollectablePickup::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ACollectablePickup::BeginPlay()
{
	Super::BeginPlay();

	UGRM_Subsystem* Manager = GetWorld()->GetSubsystem<UGRM_Subsystem>();
	Manager->RegisterCollectible(this);

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, [this]()
	{
		if (UGRM_Subsystem* Manager = GetWorld()->GetSubsystem<UGRM_Subsystem>())
		{
			Manager->FinaliseRegistration();
		}
	}, 0.1f, false);
}

void ACollectablePickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UKismetSystemLibrary::DoesImplementInterface(OtherActor, UPlayerCharacterInterface::StaticClass()))
	{
		UGRM_Subsystem* Manager = GetWorld()->GetSubsystem<UGRM_Subsystem>();
		Manager->NotifyCollection(this);
		if (PickupSound)
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetActorLocation());
		Destroy();
	}
}

// Called every frame
void ACollectablePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

