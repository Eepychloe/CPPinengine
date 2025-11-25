// Fill out your copyright notice in the Description page of Project Settings.


#include "GamJam25/Public/C++Scripts/PlayerCharacter_Base.h"

#include "C++Scripts/PlayerCharacter/InventoryComponent.h"
#include "C++Scripts/PlayerCharacter/PlayerCharacterAnimInterface.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GamJam25/Interactables/InteractionInterface.h"
#include "GamJam25/Public/C++Scripts/PlayerController_Base.h"
#include "GamJam25/Public/C++Scripts/PlayerCharacter/HealthComponent.h"


// Sets default values
APlayerCharacter_Base::APlayerCharacter_Base()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	Health = CreateDefaultSubobject<UHealthComponent>("Health");
	InventoryComp = CreateDefaultSubobject<UInventoryComponent>("InventoryComponent");

	bUseControllerRotationPitch = true;
	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = false;
	SpringArm->bUsePawnControlRotation = true;

	Tags.Add(FName("Player"));
}

// Called when the game starts or when spawned
void APlayerCharacter_Base::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	if (Health)
	{
		Health->OnDeath.AddUniqueDynamic(this, &APlayerCharacter_Base::PlayerDeath);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "No Health Valid Component Added");
	}

	SkeletalMeshComponent = GetMesh();
	if (!SkeletalMeshComponent)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "No Skeletal Mesh Assigned");
		return;
	}
	AnimInstance = SkeletalMeshComponent->GetAnimInstance();
	if (!AnimInstance)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "No Anim BP Assigned");
		return;
	}

	if (InventoryComp)
	{
		InventoryComp->OnSpellChanged.AddUniqueDynamic(this, &APlayerCharacter_Base::AttachSpell);
		InventoryComp->AddSpell(SpellWeapon);
	}
}

// Called every frame
void APlayerCharacter_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter_Base::Move_Implementation(const FInputActionInstance& Instance)
{
	IIAInterface::Move_Implementation(Instance);
	if (Controller)
	{
		const FVector2D MoveValue = Instance.GetValue().Get<FVector2D>();
		const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);

		if (FMath::Abs(MoveValue.Y) > KINDA_SMALL_NUMBER)
		{
			const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);
			AddMovementInput(Direction, MoveValue.Y);
		}
		if (FMath::Abs(MoveValue.X) > KINDA_SMALL_NUMBER)
		{
			const FVector Direction = MovementRotation.RotateVector( FVector::RightVector);
			AddMovementInput(Direction, MoveValue.X);
		}
	}
}

void APlayerCharacter_Base::Look_Implementation(const FInputActionInstance& Instance)
{
	IIAInterface::Look_Implementation(Instance);
	if (Controller)
	{
		const FVector2D AxisValue = Instance.GetValue().Get<FVector2D>();
		if (AxisValue.Y != 0.0f)
		{
			AddControllerPitchInput(-AxisValue.Y);
		}
		if (AxisValue.X != 0.0f)
		{
			AddControllerYawInput(AxisValue.X);
		}
	}
}

void APlayerCharacter_Base::Action_Implementation(const FInputActionInstance& Instance)
{
	IIAInterface::Action_Implementation(Instance);
	bool bValue = Instance.GetValue().Get<bool>();

	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Fire");
	if (OverlappingActor)
	{
		IInteractionInterface::Execute_Interact(OverlappingActor);
	}
}

void APlayerCharacter_Base::JumpAction_Implementation(const FInputActionInstance& Instance)
{
	IIAInterface::JumpAction_Implementation(Instance);
	Jump();
}

void APlayerCharacter_Base::Fire_Implementation(const FInputActionInstance& Instance)
{
	IIAInterface::Fire_Implementation(Instance);

	if (!SkeletalMeshComponent)
		return;

	if (bCanFire)
	{
		bCanFire = false;
		IPlayerCharacterAnimInterface::Execute_PlaySpellCastAnimation(AnimInstance, true);
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Fire");
	}
}

void APlayerCharacter_Base::Scroll_Implementation(const FInputActionInstance& Instance)
{
	IIAInterface::Scroll_Implementation(Instance);

	float ScrolledValue = Instance.GetValue().Get<float>();
	if (InventoryComp)
	{
		if (ScrolledValue > 0.0f)
			InventoryComp->NextSpell();

		else if (ScrolledValue < 0.0f)
			InventoryComp->PreviousSpell();
	}
}

void APlayerCharacter_Base::SpellCast_Implementation()
{
	IPlayerCharacterInterface::SpellCast_Implementation();

	EquippedSpell->SpellCast();
}

void APlayerCharacter_Base::EnableSpellCasting_Implementation(bool bEnableFire)
{
	IPlayerCharacterInterface::EnableSpellCasting_Implementation(bEnableFire);
	bCanFire = bEnableFire;
}

void APlayerCharacter_Base::AddHealthFromPickup_Implementation(float Value)
{
	IPlayerCharacterInterface::AddHealthFromPickup_Implementation(Value);
	Health->AddHealth(Value);
}

void APlayerCharacter_Base::AddSpellFromPickup_Implementation(TSubclassOf<ASpellBase> Spell)
{
	IPlayerCharacterInterface::AddSpellFromPickup_Implementation(Spell);
	InventoryComp->AddSpell(Spell);
}

void APlayerCharacter_Base::AttachSpell() //Refactored after binding with inventory comp
{
	if (!SpellWeapon || !InventoryComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "No Spell Class Or Inventory Assigned");
		return;
	}

	TSubclassOf<ASpellBase>SpellClass = InventoryComp->GetCurrentSpell();
	if (!SpellClass)
		return;

	if (EquippedSpell)
	{
		EquippedSpell->SetActorHiddenInGame(true);
		EquippedSpell->SetActorEnableCollision(false);
	}

	ASpellBase* CachedSpell = nullptr;

	if (SpawnedSpells.Contains(SpellClass))
	{
		CachedSpell = SpawnedSpells[SpellClass];
	}
	else
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		SpawnParameters.Instigator = GetInstigator();

		CachedSpell = GetWorld()->SpawnActor<ASpellBase>(SpellClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);

		if (CachedSpell)
		{
			const FName AttachmentSocketName = FName("SpellSocket");
			CachedSpell->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, AttachmentSocketName);
		}
	}

	if (CachedSpell)
	{
		EquippedSpell = CachedSpell;
		EquippedSpell->SetActorHiddenInGame(false);
		EquippedSpell->SetActorEnableCollision(true);
	}
}

void APlayerCharacter_Base::PerformTrace(float Length, float Radius, ECollisionChannel Channel, bool& bHit,
	FHitResult& Result)
{
	bHit = false;
	Result = FHitResult();

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	const FVector Start = GetActorLocation();
	const FVector End = Start + (GetActorForwardVector() * Length);

	bHit = GetWorld()->SweepSingleByChannel(Result, Start, End, FQuat::Identity, Channel,
		FCollisionShape::MakeSphere(Radius), Params);
	if (bDrawDebug)
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 2.0f, 0, 2.0f);

		DrawDebugSphere(GetWorld(), Start, Radius, 16, FColor::Yellow, false, 2.0f);

		DrawDebugSphere(GetWorld(), End, Radius, 16, FColor::Yellow, false, 2.0f);

		if (bHit)
		{
			DrawDebugPoint(GetWorld(), Result.ImpactPoint, 12.0f, FColor::Red, false, 2.0f);

			DrawDebugLine(GetWorld(), Result.ImpactPoint, Result.ImpactPoint + Result.ImpactNormal * 50.0f, FColor::Red,
				false, 2.0f, 0, 2.0f);
		}
	}
}

void APlayerCharacter_Base::SetOverlappedActor_Implementation(AActor* OverlappedActor)
{
	IPlayerCharacterInterface::SetOverlappedActor_Implementation(OverlappedActor);
	OverlappingActor = OverlappedActor;
}

void APlayerCharacter_Base::PlayerDeath()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Player Died! Disabling Input.");
	APlayerController_Base* PC = Cast<APlayerController_Base>(GetController());
	PC->SetIgnoreMoveInput(true);
	PC->SetIgnoreLookInput(true);
}


