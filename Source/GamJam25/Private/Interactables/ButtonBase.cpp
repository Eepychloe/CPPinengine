// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/ButtonBase.h"

#include "C++Scripts/PlayerCharacter/PlayerCharacterInterface.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Managers/TurretWorldManager.h"

class UTurretWorldManager;
// Sets default values
AButtonBase::AButtonBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Collider");
	SetRootComponent(BoxCollision);

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>("ButtonMesh");
	ButtonMesh->SetupAttachment(BoxCollision);
}

// Called when the game starts or when spawned
void AButtonBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AButtonBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (BoxCollision)
	{
		BoxCollision->OnComponentBeginOverlap.RemoveDynamic(this, &AButtonBase::CheckpointOverlapped);
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AButtonBase::CheckpointOverlapped);
		BoxCollision->OnComponentEndOverlap.RemoveDynamic(this, &AButtonBase::CheckpointOverlapEnd);
		BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AButtonBase::CheckpointOverlapEnd);
	}
}

void AButtonBase::Interact_Implementation()
{
	if (!bInteracted)
	{
		IInteractionInterface::Interact_Implementation();
		if (UWorld* World = GetWorld())
		{
			if (UTurretWorldManager* Manager = World->GetSubsystem<UTurretWorldManager>())
			{
				Manager->DisableAllTurrets();
				bInteracted = true;
			}
		}
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, "Turrets Disabled");
	}
}

void AButtonBase::CheckpointOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (UKismetSystemLibrary::DoesImplementInterface(OtherActor, UPlayerCharacterInterface::StaticClass()))
	{
		IPlayerCharacterInterface::Execute_SetOverlappedActor(OtherActor, this);
	}
}

void AButtonBase::CheckpointOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (UKismetSystemLibrary::DoesImplementInterface(OtherActor, UPlayerCharacterInterface::StaticClass()))
	{
		IPlayerCharacterInterface::Execute_SetOverlappedActor(OtherActor, nullptr);
	}
}


// Called every frame
void AButtonBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

