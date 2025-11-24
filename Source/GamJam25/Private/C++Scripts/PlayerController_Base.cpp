// Fill out your copyright notice in the Description page of Project Settings.


#include "GamJam25/Public/C++Scripts/PlayerController_Base.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "C++Scripts/BaseGamemode.h"
#include "C++Scripts/PlayerCharacter/HealthComponent.h"
#include "C++Scripts/PlayerCharacter/HealthInterface.h"
#include "C++Scripts/PlayerCharacter/HUD/MyHUDWidget.h"
#include "GameFramework/GameModeBase.h"
#include "GamJam25/Public/C++Scripts/IAInterface.h"
#include "GamJam25/Public/C++Scripts/IADataConfig.h"

void APlayerController_Base::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (MappingContext)
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}

	if (ABaseGamemode* GM = Cast<ABaseGamemode>(GetWorld()->GetAuthGameMode()))
	{
		GM->CollectibleRuleComplete.AddUniqueDynamic(this, &APlayerController_Base::GameWin);
		GM->OnUpdateCollectibles.AddUniqueDynamic(this, &APlayerController_Base::UpdateScore);
	}
}

void APlayerController_Base::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(InputComponent))
	{
		PEI->BindAction(InputActions->Move.LoadSynchronous(), ETriggerEvent::Triggered, this, &APlayerController_Base::Move);
		PEI->BindAction(InputActions->Look.LoadSynchronous(), ETriggerEvent::Triggered, this, &APlayerController_Base::Look);
		PEI->BindAction(InputActions->Action.LoadSynchronous(), ETriggerEvent::Triggered, this, &APlayerController_Base::Action);
		PEI->BindAction(InputActions->Fire.LoadSynchronous(), ETriggerEvent::Triggered, this, &APlayerController_Base::Fire);
		PEI->BindAction(InputActions->Jump.LoadSynchronous(), ETriggerEvent::Triggered, this, &APlayerController_Base::Jump);
		PEI->BindAction(InputActions->Scroll.LoadSynchronous(), ETriggerEvent::Triggered, this, &APlayerController_Base::Scroll);
	}
}

void APlayerController_Base::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	LocalPlayerCharacter = GetPawn();

	if (auto* HealthCompInterface = Cast<IHealthInterface>(InPawn->GetComponentByClass(UHealthComponent::StaticClass())))
	{
		auto& HealthDelegate = HealthCompInterface->GetHealthChangedDelegate();
		HealthDelegate.AddDynamic(this, &APlayerController_Base::UpdateHealth);

		if (IsLocalController() && HUDClass)
		{
			ActiveHUD = CreateWidget<UMyHUDWidget>(this, HUDClass);
			if (ActiveHUD)
			{
				ActiveHUD->AddToViewport();
				ActiveHUD->SetMaxHealth(HealthCompInterface->GetMaxHealth());
				ActiveHUD->OnScoreChanged(0);
			}
		}
	}
}

void APlayerController_Base::OnUnPossess()
{
	if (auto* HealthCompInterface = Cast<IHealthInterface>(LocalPlayerCharacter->GetComponentByClass(UHealthComponent::StaticClass())))
	{
		HealthCompInterface->GetHealthChangedDelegate().RemoveDynamic(this, &APlayerController_Base::UpdateHealth);
	}
	Super::OnUnPossess();
}

void APlayerController_Base::UpdateHealth(float NewHealth)
{
	ActiveHUD->OnHealthChanged(NewHealth);
}

void APlayerController_Base::Move(const FInputActionInstance& Instance)
{
	IIAInterface::Execute_Move(LocalPlayerCharacter, Instance);
}

void APlayerController_Base::Look(const FInputActionInstance& Instance)
{
	IIAInterface::Execute_Look(LocalPlayerCharacter, Instance);
}

void APlayerController_Base::Action(const FInputActionInstance& Instance)
{
	IIAInterface::Execute_Action(LocalPlayerCharacter, Instance);
}

void APlayerController_Base::Fire(const FInputActionInstance& Instance)
{
	IIAInterface::Execute_Fire(LocalPlayerCharacter, Instance);
}

void APlayerController_Base::Jump(const FInputActionInstance& Instance)
{
	IIAInterface::Execute_JumpAction(LocalPlayerCharacter, Instance);
}

void APlayerController_Base::Scroll(const FInputActionInstance& Instance)
{
	IIAInterface::Execute_Scroll(LocalPlayerCharacter, Instance);
}

void APlayerController_Base::UpdateScore(uint8 Score)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Ammo Count: %d"), Score));
	ActiveHUD->OnScoreChanged(Score);
}

void APlayerController_Base::GameWin()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Game Won!"));
}
